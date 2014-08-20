%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm
% It takes live feed from camera using imaq toolbox (webcam or videoinput
% object).

%% Setup System objects and variables

% vid = webcam;
% vid.Resolution = '960x720';
% vid = videoinput('winvideo', 1, 'RGB24_176x144');
vid = imaq.VideoDevice('winvideo', 1);
vid.VideoFormat = 'MJPG_960x720';
% vid = getselectedsource(vid);
% vid.FramesPerTrigger = 1;
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/MarioLiveFeedT.mp4', 'FileFormat', 'MPEG4');

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
[CalibratedImage, MingTForm] = imageCalibration(videoFrame);

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

%% Get features from template image (Option 2)
template = imread('media/Mario.jpg');
bwTemplate = rgb2gray(template);

% Region of interest = [xmin ymin width height]. hard coded for each image
% ROI = [200 130 210 200]; %For LomographyTemplate.jpg
% ROI = [84   139   480   205]; %For Gautam.jpg
ROI = [244 181 106 130]; %For Gautam.jpg 640 x 480
% ROI = [0 0 size(template,1) size(template,2)];
% imshow(template);
% disp('Select rectangular ROI for Template');
% ROI = round(getPosition(imrect));

pointsTemplate = detectSURFFeatures(bwTemplate); %, 'ROI', ROI);
imshow(template);
hold on;
plot(pointsTemplate);
title('Template image with detected features');

% Get objectRegion from features and RegionOfInterest of template (Option 2 continued)
sceneImage = rgb2gray(videoFrame);
boxImage = bwTemplate;
scenePoints = detectSURFFeatures(sceneImage);
boxPoints = pointsTemplate; %converting to variables of demo

% Extract features from both and match
[boxFeatures, boxPoints] = extractFeatures(boxImage, boxPoints);
[sceneFeatures, scenePoints] = extractFeatures(sceneImage, scenePoints);
boxPairs = matchFeatures(boxFeatures, sceneFeatures);

matchedBoxPoints = boxPoints(boxPairs(:, 1), :);
matchedScenePoints = scenePoints(boxPairs(:, 2), :);
[tform, inlierBoxPoints, inlierScenePoints] = estimateGeometricTransform(matchedBoxPoints, matchedScenePoints, 'affine');

figure;
showMatchedFeatures(boxImage, sceneImage, inlierBoxPoints, inlierScenePoints, 'montage');
title('Matched Points (Inliers Only)');

boxPolygon = [ROI(1), ROI(2); ... %top-left
    ROI(1)+ ROI(3), ROI(2); ... %top-right
    ROI(1)+ ROI(3), ROI(2)+ ROI(4); ... %bottom right
    ROI(1), ROI(2)+ ROI(4); ... bottom-left
    ROI(1), ROI(2)]; %top-left again to close the loop

newBoxPolygon = transformPointsForward(tform, boxPolygon);
figure; imshow(sceneImage);
hold on;
line(newBoxPolygon(:, 1), newBoxPolygon(:, 2), 'Color', 'y');
title('Detected Template');
xmax = max(newBoxPolygon(:,1));
ymax = max(newBoxPolygon(:,2));
xmin = min(newBoxPolygon(:,1));
ymin = min(newBoxPolygon(:,2));
w = xmax - xmin;
h = ymax - ymin;

objectRegion = uint16([xmin, ymin, w, h]); % Use this ROI to get features

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
%     botMean = mean(visiblePoints); % Mean of all visible features
% 
% %     position =  [50 50]; % [x y]
% %     videoFrame = insertText(videoFrame, position, int2str(botMean)); 
% 
%     % Show the centroids on the output video
%     videoFrame = insertMarker(videoFrame, botMean , 'x', 'Color', 'red', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, botMean2 , 'x', 'Color', 'red', 'Size', 5);
%     
%     % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
% step(videoWriter, videoFrame);
    TimePlayer(ii) = toc;
%     step(videoWriter, videoFrame);

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