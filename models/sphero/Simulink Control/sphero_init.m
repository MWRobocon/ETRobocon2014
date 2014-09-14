function sphero_init(sphOrangeName, sphBlueName)

sphOrange = sphero(sphOrangeName);
% sphBlue = sphero(sphBlueName);

comms.SpheroStore.forceReset();
comms.SpheroStore.registerRobot(RobotID.SPHERO_ORANGE, sphOrange);
% comms.SpheroStore.registerRobot(RobotID.SPHERO_BLUE, sphBlue);


