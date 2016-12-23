typedef struct {
	float current;
	float kP;
	float kI;
	float kD;
	float target;
	float error;
	float integral;
	float derivative;
	float lastError;
	float threshold;
	int   deltaTime;
	int   lastTime;
} pid;

int MC29[128] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 13, 13, 14,
	14, 14, 14, 15, 15, 15, 15, 16, 16, 16,
	16, 16, 17, 17, 17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 20, 20, 20, 20, 21, 21, 21, 22,
	22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
	25, 25, 25, 26, 26, 26, 27, 27, 27, 28,
	28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
	32, 33, 33, 34, 34, 35, 36, 36, 37, 37,
	38, 39, 40, 40, 41, 42, 43, 44, 45, 46,
	46, 48, 49, 50, 51, 53, 55, 56, 58, 60,
	62, 64, 67, 70, 72, 76, 79, 83, 84, 127,
};

void
tank (int iSpeedL, int iSpeedR) {
	motor[chassis_l1] = 
	motor[chassis_l2] = sgn(iSpeedL) * MC29[abs(clipNum(iSpeedL, 127, -127))];
	motor[chassis_r1] = 
	motor[chassis_r2] = sgn(iSpeedR) * MC29[abs(clipNum(iSpeedR, 127, -127))];
}

void
arm (int iSpeed) {
	motor[arm_l1] = 
	motor[arm_l2] = 
	motor[arm_l3] = 
	motor[arm_r1] = 
	motor[arm_r2] = 
	motor[arm_r3] = clipNum(iSpeed, 127, -127);
}

pid sArmPID;

int iArmPID (int iDes) {
	const float kP = 0.5; 
	const float kD = 0.4;
	
	sArmPID.current   = (SensorValue[I2C_1] + SensorValue[I2C_2]) / 2;
	
	sArmPID.error     = sArmPID.current - iDes;
	sArmPID.deltaTime = nPgmTime - sArmPID.lastTime;
	
	if (sArmPID.deltaTime == 0)
		sArmPID.derivative = 0;
	else
		sArmPID.derivative = (sArmPID.error - sArmPID.lastError) / sArmPID.deltaTime;
	
	return ( (sArmPID.error * kP) + (sArmPID.derivative * kD) );
		
	sArmPID.lastTime  = nPgmTime;
	sArmPID.lastError = sArmPID.error;
}

int iArmPID (int iDes, int iMaxSpeed) {
	return ( clipNum(iArmPID(iDes), abs(iMaxSpeed), -abs(iMaxSpeed)) );
}
