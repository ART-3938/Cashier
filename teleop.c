#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     Motors,         sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void rotate()
{
	float r = joystick.joy1_x2 / 128.0;

	int speed = 100;

	motor[motorFL] = motor[motorFL] + (speed * r);
	motor[motorBR] = motor[motorBR] + (speed * -r);
	motor[motorFR] = motor[motorFR] + (speed * -r);
	motor[motorBL] = motor[motorBL] + (speed * r);
}

void strafe(){
	float x = joystick.joy1_x1 / 128.0;
	float y = joystick.joy1_y1 / 128.0;

	int speed = 100;

	//Speed coefficient of FL and BR motors
	float a;
	//Speed coefficient of FR and BL motors
	float b;

	//math!
	a = (-x - y)/2.0;
	b = (x - y)/2.0;

	//divide by 1.3 because the joystick values are above 100.
	motor[motorFL] = speed * a;
	motor[motorBR] = speed * a;
	motor[motorFR] = speed * b;
	motor[motorBL] = speed * b;
}

void InitializeRobot()
{
	disableDiagnosticsDisplay();
}

task drive()
{
	//strafe();
	rotate();
}

task drawScreen()
{
	eraseDisplay();
	nxtDisplayCenteredTextLine(0, "ART-3938");
	nxtDisplayString(0, "MotorFL: %d", motor[motorFL]);
  nxtDisplayString(1, "MotorFR: %d", motor[motorFR]);
  nxtDisplayString(2, "MotorBL: %d", motor[motorBL]);
  nxtDisplayString(3, "MotorBR: %d", motor[motorBR]);
	wait1Msec(100);
}

task arm()
{
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
