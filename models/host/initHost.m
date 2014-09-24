clc
%%
fprintf('Start initializing Sphero and CV\n');

%%
if ~exist('sphOrangeName', 'var')
    sphOrangeName = 'Sphero-PGP';
else
    sphOrangeName = char(sphOrangeName);
end

if ~exist('sphBlueName', 'var')
    sphBlueName = 'Sphero-PRB';
else
    sphBlueName = char(sphBlueName);
end

%%
fprintf('Sphero init\n');

sphero_init(sphOrangeName, sphBlueName);

%%
fprintf('Zumo connect \n')
comms.BluetoothStore.forceReset();
comms.BluetoothStore.registerRobot(RobotID.ZUMO_32B0,'Adafruit EZ-Link 32b0', 1);
comms.BluetoothStore.registerRobot(RobotID.ZUMO_329B,'Adafruit EZ-Link 329b', 1);
z1 = comms.Bt(RobotID.ZUMO_32B0);
z1.init();
z2 = comms.Bt(RobotID.ZUMO_329B);
z2.init();

%%
fprintf('Init trackTwoMinions\n')
detectVideoFormatStr = 'RGB24_1600x1200';
trackVideoFormatStr = 'RGB24_640x480';

initTrackTwoMinions(0, detectVideoFormatStr, trackVideoFormatStr)

%%

fprintf('Done initializing Sphero and CV\n');