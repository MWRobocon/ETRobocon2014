clc
%%
fprintf('Start initializing Sphero and Zumo\n');

%%
if ~exist('sphOrangeName', 'var')
    sphOrangeName = 'Sphero-PGP';
else
    sphOrangeName = char(sphOrangeName);
end

if ~exist('sphBlueName', 'var')
    sphBlueName = 'Sphero-PYP';
else
    sphBlueName = char(sphBlueName);
end

%%
fprintf('Sphero init\n');

sphero_init(sphOrangeName, sphBlueName);

%% Reset BluetoothStore and Register Robots
fprintf('Reseting Bluetooth Store\n');
comms.BluetoothStore.closeAllOpen();
comms.BluetoothStore.forceReset();
fprintf('Done reseting Bluetooth Store\n');

fprintf('Registering Robots\n');
comms.BluetoothStore.registerRobot(RobotID.ZUMO_32B0,'Adafruit EZ-Link 32b0', 1);
comms.BluetoothStore.registerRobot(RobotID.ZUMO_329B,'Adafruit EZ-Link 329b', 1);
comms.BluetoothStore.registerRobot(RobotID.NXT, 'NXT', 1);
fprintf('Done Registering Robots\n');

%%
fprintf('Zumo connect \n')
z1 = comms.Bt(RobotID.ZUMO_32B0);
z1.init();
z2 = comms.Bt(RobotID.ZUMO_329B);
z2.init();
fprintf('Done initializing Sphero and Zumo\n');
