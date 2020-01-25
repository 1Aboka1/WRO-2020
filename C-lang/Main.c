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
	return compass.relativeHeading * (-5);
}

//This procedure directs robot to a startPosition that is right before a centre of field
void startPosition(){
	time1[T1] = 0;
	while(time1[T1] < 300 && irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		OmniDrive(FrontCalibrate(), -100, 0);
	}
	time1[T1] = 0;
	while(time1[T1] < 4000 && getUSDistance(S4) != 255 && irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		OmniDrive(FrontCalibrate(), -100, -100);
	}
	time1[T1] = 0;
	while(time1[T1] < 200 && irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		OmniDrive(FrontCalibrate(), 0, 100);
	}
	time1[T1] = 0;
	while(time1[T1] < 2500 && irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		OmniDrive(FrontCalibrate(), -100, 0);
	}
	time1[T1] = 0;
	while(time1[T1] < 2000 && irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		OmniDrive(FrontCalibrate(), 100, 90);
	}
	OmniDrive(0, 0, 0);
	time1[T1] = 0;
	while(irSeeker.dcDirection == 0){
		readSensor(&irSeeker);
		readSensor(&compass);
		if(time1[T1] > 3000)
			startPosition();
	}
}

void wallCalibrate(){
	time1[T1] = 0;
	while(time1[T1] < 500)
		OmniDrive(FrontCalibrate(), 100, 0);
	if(getUSDistance(S4) > 0 && getUSDistance(S4) < 65){
		while(getUSDistance(S4) > 0 && getUSDistance(S4) < 65 && irSeeker.dcDirection == 5){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), 100, 80);
		}
	}
	else if(getUSDistance(S4) < 255 && getUSDistance(S4) > 115){
		while(getUSDistance(S4) < 255 && getUSDistance(S4) > 115 && irSeeker.dcDirection == 5){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), 100, -80);
		}
	}
	else{
		while(irSeeker.dcDirection == 5){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), 100, 0);
		}
	}
}

task main()
{
	initSensor(&irSeeker, S3);
	initSensor(&compass, S1);
	compass.offset = 300;

	//Main loop
	while(true){
		readSensor(&irSeeker);
		readSensor(&compass);
		int irDir = irSeeker.dcDirection;
		switch(irDir){
		case 1:
			OmniDrive(FrontCalibrate(), -1000, 0);
			break;
		case 2:
			OmniDrive(FrontCalibrate(), -1000, 0);
			break;
		case 3:
			OmniDrive(FrontCalibrate(), 0, 1000);
			break;
		case 4:
			OmniDrive(FrontCalibrate(), 0, 1000);
			break;
		case 5:
			wallCalibrate();
			break;
		case 6:
			OmniDrive(FrontCalibrate(), 0, -1000);
			break;
		case 7:
			OmniDrive(FrontCalibrate(), 0, -1000);
			break;
		case 8:
			OmniDrive(FrontCalibrate(), -1000, 0);
			break;
		case 9:
			OmniDrive(FrontCalibrate(), -1000, 0);
			break;
		default:
			startPosition();
			break;
		}
	}
}











































































































































































































































































































//This code and this project is a private property of ?ae?ia Aaoeoae? 29.08.2005
//Made by 1AbokA1
