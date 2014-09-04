<<<<<<< HEAD
function [data,rxLength] = readWrapper(robotId,numBytes)
    robot = comms.Bt(robotId);
    [data,rxLength] = robot.read(numBytes);
=======
<<<<<<< HEAD
function [data,rxLength] = readWrapper(numBytes,deviceName,channelNum)
    robot = comms.Bt(deviceName,channelNum);
    [data,rxLength] = robot.read(numBytes);
=======
function [data,rxLength] = readWrapper(robotId,numBytes)
    robot = comms.Bt(robotId);
    [data,rxLength] = robot.read(numBytes);
>>>>>>> refs/remotes/origin/master
>>>>>>> 49348b51a63c56d87ba47b68ef106e265e871506
end