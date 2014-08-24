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
videoObj.release;