<<<<<<< HEAD
% videoObj = imaq.VideoDevice('winvideo', 1);
videoObj = videoinput('winvideo', 1, 'MJPG_640x480');
videoObj.DeviceProperties.FrameRate = '5';
frame0 = step(videoObj);
while true
    tic;
    frame1 = step(videoObj);
    if frame0 == frame1
        disp('hello');
    else
        disp('world');
    end
    frame0 = frame1;
    toc;
   % preview(frame);
end
=======
videoObj = imaq.VideoDevice('winvideo', 1);
videoObj.DeviceProperties.FrameRate = '5';
frame0 = step(videoObj);
while true
    tic;
    frame1 = step(videoObj);
    if frame0 == frame1
        disp('hello');
    else
        disp('world');
    end
    frame0 = frame1;
    toc;
   % preview(frame);
end
>>>>>>> 49348b51a63c56d87ba47b68ef106e265e871506
videoObj.release;