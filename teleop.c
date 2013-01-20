#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     Controllers,    sensorI2CMuxController)
#pragma config(Sensor, S2,     Infrared1,      sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Infrared2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorARM,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LED,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoArm1,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoArm2,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Servo,  srvo_S1_C4_1,    servoARM,             tServoStandard)
/*
	ART-3938
	Last edited 12.22.12

	Code for teleop mode -- uses one gamepad for now
*/

#include "JoystickDriver.c"

string debug_val;

void rotate()
{

}

void strafe(){
	short x = (joystick.joy1_x1 / 128.0) * 100;
	short y = (joystick.joy1_y1 / 128.0) * 100;

	motor[motorL] = y;
	motor[motorR] = y;
	motor[motorF] = x;
	motor[motorB] = x;
}

void InitializeRobot()
{
	disableDiagnosticsDisplay();
	eraseDisplay();
	nxtDisplayCenteredBigTextLine(2, "ART-3938");
	nxtDisplayCenteredTextLine(5, "Waiting to Start");
	StringConcatenate(debug_val, "_DIAG_DISPLAY_DISABLED");
	motor[LED] = 100;
	//servo[servoARM] = 200;
}

task drive()
{
	while(true){
		strafe();
		//rotate();
	}
}

task drawScreen()
{
	while(true)
	{
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "ART-3938");
	nxtDisplayString(0, "MotorL: %d", motor[motorL]);
  nxtDisplayString(1, "MotorR: %d", motor[motorR]);
  nxtDisplayString(2, "MotorF: %d", motor[motorF]);
  nxtDisplayString(3, "MotorB: %d", motor[motorB]);
  nxtDisplayString(4, "MotorARM: %d", motor[motorARM]);
  //nxtDisplayString(5, "ServoARM: %d", ServoValue[servoARM]);
  nxtDisplayCenteredTextLine(7, "ART-3938");
	wait10Msec(10);
	}
}

task arm()
{
	bool pressed_sARM_up = false;
	bool pressed_sARM_down = false;
	int time_step = 200;
	while(true){


		//Lower Arm
		if(joy1Btn(2) == 1 && joy1Btn(3) == 0){
			motor[motorARM] = 30;
		}
		else if(joy1Btn(3) == 1 && joy1Btn(2) == 0){
			motor[motorARM] = -5;
		}
		else{
			motor[motorARM] = 0;
		}

		//Upper Arm

		if(joy1Btn(1) == 1){
			if(!pressed_sARM_up)
			{
				//servo[servoARM] = servo[servoARM] + 5;
				ClearTimer(T1);
				pressed_sARM_up = true;
			}
			else
			{
				if(time1[T1] >= time_step)
				{
					pressed_sARM_up = false;
				}
			}
		}
		else if(joy1Btn(4) == 1){
			if(!pressed_sARM_down)
			{
				//servo[servoARM] = servo[servoARM] - 5;
				ClearTimer(T2);
				pressed_sARM_down = true;
			}
			else
			{
				if(time1[T2] >= time_step)
				{
					pressed_sARM_down = false;
				}
			}
		}

	}
}

task main()
{
	InitializeRobot();
	waitForStart();
	getJoystickSettings(joystick);
	StartTask(drive);
	StartTask(drawScreen);
	StartTask(arm);
	while(true)
	{
			getJoystickSettings(joystick);
	}
}
