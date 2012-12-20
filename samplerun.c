#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     Motors,         sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armMotor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    armServo,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void InitializeRobot()
{
	disableDiagnosticsDisplay();
}

task drive()
{
	//we don't have a drive train
	wait10Msec(1000);
}

task drawScreen()
{
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "ART-3938");
	nxtDisplayString(1, "Arm: %d", motor[armMotor]);
	nxtDisplayString(2, "Servo: %d", ServoValue[armServo]);
	wait1Msec(100);
}

task arm()
{
	float am = (joystick.joy1_y1 / 128.0) * 20;
	motor[armMotor] = am;
	float as = abs((joystick.joy1_y2 / 128.0)) * 255;
	servo[armServo] = as;
}

task main()
{
	InitializeRobot();
	waitForStart();
	while(true)
	{
		getJoystickSettings(joystick);
		StartTask(drive);
		StartTask(drawScreen);
		StartTask(arm);
	}
}
