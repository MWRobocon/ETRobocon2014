%% Move sphero to particular point, based on feedback from camera
tfinal = 10;
xdes = 200;
ydes = 150;

vid = webcam(2);
start(vid);
% sph = sphero('Sphero-GPG');
% sph = sphero('Sphero-PGP');


sph.BackLEDBrightness = 255;

t0 = cputime;
posArr = [];
distArr = [];
while(cputime-t0<tfinal)
   pos = findBall(vid);
   xpos = pos(1);
   ypos = pos(2);
   
   dist = moveSphero(sph, xdes, ydes, xpos, ypos, 0);
    
   posArr(end+1, :) = pos;
   distArr(end+1) = dist;
end

moveSphero(sph, 0, 0, 0, 0, 1);
stop(vid)
% clear sph