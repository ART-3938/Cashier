#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     Controllers,    sensorNone)
#pragma config(Sensor, S2,     infrared1,      sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     infrared2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorARM,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LED,           tmotorTetrix, openLoop)
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

int zone1Num = 7;
int zone2Num = 7;

void rotate(bool clockwise, int speed)
{
	if(!clockwise){
		speed *= -1;
	}
	motor[motorL] = speed;
	motor[motorR] = -speed;
	motor[motorF] = speed;
	motor[motorB] = -speed;

}

void strafe(float x, float y){
	motor[motorL] = y;
	motor[motorR] = y;
	motor[motorF] = x;
	motor[motorB] = x;
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

bool isInZone(int zone, int sensor)
{
	return SensorValue[sensor] == zone;
}

void moveUntilAligned(int x, int y, int zone, int sensor){
	bool aligned = false;
	strafe(x, y)
	while(!aligned){
		if(isInZone(zone, sensor){
			aligned = true;
			strafe(0, 0);
		}
	}
}

bool realignZone1(){
	if(isInZone(zone1Num, infrared1){
		return false;
	}
	else{
		strafe(0, 0);
		if(SensorValue[infrared1] < zone1Num){
			moveUntilAligned(-10, -10, zone1Num, infrared1);
		}
		else{
			moveUntilAligned(10, 10, zone1Num, infrared1);
		}
		return true;
	}
{

void driveDiagonal(){
	int vectorX = 20;
	int vectorY = 10;

	bool aligned = false;
	strafe(vectorX, vectorY);
	while(!aligned){
		if(realignZone1()){
			strafe(vectorX, vectorY);
		}
		if(SensorValue[infrared2] == zone2Num){
			strafe(0, 0);
			aligned = true;
		}
	}
}

void placeRing(){

}

task AI()
{
	//presumably, here we put the sensor-based stimuli for action to be handled in
	//asynchronous tasks
	wait10Msec(0); //1500 is longest
	moveUntilAligned(10, 10, zone1Num, infrared1); //drive forward
	driveDiagonal();
	placeRing();
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
