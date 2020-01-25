//Here is a v2 of startPosition(which is better i will check in Monday)
void startPositionV2(){
	time1[T1] = 0;
	if(getUSDistance(S4) > 65 && getUSDistance(S4) < 115){
		while(getUSDistance(S4) > 65 && irSeeker.dcDirection == 0){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), -100, -80);
		}
		while(getUSDistance(S4) < 65 && irSeeker.dcDirection == 0){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), -100, 80);
		}
		time1[T1] = 0;
		while(time1[T1] < 200){
			readSensor(&irSeeker);
			OmniDrive(FrontCalibrate(), 100, 0);
		}
		if(getUSDistance(S4) < 65){
			while(getUSDistance(S4) < 65 && irSeeker.dcDirection == 0){
				OmniDrive(FrontCalibrate(), 0, 100);
				readSensor(&irSeeker);
			}
		}
		else if(getUSDistance(S4) > 115){
			while(getUSDistance(S4) > 115 && irSeeker.dcDirection == 0){
				OmniDrive(FrontCalibrate(), 0, -100);
				readSensor(&irSeeker);
			}
		}
		while(irSeeker.dcDirection == 0){
			OmniDrive(FrontCalibrate(), 0, 0);
			readSensor(&irSeeker);
		}
	}
	else{
		while(irSeeker.dcDirection == 0){
			OmniDrive(FrontCalibrate(), 0, 0);
			readSensor(&irSeeker);
		}
	}
}
