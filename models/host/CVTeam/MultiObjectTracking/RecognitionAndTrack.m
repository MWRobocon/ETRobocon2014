function RecognitionAndTrack()

videoObj = videoinput('winvideo', 1, 'MJPG_640x480');

frame0 = getsnapshot(videoObj);
imshow(frame0);

[CentroidZ, CentroidS] = detectZumoAndSphero(frame0);

locations(1).name = 'ZumoRobot';
locations(1).centroid = CentroidZ;
locations(2).name = 'Sphero';
locations(2).centroid = CentroidS;

multiObjectTracking(locations);

end