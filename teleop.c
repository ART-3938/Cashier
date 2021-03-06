#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     Controllers,    sensorNone)
#pragma config(Sensor, S2,     InfraredL,      sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     InfraredR,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorB,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LED,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorARM,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    servoArm1,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoArm2,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servoArm3,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servoArm4,            tServoStandard)
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

//Globals

//Arm values
short raiseSpeed = 20;
short lowerSpeed = -7;
float encoderScale = 600.0;
short arm3Initial = 165;
short timeStepAuto = 50;
short timeStepManual = 50;
short servoStep = 3;
bool motorActive = false;

task drive(){
	short x;
	short y;
	short r;
	while(true){
		//strafe
		x = (joystick.joy1_x1 / 128.0) * 100;
		y = (joystick.joy1_y1 / 128.0) * 100;

		//rotate
		r = (joystick.joy1_x2 / 128.0) * 100;

		motor[motorL] = y - r;
		motor[motorR] = y + r;
		motor[motorF] = x - r;
		motor[motorB] = x + r;
	}
}

void InitializeRobot()
{
	disableDiagnosticsDisplay();
	eraseDisplay();
	nxtDisplayCenteredBigTextLine(2, "ART-3938");
	nxtDisplayCenteredTextLine(5, "Waiting to Start");
	servo[servoArm1] = 255;
	servo[servoArm2] = 0;
	servo[servoArm3] = 165;
	short armChangeRate = 5;
	servoChangeRate[servoArm1] = armChangeRate;
	servoChangeRate[servoArm2] = armChangeRate;
	servoChangeRate[servoArm3] = armChangeRate;
	nMotorEncoder[motorARM] = 0;
}

task drawScreen()
{
	while(true)
	{
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "ART-3938");
	//nxtDisplayString(0, "MotorL: %d", motor[motorL]);
  //nxtDisplayString(1, "MotorR: %d", motor[motorR]);
  //nxtDisplayString(2, "MotorF: %d", motor[motorF]);
  //nxtDisplayString(3, "MotorB: %d", motor[motorB]);
	nxtDisplayString(0, "InfraredL: %d", SensorValue[InfraredL]);
	nxtDisplayString(1, "LEDL: %d", motor[LED]);
	nxtDisplayString(2, "InfraredR: %d", SensorValue[InfraredR]);
  nxtDisplayString(4, "MotorARM: %d", motor[motorARM]);
  nxtDisplayString(5, "Encoder: %d", nMotorEncoder[motorARM]);
  nxtDisplayString(6, "ServArm3: %d", ServoValue[servoArm3]);
  nxtDisplayCenteredTextLine(7, "ART-3938");
	wait10Msec(10);
	}
}

task led()
{
	float value = 0;
	float change = PI/600;

	while(true)
	{
		wait1Msec(5);
		value += change;
		motor[LED] = 100 * pow(sin(value), 2);
	}
}

void autoArm(){
	short tophat = joystick.joy1_TopHat;

	if(tophat == 0){
		motor[motorARM] = raiseSpeed;
		servo[servoArm3] = arm3Initial + ((nMotorEncoder[motorARM] / encoderScale) * 256.0) - ServoValue[servoArm2];
		motorActive = true;
	}
	else if(tophat == 4){
		motor[motorARM] = lowerSpeed;
		servo[servoArm3] = arm3Initial + ((nMotorEncoder[motorARM] / encoderScale) * 256.0) - ServoValue[servoArm2];
		motorActive = true;
	}
	else if(tophat == 2){
		if(time1[T1] > timeStepAuto){
			ClearTimer(T1);
			servo[servoArm1] -= servoStep;
			servo[servoArm2] += servoStep;
			servo[servoArm3] -= servoStep;
			motorActive = false;
		}
	}
	else if(tophat == 6){
		if(time1[T1] > timeStepAuto){
			ClearTimer(T1);
			servo[servoArm1] += servoStep;
			servo[servoArm2] -= servoStep;
			servo[servoArm3] += servoStep;
			motorActive = false;
		}
	}
	else{
		motorActive = false;
	}
}

void manualArm(){
	if(joy1Btn(4)){
		motorActive = true;
		motor[motorARM] = raiseSpeed;
	}
	else if(joy1Btn(2)){
		motorActive = true;
		motor[motorARM] = lowerSpeed;
	}
	if(joy1Btn(3) && time1[T2] > timeStepManual){
		ClearTimer(T2);
		servo[servoArm1] += servoStep;
		servo[servoArm2] -= servoStep;
		motorActive = false;
	}
	else if(joy1Btn(1) && time1[T2] > timeStepManual){
		ClearTimer(T2);
		servo[servoArm1] -= servoStep;
		servo[servoArm2] += servoStep;
		motorActive = false;
	}
	if(joy1Btn(6) && time1[T3] > timeStepManual){
		ClearTimer(T3);
		servo[servoArm3] -= servoStep;
		motorActive = false;
	}
	else if(joy1Btn(8) && time1[T3] > timeStepManual){
		ClearTimer(T3);
		servo[servoArm3] += servoStep;
		motorActive = false;
	}
	else{
		motorActive = false;
	}
}

void adjustArmValues(){
	if(ServoValue[servoArm2] > 64){
		raiseSpeed = 35;
		if(!motorActive){
			motor[motorARM] = 10;
		}
	}
	else{
		raiseSpeed = 20;
		if(!motorActive){
			motor[motorARM] = 0;
		}
	}
}

task arm()
{
	while(true){
		autoArm();
		manualArm();
		adjustArmValues();
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
	StartTask(led);
	while(true)
	{
			getJoystickSettings(joystick);
	}
}
