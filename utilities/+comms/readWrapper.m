<<<<<<< HEAD
function [data,rxLength] = readWrapper(numBytes,deviceName,channelNum)
    robot = comms.Bt(deviceName,channelNum);
    [data,rxLength] = robot.read(numBytes);
=======
function [data,rxLength] = readWrapper(numBytes,deviceName,channelNum)
    robot = comms.Bt(deviceName,channelNum);
    [data,rxLength] = robot.read(numBytes);
>>>>>>> refs/remotes/origin/Minions
end