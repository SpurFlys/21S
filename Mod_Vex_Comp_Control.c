void allMotorsOff();
void allTasksStop();
void initIO();
void pre_auton();
task autonomous();
task usercontrol();
string sTeam;
bool bLCDUserControl, bLCDAuton;

#define clipNum(iInput, iHigh, iLow) iInput <= iLow ? iLow : (iInput >= iHigh ? iHigh : iInput)

bool bStopTasksBetweenModes = true;

void
clearLCDLines () {
	clearLCDLine(0);
	clearLCDLine(1);
}

void
clearAllIME () {
	SensorValue[I2C_1] =
	SensorValue[I2C_2] =
	SensorValue[I2C_3] =
	SensorValue[I2C_4] =
	SensorValue[I2C_5] =
	SensorValue[I2C_6] =
	SensorValue[I2C_7] =
	SensorValue[I2C_8] = 0;
}

void
waitForReleased7D () {
	while (vexRT[Btn7D]){} wait1Msec(25);
}

task
main() {
	bLCDBacklight = true;
	clearDebugStream();
	clearLCDLines();
	initIO();
	allMotorsOff();
	displayLCDCenteredString(0, sTeam);
	displayLCDCenteredString(1,  "Starting . . .");
	wait1Msec(2000);
	pre_auton();

	while (true){
		clearLCDLine(1);
		if (bIfiAutonomousMode){
			if (bLCDAuton) {
				clearLCDLines();
				displayLCDCenteredString(0, sTeam);
				displayLCDCenteredString(1, "Autonomous");
			}
			else clearLCDLines();
			startTask(autonomous);

			while (bIfiAutonomousMode && !bIfiRobotDisabled){
				if (!bVEXNETActive){
					if (nVexRCReceiveState == vrNoXmiters)
						allMotorsOff();
				}
				wait1Msec(25);
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
				allTasksStop();
		}

		else{
			if (bLCDUserControl) {
				clearLCDLines();
				displayLCDCenteredString(0, sTeam);
				displayLCDCenteredString(1, "User Control");
			}
			else clearLCDLines();
			startTask(usercontrol);

			while (!bIfiAutonomousMode && !bIfiRobotDisabled){
				if (nVexRCReceiveState == vrNoXmiters)
					allMotorsOff();
				wait1Msec(25);
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
				allTasksStop();
		}
	}
}


void
allMotorsOff() {
	for (int i = 0; i < 10; i++)
		motor[i] = 0;
}

void
allTasksStop() {
	stopTask(1);
	stopTask(2);
	stopTask(3);
	stopTask(4);
	stopTask(5);
	stopTask(6);
	stopTask(7);
	stopTask(8);
	stopTask(9);
	stopTask(10);
	stopTask(11);
	stopTask(12);
	stopTask(13);
	stopTask(14);
	stopTask(15);
	stopTask(16);
	stopTask(17);
	stopTask(18);
	stopTask(19);
}
