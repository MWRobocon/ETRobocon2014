%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm
% It takes live feed from camera using imaq toolbox (webcam or videoinput
% object).

%% Setup System objects and variables

% vid = webcam;
% vid.Resolution = '960x720';
% vid = videoinput('winvideo', 1, 'RGB24_176x144');
vid = imaq.VideoDevice('winvideo', 1);
% vid.VideoFormat = 'MJPG_1280x720';
vid.VideoFormat = 'MJPG_640x480';
% vid = getselectedsource(vid);
% vid.FramesPerTrigger = 1;
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/MarioLiveFeedT.mp4', 'FileFormat', 'MPEG4');
% load('MSLifeCamParams.mat');
load('logitechCameraParams.mat');
magnification = 25;
NFeaturesToTrack = 50; % Track strongest N features
NFrame = 800; % Number of frames
% numFramesToSkip = 0; % Skip first few frames
% 
% for i=1:numFramesToSkip
%     step(videoFileReader);
% end

disp('Press any key when you are ready for first frame capture');
pause;

% Why are all of these different! usability
% videoFrame = step(videoFileReader); %for video file reader object
% videoFrame = getsnapshot(vid); %for videoinput object
% videoFrame = snapshot(vid); %for webcam object
videoFrame = step(vid);
r = size(videoFrame,1);
c = size(videoFrame,2);
% [CalibratedImage, MingTForm] = imageCalibration(videoFrame);
% warpedImage = imwarp(videoFrame, MingTForm);
% figure; imshow(warpedImage);
% Get objectRegion from features and ROI of template (for Option 2)
sceneImage = rgb2gray(videoFrame);
% boxImage = rgb2gray(template);
scenePoints = detectSURFFeatures(sceneImage);
% boxPoints = pointsTemplate; %converting to variables of demo

mode = 0;

%% Read a video frame and run the detector (Option 1)
% figure; 
% imshow(videoFrame); 
% 
% % Draw a rectangle around the region of interest, and track it
% disp('Select rectangular ROI');
% objectRegion=round(getPosition(imrect));
% objectImage = insertShape(videoFrame,'Rectangle',objectRegion);
% 
% mode = 10;

%% Run matchWithTemplate function
template = imread('media/Mario.jpg');
objectRegion = matchWithTemplate(videoFrame, template);

mode = 11;

%% Get features within newly obtained objectRegion. Initialize tracker

points = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'yellow');

% Make a copy of the points to be used for computing the geometric
% transformation between the points in the previous and the current frames
oldPoints = points.Location;

% Initialize tracker with given points and frame
tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, points.Location, videoFrame);

mode = 20; % mode = initializing

%% Get undistorted image
[im, newOrigin] = undistortImage(videoFrame, cameraParams, 'OutputView', 'full');
figure; imshow(im, 'InitialMagnification', magnification);
title('Undistorted Image');

% Compute extrinsics
% Both imagePoints and boardSize don't change if the checkerboard stays
% where it is during the video
[imagePoints, boardSize] = detectCheckerboardPoints(im);

% Compute rotation and translation of the camera.
[R, t] = extrinsics(imagePoints, cameraParams.WorldPoints, cameraParams);

%% Track (and re-detect if necessary) for the whole video
disp('Press any key to start tic-toc');
pause;

TimeReader = zeros(NFrame,1);
TimeTracker = zeros(NFrame,1);
TimePlayer = zeros(NFrame,1);

tstart = clock;
% tic
% while ~isDone(videoFileReader)
for ii = 1:NFrame
    
    tic
    % Get next frame of vide/camera
%     videoFrame = step(videoFileReader);
%     videoFrame = getsnapshot(vid);
% videoFrame = snapshot(vid);
videoFrame = step(vid);
% videoFrame = imwarp(videoFrame, MingTForm);
    TimeReader(ii) = toc;
    
    % Track features in the new frame
    [points, isFound] = step(tracker,videoFrame);
    TimeTracker(ii) = toc;   
    
    % Get array of visible points
    visiblePoints = points(isFound, :);
    
    % Display tracked points
    if ~isempty(visiblePoints)
        videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
            'Color', 'green', 'Size', 5);
    end
%     

    botMean = mean(visiblePoints); % Mean of all visible features
%     TBotMean = transformPointsForward(MingTForm, botMean);

    % Get the world coordinates of the centroid
    worldCentroid = pointsToWorld(cameraParams, R, t, botMean);
    
    position =  [50 50]; % [x y]
    videoFrame = insertText(videoFrame, position, int2str(worldCentroid));
 
    % Show the points on the output video
    videoFrame = insertMarker(videoFrame, botMean , 'x', 'Color', 'red', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, botMean2 , 'x', 'Color', 'red', 'Size', 5);
%     
%     % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
% step(videoWriter, videoFrame);
    TimePlayer(ii) = toc;
%     step(videoWriter, videoFrame);

% img = step(vid);
% imshow(img)
temp = rgb2hsv(videoFrame);
saturation = temp(:,:,2);
thresh = graythresh(saturation);
filtered = (saturation > thresh);
% imshow(filtered);
blobAnalysis = vision.BlobAnalysis('AreaOutputPort', true,...
'CentroidOutputPort', true,...
'BoundingBoxOutputPort', true,...
'MinimumBlobArea', 200);
[areas, boxes] = step(blobAnalysis, filtered);

end
% tend = toc;
tLoop = etime(clock, tstart)

%% Release system objects
release(videoPlayer);
% release(videoFileReader);
release(videoWriter);
% release(vid);
clear vid;

mode = 30;

Timing = struct('TimeReader', TimeReader, 'TimeTracker', (TimeTracker - TimeReader), 'TimePlayer', (TimePlayer - TimeTracker));
figure
plot(1:NFrame, Timing.TimeReader, 1:NFrame,Timing.TimeTracker,1:NFrame, Timing.TimePlayer);
title('Timing for Reader, Tracker, Player');
legend('TimeReader', 'TimeTracker', 'TimePlayer');

figure
plot(1:NFrame, Timing.TimeReader, 1:NFrame, (Timing.TimeReader + Timing.TimeTracker));
legend('Reader', 'Reader + Tracker');
title('Timing for Reader, Reader+Tracker');

% Avg computation time with reader and tracker ONLY; display not counted
% removing initial overhead of first few frames. this is steady state avg
AvgComputationPerFrame = sum(Timing.TimeReader(21:end) + Timing.TimeTracker(21:end))/(NFrame-20)

% Computational fps for reading and tracking ONLY
ComputationFrameRate = 1/AvgComputationPerFrame