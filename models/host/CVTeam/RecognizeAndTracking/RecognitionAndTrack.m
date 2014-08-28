function RecognitionAndTrack()

videoObj = videoinput('winvideo', 1, 'MJPG_960x720');
% preview(videoObj);
frame0 = getsnapshot(videoObj);
% videoObj = imaq.VideoDevice('winvideo', 1, 'MJPG_1280x720');
% frame0 = step(videoObj);
imshow(frame0);
% videoObj.release;

[CentroidZ, CentroidS] = detectZumoAndSphero(frame0);

locations(1).name = 'ZumoRobot';
locations(1).centroid = CentroidZ/6; % Convert 960x720 to 160x120
locations(2).name = 'Sphero';
locations(2).centroid = CentroidS/6;

multiObjectTracking(locations);

end