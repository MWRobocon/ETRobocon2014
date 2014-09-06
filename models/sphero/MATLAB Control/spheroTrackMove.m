function [distArr, posArr, angleArr] = spheroTrackMove(sphName, pos)

%% Move sphero to particular point, based on feedback from camera
try 
tfinal = 10;
xdes = pos(1);
ydes = pos(2);

vid = webcam(1);
start(vid);
sph = sphero(sphName);
% sph = sphero('Sphero-PGP');


sph.BackLEDBrightness = 255;

t0 = cputime;
posArr = [];
distArr = [];
angleArr = [];
while(cputime-t0<tfinal)
   pos = findBall(vid);
   xpos = pos(1);
   ypos = pos(2);
   
   if length(distArr)<=5
       avgSpeed = avg(distArr);
   else
       avgSpeed = mean(diff(distArr(end-5:end)));
   end
   
   [dist, angle, u] = moveSphero(sph, xdes, ydes, xpos, ypos, avgSpeed, 0);
    
   posArr(end+1, :) = pos;
   distArr(end+1) = dist;
   angleArr(end+1) = angle;
end

moveSphero(sph, 0, 0, 0, 0, 1);
stop(vid)
clear sph
catch exception
    moveSphero(sph, 0, 0, 0, 0, 1);
    if exist('sph', 'var')
        clear sph
    end
    if exist('vid', 'var')
        stop(vid);
    end
    throw(exception)
end