function dist = moveSpheroWebcamOriented(sph, xdes, ydes, x, y, clearVars)
%%% Assuming that the orientation of the sphero is initially along y
%%% direction (wrt camera)
persistent x0 t0 prevu preve prevt prev2e prev2t counter

if clearVars
    clear x0 t0 prevu preve prevt prev2e prev2t
    return
end

%% Controller Gains
Kp = 1;
Ki = 0;
Kd = 0;
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
end
 
t = cputime;

if dist<3
    u=0;
elseif counter<2
    u = prevu+Kp*(dist-preve)+Ki*(t-prevt)*dist;
else
%    u = Kp*dist;
   
    u = prevu+Kp*(dist-preve)+Ki*(t-prevt)*dist; % + Kd*((dist-preve)/(t-prevt) - (preve-prev2e)/(prevt-prev2t));
end

prevu = u;
prev2e = preve;
preve = dist;
prev2t = prevt;
prevt = t;
counter = counter+1;
%% Send command to sphero
roll(sph, u, angle);
