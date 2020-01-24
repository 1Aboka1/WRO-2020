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

void OmniDrive(int side, int frontback, int turn){
	setMotorSpeed(motorC, (frontback - side) + turn);
	setMotorSpeed(motorB, ((frontback - side) - turn) - frontback);
	setMotorSpeed(motorA, ((frontback + side) - turn) * (-1));
}

int FrontCalibrate(){
	readSensor(&compass);
	displayTextLine(2, "%4d", compass.relativeHeading);
	return compass.relativeHeading * (-1);
}

task main()
{
	initSensor(&irSeeker, S3);
	initSensor(&compass, S1);
	compass.offset = 288;

	while(true)
		OmniDrive(FrontCalibrate(), 0, 0);


}
