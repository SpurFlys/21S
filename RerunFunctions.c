task
record () {
	int j = 10, s = 1;
	for (int i = 0; i < 150; i++) {
		if (j == 10) {
			writeDebugStream("\n");
			writeDebugStream("\n	/* %i Second(s) */", s);
			s++;
			j = 0;
		}
		j++;
		writeDebugStream ("\n	auton (%i, %i);", (SensorValue[I2C_1] + -SensorValue[I2C_2]) / 2, motor[arm_l1]);
		delay(100);
	}
}

void
auton (int iArmDes, int iArmSpeed) {
	arm(iArmPID (iArmDes, iArmSpeed));
	delay(100);
}
