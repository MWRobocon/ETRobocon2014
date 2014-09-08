function RecognitionAndTrack()

while true

    % videoinput is much slower than imaq.VideoDevice
    % videoObj = videoinput('winvideo', 1, 'MJPG_960x720');
    % frame0 = getsnapshot(videoObj);
    
    videoObj = imaq.VideoDevice('winvideo', 1, 'MJPG_960x720');
    frame0 = step(videoObj);
    videoObj.release;
    
    imshow(frame0);

    % Feature detection to detect all the known objects. 
    % The output is the central location of the object.
    [CentroidZ, CentroidS] = detectZumoAndSphero(frame0);

    locations(1).name = 'ZumoRobot';
    locations(1).centroid = CentroidZ/6; % Convert 960x720 to 160x120
    locations(2).name = 'Sphero';
    locations(2).centroid = CentroidS/6;

    % Object tracking for 100 frames
    multiObjectTracking(locations);

end

end