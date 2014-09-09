function [dist, angle, u] = moveSphero(sph, xdes, ydes, x, y, avgSpeed, stopRadius,clearVars)

%%% Assuming that the orientation of the sphero is initially along y
%%% direction (wrt camera)
persistent x0 t0 prevu preve prevt prev2e prev2t counter flag

if clearVars
    clear x0 t0 prevu preve prevt prev2e prev2t counter flag
    return
end

%% Controller Gains
Kp = 0.2;

if x<0 || y<0
    dist = Inf;
    return
end

Ki = 0.1;
Kd = 0.05;
speedIfSlow = 65;
% Tf = 0;
% tfinal = 60; %run the model for 1 minute


%% Angle and distance calculation
 
    %Angle of desired position wrt y axis (or orientation of sphero)
    angle = atan2(xdes-x, ydes-y);

    if angle<0
        angle = -angle;
    else
        angle = 2*pi-angle;
    end

    angle = rad2deg(angle);

dist = pdist([xdes ydes; x y]); %Distance or the error

% %% Controller
% C = pid(Kp, Ki, Kd, Tf);
% 
% if isempty(x0)
%     [speed, t, x0] = lsim(C, dist, t);
% end
%% 
if isempty(t0)
    t0 = cputime;
    prevu = 0;
    preve = 0;
    prev2e = 0;
    prevt = cputime;
    prev2t = cputime;
    counter = 0;
    flag = 0;
end
 
t = cputime;

% 
% if dist>50
%     Kp = 0.7;
% elseif dist>20
%     Kp = 2;
% else
%     Kp = 4;
% %     Kp = 1;
% % else
% %     Kp = 0.5;
% end


if dist<stopRadius || flag
    u=0;
%     flag = 1;
elseif avgSpeed<1
    u = speedIfSlow;
elseif counter<2
    u = prevu+Kp*(dist-preve)+Ki*(t-prevt)*dist;
else
%    u = Kp*dist;
   
    u = prevu+Kp*(dist-preve)+Ki*(t-prevt)*dist + Kd*((dist-preve)/(t-prevt) - (preve-prev2e)/(prevt-prev2t));
end

prevu = u;
prev2e = preve;
preve = dist;
prev2t = prevt;
prevt = t;
counter = counter+1;

%% Check value of u
% if u<60 && u>0
%     u=60;
% end

%% Send command to sphero

%Saturate
if u>150
    usend= 150;
elseif u<-150
    usend = -150;
else
    usend = u;
end

if usend==0
    brake(sph)
else
    roll(sph, usend, angle);
end