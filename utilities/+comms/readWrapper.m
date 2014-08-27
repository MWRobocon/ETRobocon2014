function [data,rxLength] = readWrapper(numBytes,deviceName,channelNum)
    robot = comms.Bt(deviceName,channelNum);
    [data,rxLength] = robot.read(numBytes);
end