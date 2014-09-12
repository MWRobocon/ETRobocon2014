function writeWrapper(robotId,byteArray,txLength)
% WRITEWRAPPER Wrapper for writing to robot via bluetooth
% 
% writeWrapper(byteArray,txLength,deviceName,channelNum)

    robot = comms.Bt(robotId);
    robot.write(byteArray,txLength);
end