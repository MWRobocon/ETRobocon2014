function writeWrapper(byteArray,txLength,deviceName,channelNum)
% WRITEWRAPPER Wrapper for writing to robot via bluetooth
% 
% writeWrapper(byteArray,txLength,deviceName,channelNum)

    robot = comms.Bt(deviceName,channelNum);
    robot.write(byteArray,txLength);
end