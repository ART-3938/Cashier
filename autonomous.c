#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     Motors,         sensorNone)
#pragma config(Sensor, S2,     Infrared1,      sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Infrared2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorARM,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    armOne,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    armTwo,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
	ART-3938
	Last edited 12.22.12

	Code for autonomous motion
	All "tasks" for motion in teleop mode converted to bools, because, well, asynchronous
	operation should (?) still work is tasks are calling methods, and we don't want
	to rotate/strafe the bot forever -- only a certain distance
*/

#include "JoystickDriver.c"

void rotate(float r)
{
	int speed = 100;

	motor[motorFL] = motor[motorFL] + (speed * r);
	motor[motorBR] = motor[motorBR] + (speed * -r);
	motor[motorFR] = motor[motorFR] + (speed * -r);
	motor[motorBL] = motor[motorBL] + (speed * r);
}

void strafe(float x, float y){
	int speed = 100;

	//Speed coefficient of FL and BR motors
	float a;
	//Speed coefficient of FR and BL motors
	float b;

	//math!
	a = (-x - y)/2.0;
	b = (x - y)/2.0;

	motor[motorFL] = speed * a;
	motor[motorBR] = speed * a;
	motor[motorFR] = speed * b;
	motor[motorBL] = speed * b;
}

void InitializeRobot()
{
	disableDiagnosticsDisplay();
}

task drawScreen()
{
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "ART-3938");
	nxtDisplayString(0, "MotorFL: %d", motor[motorFL]);
  nxtDisplayString(1, "MotorFR: %d", motor[motorFR]);
  nxtDisplayString(2, "MotorBL: %d", motor[motorBL]);
  nxtDisplayString(3, "MotorBR: %d", motor[motorBR]);
  nxtDisplayString(4, "MotorARM: %d", motor[motorARM]);
  nxtDisplayString(5, "ServoOne: %d", servo[armOne]);
  nxtDisplayString(6, "ServoTwo: %d", motor[armTwo]);
  nxtDisplayCenteredTextLine(7, "ART-3938");
	wait1Msec(100);
}

bool arm(int servoSetting, int armSetting)
{
	//servoSetting is value from -127-128 (I think); armSetting is desired
	//speed -- we could do more if we put on encoders
}

task AI()
{
	//presumably, here we put the sensor-based stimuli for action to be handled in
	//asynchronous tasks
}

task main()
{
	InitializeRobot();
	waitForStart();
	while(true)
	{
		StartTask(drawScreen);
		StartTask(AI);
	}
}
