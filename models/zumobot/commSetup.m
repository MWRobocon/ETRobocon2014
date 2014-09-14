% RobotID.m
% ZUMO_ADAFRUIT_32B0 (6);
% ZUMO_ADAFRUIT_32CA (7);
% ZUMO_ADAFRUIT_329B (8);
clear z z0 z1 z2
%% setup zumobot 1
comms.BluetoothStore.registerRobot(RobotID.ZUMO_ADAFRUIT_32B0,'Adafruit EZ-Link 32b0',1);
z0 = comms.Bt(RobotID.ZUMO_ADAFRUIT_32B0);
z0.init();
%% setup zumobot 2
comms.BluetoothStore.registerRobot(RobotID.ZUMO_ADAFRUIT_329B,'Adafruit EZ-Link 329b',1);
z1 = comms.Bt(RobotID.ZUMO_ADAFRUIT_329B);
z1.init();
%% start zumobot 1
z0.write(10,1);
%% start zumobot 2
z1.write(10,1);
%% stop zumobot 1
z0.write(0,1);
%% stop zumobot 2
z0.write(0,1)



