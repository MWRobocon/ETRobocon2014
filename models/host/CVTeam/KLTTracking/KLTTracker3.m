% function [botData, videoFrame] = KLTBotTrackerFunctionWrapper()
function [botData] = KLTBotTrackerFunctionWrapper()

%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm
% GS: NEED TO UPDATE
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

%% Setup variables and system objects
persistent firstTime
persistent tracker r c oldPoints visiblePoints

videoFileReader = vision.VideoFileReader('media/Lomography240p.mp4');
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/Lomography240p_Tracked.mp4', 'FileFormat', 'MPEG4');

% Skip first few frames (for initial camera/scene adjustment, if needed)
numFramesToSkip = 0;
for i=1:numFramesToSkip
    step(videoFileReader);
end

videoFrame = step(videoFileReader);
% Get frame dimensions
r = size(videoFrame,1);
c = size(videoFrame,2);

mode = 0; % mode of simulation. can be used as debug flag

% %% Read a video frame and run detector (Option 1)
% 
% figure;
% imshow(videoFrame); 
% title('Yellow box shows object region');
% 
% % Ask user to draw a rectangle around the region of interest
% objectRegion = round(getPosition(imrect));
% objectImage = insertShape(videoFrame,'Rectangle',objectRegion);
% 
% % Get the point features in region of interest
% points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion);
% 
% mode = 10;

%% Get points from template image (Option 2)

% Use template image with pre-decided region of interest
template = imread('media/LomographyTemplate.jpg');
templateBW = rgb2gray(template);
objectRegion = [200 130 210 200]; % [x y width height]. hard coded for a given template image

% Detect points and show them
% Note: pointsTemplate is different from points. pointsTemplate is for
% point locations in template image, which have diff dimensions than video
pointsTemplate = detectMinEigenFeatures(templateBW, 'ROI', objectRegion);
imshow(template);
hold on
plot(pointsTemplate);

mode = 11;

%% Plot detected points

% Need to match features from template to image, and get points.Location
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'white');
figure;
imshow(pointImage); 
title('Detected interest points');

% vectorize this
x = objectRegion(1,1); y = objectRegion(1,2); w = objectRegion(1,3); h = objectRegion(1,4);
bboxPolygon = [x, y, x+w, y, x+w, y+h, x, y+h];

% Make a copy of the points to be used for computing the geometric
% transformation between the points in the previous and the current frames
oldPoints = points.Location;

mode = 20; % mode = initializing

%% Set up point tracker
tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, points.Location, videoFrame);
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
%     step(videoWriter, videoFrame);
    botMean = mean(visiblePoints); % Mean of all the features
    botData = [sum(isFound) botMean  isBotInFrame]; % Display num features and output for debugging
end
% toc
release(videoPlayer);
release(videoFileReader);
release(videoWriter);

mode = 30;
end