%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm
% NEED TO UPDATE
%  
% 1. Select initial area of interest in figure for now, automatically from
% calibrated setup in the competition
%
% 2. Detect nice features within the area of interest using the standard
% definition of good features (Shi and Tomasi). (detectMinEigenFeatures)
% Track these features using KLT tracking (vision.PointTracker)
%
% 3. When bot goes partially out of image and comes back, replenish the features by regrowing the box of interest
%
% 4. If it completely goes out of image and comes back, detect all corner
% features in the image. Then cluster the valid features using K-means
% algorithm
%
% 5. botMean returns the mean of all the features detected around the bot
% isBotinFrame is a 1x4 vector that becomes 0 if the feature rich region of the bot is close to within
% 10 pixels of the left, top, right and bottom borders respectively
%
% TO BE ADDED: i) Making the algorithm robust to addition of other objects
% ii) Extract Orientation information from features. Geometrically
% transform the bounding box if necessary.

%% Setup System objects and variables
videoFileReader = vision.VideoFileReader('media/BookAndPouch720p.mp4');
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/BookAndPouch720p_Tracked.mp4', 'FileFormat', 'MPEG4');

NFeaturesToTrack = 100; % Track strongest N features
numFramesToSkip = 0; % Skip first few frames

for i=1:numFramesToSkip
    step(videoFileReader);
end

videoFrame = step(videoFileReader);
r = size(videoFrame,1);
c = size(videoFrame,2);

% Get objectRegion from features and ROI of template (for Option 2)
sceneImage = rgb2gray(videoFrame);
% boxImage = rgb2gray(template);
scenePoints = detectMinEigenFeatures(sceneImage);
% boxPoints = pointsTemplate; %converting to variables of demo

mode = 0;

%% Read a video frame and run the detector (Option 1)
figure; 
imshow(videoFrame); 

% Draw a rectangle around the region of interest, and track it
disp('Select rectangular ROI');
objectRegion=round(getPosition(imrect));
objectImage = insertShape(videoFrame,'Rectangle',objectRegion);

mode = 10;

%% Use drawing technique for second object. For now.
figure; 
imshow(videoFrame); 
disp('Select rectangular ROI');
objectRegion2 = round(getPosition(imrect));
objectImage2 = insertShape(videoFrame,'Rectangle',objectRegion2);

%% Get features from template image (Option 2)
% template = imread('media/LomographyTemplate.jpg');
% bwTemplate = rgb2gray(template);
% ROI = [200 130 210 200]; % Region of interest = [xmin ymin width height]. hard coded for each image
% pointsTemplate = detectMinEigenFeatures(bwTemplate, 'ROI', ROI);
% imshow(template);
% hold on;
% plot(pointsTemplate);
% 
% % Get objectRegion from features and RegionOfInterest of template (Option 2 continued)
% sceneImage = rgb2gray(videoFrame);
% boxImage = bwTemplate;
% scenePoints = detectMinEigenFeatures(sceneImage);
% boxPoints = pointsTemplate; %converting to variables of demo
% 
% % Extract features from both and match
% [boxFeatures, boxPoints] = extractFeatures(boxImage, boxPoints);
% [sceneFeatures, scenePoints] = extractFeatures(sceneImage, scenePoints);
% boxPairs = matchFeatures(boxFeatures, sceneFeatures);
% 
% matchedBoxPoints = boxPoints(boxPairs(:, 1), :);
% matchedScenePoints = scenePoints(boxPairs(:, 2), :);
% [tform, inlierBoxPoints, inlierScenePoints] = estimateGeometricTransform(matchedBoxPoints, matchedScenePoints, 'affine');
% 
% figure;
% showMatchedFeatures(boxImage, sceneImage, inlierBoxPoints, inlierScenePoints, 'montage');
% title('Matched Points (Inliers Only)');
% 
% boxPolygon = [ROI(1), ROI(2); ... %top-left
%     ROI(1)+ ROI(3), ROI(2); ... %top-right
%     ROI(1)+ ROI(3), ROI(2)+ ROI(4); ... %bottom right
%     ROI(1), ROI(2)+ ROI(4); ... bottom-left
%     ROI(1), ROI(2)]; %top-left again to close the loop
% 
% newBoxPolygon = transformPointsForward(tform, boxPolygon);
% figure; imshow(sceneImage);
% hold on;
% line(newBoxPolygon(:, 1), newBoxPolygon(:, 2), 'Color', 'y');
% title('Detected Template');
% xmax = max(newBoxPolygon(:,1));
% ymax = max(newBoxPolygon(:,2));
% xmin = min(newBoxPolygon(:,1));
% ymin = min(newBoxPolygon(:,2));
% w = xmax - xmin;
% h = ymax - ymin;
% 
% objectRegion = uint16([xmin, ymin, w, h]); % Use this ROI to get features
% 
% mode = 11;

%% Get features within newly obtained objectRegion. Initialize tracker

points = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'yellow');

points2 = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion2);
points2 = points2.selectStrongest(NFeaturesToTrack);
pointImage2 = insertMarker(videoFrame, points2.Location, '+', 'Color', 'blue');

% Make a copy of the points to be used for computing the geometric
% transformation between the points in the previous and the current frames
oldPoints = points.Location;

% Initialize tracker with given points and frame
tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, points.Location, videoFrame);

tracker2 = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker2, points2.Location, videoFrame);

mode = 20; % mode = initializing

%% Track (and re-detect if necessary) for the whole video
disp('Press any key to start tic-toc');
pause;

NFrame = 810;
TimeReader = zeros(NFrame,1);
TimeTracker = zeros(NFrame,1);
TimePlayer = zeros(NFrame,1);

tstart = clock;
% tic
% while ~isDone(videoFileReader)
for ii = 1:NFrame
    
    tic
    % Get next frame of vide/camera
    videoFrame = step(videoFileReader);
    TimeReader(ii) = toc;
    
    % Track features in the new frame
    [points, isFound] = step(tracker,videoFrame);
    [points2, isFound2] = step(tracker2,videoFrame);
    TimeTracker(ii) = toc;   
    
%     % Get array of visible points
%     visiblePoints = points(isFound, :);
%     visiblePoints2 = points2(isFound2, :);
%     
%     % Display tracked points
%     if ~isempty(visiblePoints)
%         videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
%             'Color', 'white');
%     end
%     
%     if ~isempty(visiblePoints2)
%         videoFrame = insertMarker(videoFrame, visiblePoints2, '+', ...
%             'Color', 'yellow');
%     end
%     
%     botMean = mean(visiblePoints); % Mean of all visible features
%     botMean2 = mean(visiblePoints2); % Mean of all visible features
% 
% %     position =  [50 50]; % [x y]
% %     position2 =  [50 70]; % [x y]
% %     videoFrame = insertText(videoFrame, position, int2str(botMean)); 
% %     videoFrame = insertText(videoFrame, position2, int2str(botMean2)); 
% 
%     % Show the centroids on the output video
%     videoFrame = insertMarker(videoFrame, botMean , 'x', 'Color', 'red', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, botMean2 , 'x', 'Color', 'red', 'Size', 5);
%     
%     % Display the annotated video frame using the video player object
%     step(videoPlayer, videoFrame);
    TimePlayer(ii) = toc;
%     step(videoWriter, videoFrame);

end
% tend = toc;
tLoop = etime(clock, tstart)

%% Release system objects
release(videoPlayer);
release(videoFileReader);
release(videoWriter);

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