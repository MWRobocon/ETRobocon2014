%% Sphero Motion Control
% This example shows you how to control the motion of a Sphero using the 
% Sphero Connectivity Package
%% Introduction
% In this example, you will use the data received from the onboard sensors
% of the Sphero to perform closed loop control of the motion of the Sphero.
% We will provide a set of points that we want the Sphero to pass through. 
% The data from the sensors will be used to estimate the current position 
% of the Sphero, which is used by the controller to compute the speed and
% angle to which the Sphero will be commanded to
%
%% Prerequisites
% It is helpful to complete the <matlab:showdemo('sphero_getting_started') Getting Started with Sphero
% Connectivity Package> example
%
%% Connect to Sphero
sph = sphero();
result = ping(sph);
%%
% You can specify the Bluetooth name of the device that you would like to
% connect to, instead of searching for all the paired devices.
%%
% Turn on handshaking in order to make sure that the Sphero is able to 
% receive and respond to messages. And calibrate the orientation of the
% Sphero so that it points in the desired direction, before we start moving
% it around
sph.Handshake = 1;  %Turn on handshaking 
calibrate(sph, 0); %Calibrate the orientation of the sphero

%% Speify the points to be traversed
load('path2.mat');

listnum = length(xdeslist);

% Specify the other parameters that are used in controlling the Sphero
tfinal = 60;
stopRadius = 3; 
maxspeed = 150; minspeed = -150; restartspeed = 50;

Kp = 1; Ki = 0.1; Kd = 0.1;
% xdes = -20; ydes = 100;



% xdeslist = posdes(:, 1);
% ydeslist = posdes(:, 2);



% t = 0:100;




[x, y, ~, ~, groundspeed] = readLocator(sph);
% prevt = 0;

distarr = []; xlog = []; ylog = []; speedarr = [];

xdes = xdeslist(1);
ydes = ydeslist(1);
control_sphero_motion(xdes, ydes, x, y, groundspeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed, 1);

figure(1)
clf
hold on
plot(x, y, 'r*')
plot(xdeslist, ydeslist, 'kx')
hold off

speed = [];
dist = pdist([xdes ydes; x y]); %Distance or the error

t0 = cputime;
while(cputime-t0<tfinal) && idx<=listnum
xdes = xdeslist(idx);
ydes = ydeslist(idx);
dist = pdist([xdes ydes; x y]); %Distance or the error

control_sphero_motion(xdes, ydes, x, y, groundspeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed, 1);

while dist>stopRadius %|| speed~=0
%     if t>5
%         keyboard
%     end
    
    
    [speed, angle, dist] = control_sphero_motion(xdes, ydes, x, y, groundspeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed, 0);
    
    result = roll(sph, speed, angle);
    
    

%     x = x + speed*(t-prevt)*sin(angle)*0.7;
%     y = y + speed*(t-prevt)*cos(angle)*0.7;
    
%     prevt = t;
%     plot(x, y, 'r*')

    [x, y,~, ~, groundspeed] = readLocator(sph);
    dist = pdist(double([xdes ydes; x y])); %Distance or the error
    xlog(end+1) = x;
    ylog(end+1) = y;
    distarr(end+1) = dist;
    speedarr(end+1) = speed;
    
    
    
end
idx = idx+1;
end
roll(sph, 0, angle)
% brake(sph);

[x, y] = readLocator(sph);
distend = pdist([xdes ydes; x y]); %Distance or the error

hold on
plot(xlog, ylog, 'r*');
hold off

figure(2)
plot(distarr)

control_sphero_motion(xdes, ydes, x, y, groundspeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed, 1);

    
sleep(sph);
clear sph