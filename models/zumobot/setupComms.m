%% Register Robot
comms.BluetoothStore.registerRobot(RobotID.ZUMO_ADAFRUIT_32B0,'Adafruit EZ-Link 32b0',1);

%% Connect to robot
z = comms.Bt(RobotID.ZUMO_ADAFRUIT_32B0);
z.init();
z.write(10,1);
z.write(20,1);
