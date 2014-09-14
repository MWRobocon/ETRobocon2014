%% Getting Started with Sphero Connectivity Package
% This example shows how the Sphero Connectivity Package can be used to
% connect to a Sphero device and perform basic operations on the hardware,
% such as change the LED color, calibrate the orientation of the robot and
% move it in a particular direction.

%% Introduction
% The Sphero Connectivity Package enables us to communicate with a
% Sphero device remotely from a computer running MATLAB. The package
% includes command line interface to control the robotic ball.
%
% In this example we will learn how to create a *sphero* object to connect
% to the Sphero device from within MATLAB. We will examine the properties
% and methods of this object to control the robot and its peripherals.

%% Required Hardware
% To run this example, the following hardware is required:
%%
% * Sphero 2.0
% * Computer which is Bluetooth-capable, or a Bluetooth dongle 
% 
%% Setup hardware
% In order to connect to the Sphero, first make sure that
% the Sphero is awake and ready for connection. The following steps to set
% up the Sphero for connection can also be found in the Quick Start Guide
% that comes with the Sphero
%%
% <html>
% <ol type="1">
% <li> Connect the Charger to a wall socket</li>
% <li> Place the Sphero in the charger with its heavy part at the
% bottom.</li>
% <li> Remove the Sphero from the charger after it lights up after a few
% seconds. It will be asleep at after it is taken out from teh charger</li>
% <li>Double tap the Sphero with your fingers to wake it up</li>
% <li>The Sphero blinks 3 unique colors until it is connected to another
% device. Sphero's Bluetooth name will contain the initials of the 3 unique
% colors it is blinking with.
% <br>     R = RED
% <br>     B = BLUE
% <br>     G = GREEN
% <br>     Y = YELLOW
% <br>     O = ORANGE
% <br>     P = PURPLE
% <br>     W = WHITE
% <li> Pair the Sphero device with your phone, and launch the Sphero app. 
% This would automatically update the firmware on the device </li>
% <li> Turn on Bluetooth on your computer, and pair the Sphero to it. Once it
%  is paired, we can start using the Connectivity Package to communicate 
%  with the Sphero device</li>
% </ol>
% </html>
% 

%% Creating a sphero object
% Create a *sphero* object
sph = sphero();
%%
% The sph is a handle to a sphero object. While creating the sph object,
% MATLAB searches for the paired sphero devices and prompts the user to
% select one for connection. It then opens the Bluetooth connection with
% the Sphero. 
%%
% If you face any issues creating the sphero object, please
% refer to the <matlab:showdemo('sphero_troubleshoot_connection') Troubleshooting Connection Issues with Sphero> page.
% 
%%
% The properties of the sphero object show information such as the status of the
% connection and Bluetooth name of the connected device. It also has properties 
% that can be used to modify the color of the LED on the Sphero,
% the brightness of the back LED, timeouts for motion, response and 
% inactivity among other things.
%

%%
% <html><a id = "simple"></a></html>
%% Perform simple operations on Sphero
% The various methods of the sphero object can be used to perform different
% operations. The status of the Bluetooth connection can be checked by
% using the 'Status' property of the object:
s = sph.Status

%%
% We can also check whether the Sphero is able to receive and respond to
% messages by using the following command:
result = ping(sph)

%%
% If you receive an error when running these commands, please 
% refer to the <matlab:showdemo('sphero_troubleshoot_connection') 
% Troubleshooting Connection Issues with Sphero> page.

%%
% The Color of the LED on the Sphero, and the brightness of the back LED 
% can be changed by using the appropriate properties of the object
sph.Color = 'r'; % Change color of LED to red
sph.BackLEDBrightness = 255; %255 sets it to maximum brighness
%%
% <html> The back LED of the Sphero indicates the back of the Sphero. We will
% learn more about this in the <a href = "#move">Move Sphero </a>
% section.
% </html>
% 
%%
sph.Color = [127 127 127]; % A custom color can also be provided for the LED by specifying RGB values

%%
% <html><a id = "move"></a></html>
%% Move Sphero
% The sphero object provides basic commands for moving the Sphero. But
% before we start moving it, we need to make sure that the Sphero is
% oriented in the correct direction.
%%
% <html>
% The calibrate method can be used to calibrate the orientation of the
% Sphero. As mentioned in the <a href = "#simple">Perform simple operations 
% on Sphero</a> section, the back LED indicates the back of the robot. Thus
% the y-axis, 0 angle or the front of the robot is indicated by the
% direction opposite to the back LED.%</html>
%%
% Thus we would need to calibrate the orienatation of the robot so that its
% back is oriented towards you. The *calibrate* command might have to be used
% multiple times in order to fine tune and calibrate the robot's
% orientation
sph.BackLEDBrightness = 255; % turn on the back LED before we start calibrating the orientation of the robot

calibrate(sph, 60); % Observe that the sphero is going to rotate by 60 degrees and reset its orientation. 
% Run this command again with a different value for the angle if the back
% of the robot is not oriented towards you at present.

%%
% Once the robot is orientated properly, we can move it along a particular
% direction. Please note that all the 'angle' values that the following
% commands use are the angles from the original calibrated orientation of
% the robot
speed = 70;
angle = 0;

roll(sph, speed, angle);
%%
%Turn it by 90 degrees
roll(sph, speed, 90);

%%
% For all the aforementioned commands, we can turn on handshaking to make
% sure that the sphero is receiving and responding to the commands that are
% being sent to it
sph.Handshake = 1;

%%
% You will notice that the Sphero rolls in the particular direction for a
% small amount of time and then it stops automatically. This is due to the 
% MotionTimeout property of the object. The robot keeps moving until the 
% time in seconds that is specified by this property
sph.MotionTimeout = Inf; % Set the timeout for motion to infinity so that the robot keeps on moving unless a differnt move command is used
roll(sph, speed, angle);

pause(5); % Wait for 5 seconds and then brake the Sphero
brake(sph); 

%%
% There are other move commands such as *boost* or *rawMotor* which can be
% used to move the sphero with high speed and provide raw motor commands 
% to control the speed of the motors respectively

%% Read Sensor Data
% To read the data of a set of sensors from the Sphero, execute the command
% similar to the following.
[accX, accY, distX, distY] = readSensor(sph, {'accelX', 'accelY', 'distX', 'distY'});

%% 
% In order to read the value of a set of sensors at a particular rate, and
% save it to a MAT file, use the following command.
pollSensors(sph, 1, 'sensorname', {'accelX', 'accelY'}); %Poll accelerometer X and Y data at 1Hz

%% Disconnect or Make the Sphero go to Sleep
% We can disconnect from the Sphero by using the *disconnect* command. It
% is possible to reconnect to it again by using the *connect* command. If a different
% Sphero device name is specified as an input argument to the *connect*
% command, it will try to connect to the new device instead of the previous
% one. The *sleep* command can be used to force the currently connected
% Sphero to go to sleep

disconnect(sph);

connect(sph); % This would try to connect to the previously connected device, if it is awake
prevdevice = sph.DeviceName

sleep(sph);

connect(sph, 'Sphero-PGP'); % This would try to connect to the Sphero-PGP device, instead of the 'prevdevice'
newdevice = sph.DeviceName

%% See Also
% * <matlab:showdemo('sphero_troubleshoot_connection') Troubleshooting Connection Issues with Sphero>
% * <matlab:showdemo('sphero_motion_control') Sphero Motion Control>


