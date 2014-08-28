<<<<<<< HEAD
function writeWrapper(byteArray,txLength,deviceName,channelNum)
% WRITEWRAPPER Wrapper for writing to robot via bluetooth
% 
% writeWrapper(byteArray,txLength,deviceName,channelNum)

    robot = comms.Bt(deviceName,channelNum);
    robot.write(byteArray,txLength);
=======
function writeWrapper(robotId,byteArray,txLength)
% WRITEWRAPPER Wrapper for writing to robot via bluetooth
% 
% writeWrapper(byteArray,txLength,deviceName,channelNum)

    robot = comms.Bt(robotId);
    robot.write(byteArray,txLength);
>>>>>>> refs/remotes/origin/master
end