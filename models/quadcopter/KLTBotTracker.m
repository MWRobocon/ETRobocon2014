function [botMean] = KLTBotTracker(videoFrame1)
%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm

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

%% Step 1: Select the Bot
persistent selectBounds;
persistent objectRegion;
persistent tracker;
% persistent videoPlayer;
% persistent 

videoFrame(:, :, 1) = videoFrame1;
videoFrame(:, :, 2) = videoFrame1;
videoFrame(:, :, 3) = videoFrame1;

% Read a video frame and run the detector.
% videoFileReader = vision.VideoFileReader('natickTrial7.mp4');
% videoPlayer = vision.VideoPlayer();
% videoFrame = step(videoFileReader);
if isempty(selectBounds)
    figure; imshow(videoFrame); title('Yellow box shows object region');
    objectRegion=round(getPosition(imrect));
    %     objectImage = insertShape(videoFrame,'Rectangle',objectRegion);
    selectBounds = true;
    

    
    %% Get the point features
    points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion);
    % pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'white');
%     figure, imshow(pointImage), title('Detected interest points');
    
%     x = objectRegion(1,1); y = objectRegion(1,2); w = objectRegion(1,3); h = objectRegion(1,4);
%     bboxPolygon = [x, y, x+w, y, x+w, y+h, x, y+h];
    
    % Make a copy of the points to be used for computing the geometric
    % transformation between the points in the previous and the current frames
%     oldPoints = points.Location;
%     mode = 0;
    %% Set up point tracker
    tracker = vision.PointTracker('MaxBidirectionalError', 3);
    initialize(tracker, points.Location, videoFrame);
end

    r = size(videoFrame,1);
    c = size(videoFrame,2);

% while ~isDone(videoFileReader)
%     videoFrame = step(videoFileReader);
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
        oldPoints = visiblePoints;
        setPoints(tracker, oldPoints);
        mode = 1;
    elseif size(visiblePoints, 1) >= 8 % atleast 8 points
        
        if xmin>0 && ymin>0 && scaleFactor*(xmax-xmin)+ xmin<c && scaleFactor*(ymax-ymin)+ ymin<r % if within image dimensions
            release(tracker);
            points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', captureFrame);
            points = points.Location;
            visiblePoints = points;
            oldPoints = points;
            initialize(tracker, points, videoFrame);
            mode = 2;
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
        mode = 3;
    end
    
    % Display tracked points
    if ~isempty(visiblePoints)
%         videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
%             'Color', 'white');
%         videoFrame = insertShape(videoFrame,'rectangle', [xmin+5 ymin+5 xmax-xmin ymax-ymin]);
    end
    
    % Display the annotated video frame using the video player object
%     step(videoPlayer, videoFrame);
    botMean = mean(visiblePoints); % Mean of all the features
%     pause(0.05);
%     disp([sum(isFound) botMean  isBotInFrame]); % Display num features and output for debugging
% end


if isnan(botMean)
    botMean = [0 0];
end

%%
% release(videoPlayer);
% release(videoFileReader);


