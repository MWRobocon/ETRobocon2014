%Version 4 in AH. Need to sync v3 from loaner laptop.
function [botData] = KLTBotTrackerFunctionWrapper()
%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm
% NEED TO UPDATE
% 1. Select initial area of interest in figure for now, automatically from
% calibrated setup in the competition

% 2. Detect nice features within the area of interest using the standard
% definition of good features (Shi and Tomasi). (detectMinEigenFeatures)
% Track these features using KLT tracking (vision.PointTracker)

% 3. When bot goes partially out of image and comes back, replenish the features by regrowing the box of interest

% 4. If it completely goes out of image and comes back, detect all corner
% features in the image. Then cluster the valid features using K-means
% algorithm

% 5. botMean returns the mean of all the features detected around the bot
% isBotinFrame is a 1x4 vector that becomes 0 if the feature rich region of the bot is close to within
% 10 pixels of the left, top, right and bottom borders respectively

% TO BE ADDED: i) Making the algorithm robust to addition of other objects
% ii) Extract Orientation information from features. Geometrically
% transform the bounding box if necessary.

%% Setup System objects and variables
persistent firstTime
persistent tracker r c oldPoints visiblePoints

videoFileReader = vision.VideoFileReader('media/Lomography240p.mp4');
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/Lomography240p_Tracked.mp4', 'FileFormat', 'MPEG4');

% Skip first few frames
numFramesToSkip = 0;
for i=1:numFramesToSkip
    step(videoFileReader);
end

videoFrame = step(videoFileReader);
r = size(videoFrame,1);
c = size(videoFrame,2);

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
% disp('Select rectangular ROI');
% objectRegion2 = round(getPosition(imrect));
% objectImage2 = insertShape(videoFrame,'Rectangle',objectRegion2);
% 
% 
% mode = 10;

%% Get features from template image (Option 2)
template = imread('media/LomographyTemplate.jpg');
bwTemplate = rgb2gray(template);
ROI = [200 130 210 200]; % Region of interest = [xmin ymin width height]. hard coded for each image
pointsTemplate = detectSURFFeatures(bwTemplate, 'ROI', ROI);
imshow(template);
hold on;
plot(pointsTemplate);

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
xmax = max(newBoxPolygon(:,1))
ymax = max(newBoxPolygon(:,2))
xmin = min(newBoxPolygon(:,1))
ymin = min(newBoxPolygon(:,2))
w = xmax - xmin
h = ymax - ymin

objectRegion = uint16([xmin, ymin, w, h]); % Use this to get SURFFeatures

mode = 11;

%% Get features within newly obtained objectRegion. Initialize tracker

points = detectSURFFeatures(sceneImage, 'ROI', objectRegion);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'white');

% x = objectRegion(1,1); y = objectRegion(1,2); w = objectRegion(1,3); h = objectRegion(1,4);
% bboxPolygon = [x, y, x+w, y, x+w, y+h, x, y+h];

% Make a copy of the points to be used for computing the geometric
% transformation between the points in the previous and the current frames
oldPoints = points.Location;

% Initialize tracker with given points and frame
tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, points.Location, videoFrame);

mode = 20; % mode = initializing

%% Track (and re-detect if necessary) for the whole video
% disp('Press any key to start tic-toc');
% pause;
% tic
while ~isDone(videoFileReader)
    videoFrame = step(videoFileReader);
    [points, isFound] = step(tracker,videoFrame);
    
    visiblePoints = points(isFound, :);
    
    xmin = round(min( visiblePoints(:,1))-5); ymax = round(max( visiblePoints(:,2)));
    xmax = round(max(visiblePoints(:,1))); ymin = round(min( visiblePoints(:,2))-5);
    scaleFactor = 1.36;
    captureFrame = round([xmin ymin scaleFactor*(xmax-xmin) scaleFactor*(ymax-ymin)]);
    
    if isempty(visiblePoints)
        isBotInFrame = [0 0 0 0];
    else
        isBotInFrame = [(xmin>10 && xmax>10) (ymin>10 && ymax>10) (xmin<c-10 && xmax<c-10) (ymin<r-10 && ymax<r-10)];
    end
    
    if size(visiblePoints, 1) >= 25 % need at least 25 points consistently
        
        % Reset the points, not necessary in this code
        % GS: Why reset points if you have 25+ visible points?
        %         oldPoints = visiblePoints;
        %         setPoints(tracker, oldPoints);
        mode = 21; %mode = tracking safely
    elseif size(visiblePoints, 1) >= 8 % atleast 8 points
        
        if xmin>0 && ymin>0 && scaleFactor*(xmax-xmin)+ xmin<c && scaleFactor*(ymax-ymin)+ ymin<r % if within image dimensions
            release(tracker);
            points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', captureFrame);
            points = points.Location;
            visiblePoints = points;
            oldPoints = points;
            initialize(tracker, points, videoFrame);
            mode = 22; %mode = tracking with difficulty
        end
        
    else
        
        points = detectMinEigenFeatures(rgb2gray(videoFrame));
        points = points.Location;
        [classifiedPoints,C] = kmeans(points,2,'distance','sqEuclidean','emptyaction','drop');
        points = points(logical(classifiedPoints-1),:);
        visiblePoints = points;
        oldPoints = points;
        
        xmin = round(min( visiblePoints(:,1))-5); ymax = round(max( visiblePoints(:,2)));
        xmax = round(max(visiblePoints(:,1))); ymin = round(min( visiblePoints(:,2))-5);
        
        if (xmax-xmin)*(ymax-ymin)<3600 %max threshold for num pixels in bot
            release(tracker);
            initialize(tracker, points, videoFrame);
            
        else
            visiblePoints = [];
            oldPoints = [];
        end
        mode = 23; %mode = unable to track, do setPoints() again
    end
    
    % Display tracked points
    if ~isempty(visiblePoints)
        videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
            'Color', 'white');
        videoFrame = insertShape(videoFrame,'rectangle', [xmin+5 ymin+5 xmax-xmin ymax-ymin]);
    end
    
    % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
    step(videoWriter, videoFrame);
    botMean = mean(visiblePoints); % Mean of all the features
    botData = [sum(isFound) botMean  isBotInFrame]; % Display num features and output for debugging
end
% toc

%% Release system objects
release(videoPlayer);
release(videoFileReader);
release(videoWriter);

mode = 30;

end