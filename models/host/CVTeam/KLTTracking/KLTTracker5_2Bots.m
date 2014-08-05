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

videoFileReader = vision.VideoFileReader('media/Lomography480p.mp4');
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/Lomography480p_Tracked.mp4', 'FileFormat', 'MPEG4');

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
figure; 
imshow(videoFrame); 

% Draw a rectangle around the region of interest, and track it
disp('Select rectangular ROI');
objectRegion=round(getPosition(imrect));
objectImage = insertShape(videoFrame,'Rectangle',objectRegion);

disp('Select rectangular ROI');
objectRegion2 = round(getPosition(imrect));
objectImage2 = insertShape(videoFrame,'Rectangle',objectRegion2);


mode = 10;

%% Get features from template image (Option 2)
% template = imread('media/LomographyTemplate.jpg');
% bwTemplate = rgb2gray(template);
% RegionOfInterest = [200 130 210 200]; % hard coded for each image
% pointsTemplate = detectMinEigenFeatures(bwTemplate, 'ROI', RegionOfInterest);
% imshow(template);
% hold on;
% plot(pointsTemplate);
% 
% % TODO: get objectRegion from features and RegionOfInterest of template
% 
% mode = 11;

%% Get the point features

points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'white');
figure; 
imshow(pointImage); 
title('Detected interest points. Yellow box shows object region');
% hold on;

x = objectRegion(1,1); y = objectRegion(1,2); w = objectRegion(1,3); h = objectRegion(1,4);
bboxPolygon = [x, y, x+w, y, x+w, y+h, x, y+h];

points2 = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion2);
pointImage2 = insertMarker(videoFrame, points2.Location, '+', 'Color', 'yellow');
figure;
imshow(pointImage2);

x2 = objectRegion(1,1); y2 = objectRegion(1,2); w2 = objectRegion(1,3); h2 = objectRegion(1,4);
bboxPolygon2 = [x2, y2, x2+w2, y2, x2+w2, y2+h2, x2, y2+h2];


% Make a copy of the points to be used for computing the geometric
% transformation between the points in the previous and the current frames
oldPoints = points.Location;
oldPoints2 = points2.Location;

mode = 20; % mode = initializing

%% Set up point tracker
tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, points.Location, videoFrame);

tracker2 = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker2, points2.Location, videoFrame);

%% Track (and re-detect if necessary) for the whole video
% disp('Press any key to start tic-toc');
% pause;
% tic
while ~isDone(videoFileReader)
    videoFrame = step(videoFileReader);
    [points, isFound] = step(tracker,videoFrame);
    [points2, isFound2] = step(tracker2,videoFrame);
        
    visiblePoints = points(isFound, :);
    visiblePoints2 = points2(isFound2, :);
    
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
    
    if ~isempty(visiblePoints2)
        videoFrame = insertMarker(videoFrame, visiblePoints2, '+', ...
            'Color', 'yellow');
%         videoFrame = insertShape(videoFrame,'rectangle', [xmin+5 ymin+5 xmax-xmin ymax-ymin]);
    end
    
    % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
%     step(videoWriter, videoFrame);
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