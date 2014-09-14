function [speed, angle, dist] = control_sphero_motion(xdes, ydes, xcur, ycur, groundspeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed, clearvars)
%CONTROL_SPHERO_MOTION PID Controller for Sphero motion

persistent init prevu preve prevt prev2e prev2t

%% Clear variables if appropriate flag received
if clearvars
    clear init prevu preve prevt prev2e prev2t
    return
end

%% Angle and distance calculation
 
%Angle of desired position wrt y axis (or orientation of sphero)
angle = rad2deg(atan2(double(xdes-xcur), double(ydes-ycur)));
dist = pdist([xdes ydes; xcur ycur]); %Distance or the error

%% PID Control

% Initialize
if isempty(init)
    prevu = 0;
    preve = 0;
    prev2e = 0;
    prev2t = cputime;
    prevt = cputime;
    init = 1;
end

t = cputime;
dt = t-prevt;
dt2 = prevt-prev2t;
%Control
if dist<stopRadius
    u=0;
else
    if dt<eps || dt2<eps
        u = prevu+Kp*(dist-preve)+Ki*dt*dist;
    else
        u = prevu+Kp*(dist-preve)+Ki*dt*dist + Kd*((dist-preve)/dt - (preve-prev2e)/dt2);
    end
    
    if groundspeed<2 && u<restartspeed
        u = restartspeed;
    end
        
end

prevu = u;
prev2e = preve;
preve = dist;
prev2t = prevt;
prevt = t;

% Saturate
if u>maxspeed
    speed = maxspeed;
elseif u<minspeed
     speed = minspeed;
else
    speed = u;
end


end

