#pragma config(Sensor, S3, HTIRS2, sensorI2CCustom)
#pragma config(Sensor, S2, , sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ,               sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorEV3_Medium, openLoop, encoder)


#include "include/hitechnic-compass.h"
#include "include/hitechnic-irseeker-v2.h"

tHTMC compass;
tHTIRS2 irSeeker;

//This procedure is a formula for HolonomicDrive
void OmniDrive(int side, int frontback, int turn){
	setMotorSpeed(motorC, (frontback - side) + turn);
	setMotorSpeed(motorB, ((frontback - side) - turn) - frontback);
	setMotorSpeed(motorA, ((frontback + side) - turn) * (-1));
}

// This function returns a value for motors to direct ahead
int FrontCalibrate(){
	readSensor(&compass);
	//displayTextLine(2, "%4d", compass.relativeHeading);
	return compass.relativeHeading * (-5);
}

//This procedure directs robot to a startPosition that is right before a centre of field
void startPosition(){
	time1[T1] = 0;
	while(time1[T1] < 600)
		OmniDrive(FrontCalibrate(), -100, 0);
	time1[T1] = 0;
	while(time1[T1] < 4000 && getUSDistance(S4) != 255 && irSeeker.dcDirection == 0)
		OmniDrive(FrontCalibrate(), 0, -100);
	time1[T1] = 0;
	while(time1[T1] < 3500 && irSeeker.dcDirection == 0)
		OmniDrive(FrontCalibrate(), -100, 0);
	time1[T1] = 0;
	while(time1[T1] < 2000 && irSeeker.dcDirection == 0)
		OmniDrive(FrontCalibrate(), 100, 70);
	OmniDrive(0, 0, 0);
	while(irSeeker.dcDirection == 0)
		continue;
}

task main()
{
	initSensor(&irSeeker, S3);
	initSensor(&compass, S1);
	compass.offset = 310;

	//Main loop
	while(true){
		readSensor(&irSeeker);
		readSensor(&compass);
		int irDir = irSeeker.dcDirection;
		switch(irDir){
		case 1:
			OmniDrive(FrontCalibrate(), -100, 0);
			break;
		case 2:
			OmniDrive(FrontCalibrate(), -100, 0);
			break;
		case 3:
			OmniDrive(FrontCalibrate(), 0, 100);
			break;
		case 4:
			OmniDrive(FrontCalibrate(), 0, 100);
			break;
		case 5:
			OmniDrive(FrontCalibrate(), 100, 0);
			break;
		case 6:
			OmniDrive(FrontCalibrate(), 0, -100);
			break;
		case 7:
			OmniDrive(FrontCalibrate(), 0, -100);
			break;
		case 8:
			OmniDrive(FrontCalibrate(), -100, 0);
			break;
		case 9:
			OmniDrive(FrontCalibrate(), -100, 0);
			break;
		default:
			OmniDrive(FrontCalibrate(), -100, 0);
			break;
		}
	}
}
