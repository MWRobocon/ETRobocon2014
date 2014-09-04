<<<<<<< HEAD
function [data,rxLength] = readWrapper(numBytes,deviceName,channelNum)
    robot = comms.Bt(deviceName,channelNum);
    [data,rxLength] = robot.read(numBytes);
=======
function [data,rxLength] = readWrapper(robotId,numBytes)
    robot = comms.Bt(robotId);
    [data,rxLength] = robot.read(numBytes);
>>>>>>> refs/remotes/origin/master
end