function [data,rxLength] = readWrapper(robotId,numBytes)
    robot = comms.Bt(robotId);
    [data,rxLength] = robot.read(numBytes);
end