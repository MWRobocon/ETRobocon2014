function [CentroidZ, CentroidS, visiblePoints, threshold] = trackTwoMinions(videoFrame, varargin)
% DETECTZUMOANDSPHERO detects Zumobot and Sphero in first frame, given in
% input videoFrame
persistent blobAnalysis tracker tracker2 NFeaturesToTrack initFlag inlierThreshold;

if(nargin == 2)
    initFlag = varargin{1};
elseif (nargin > 2)
    initFlag = varargin{1};
    objectRegion = varargin{2};
    objectRegion2 = varargin{3};
    PolygonPoints = varargin{4};
    PolygonPoints2 = varargin{5};
end

NFeaturesToTrack = 50;
thresholdScale = 0.6;

%% Initialize
if(initFlag)
    
    blobAnalysis = vision.BlobAnalysis('AreaOutputPort', true,...
        'CentroidOutputPort', true,...
        'BoundingBoxOutputPort', true,...
        'MinimumBlobArea', 100, ...
        'ExcludeBorderBlobs', false);
    tracker = vision.PointTracker('MaxBidirectionalError', inf);
    tracker2 = vision.PointTracker('MaxBidirectionalError', inf);

%{    
try
[objectRegion, ~, PolygonPoints] = matchWithTemplate_SIFT(videoFrame, template);
[objectRegion2, ~, PolygonPoints2] = matchWithTemplate_SIFT(videoFrame, template2);
catch
   objectRegion = uint16([0 0 10 10]); %x y width hieight
   objectRegion2 = uint16([0 0 10 10]); %x y width hieight
   PolygonPoints = zeros(5,2);
   PolygonPoints2 = zeros(5,2);
end
    %}

PolygonPoints = PolygonPoints(1:4,:); %remove 5th(=1st) point
PolygonPoints2 = PolygonPoints2(1:4,:); %remove 5th(=1st) point


x = objectRegion(1);
y = objectRegion(2);
w = objectRegion(3);
h = objectRegion(4);

x2 = objectRegion2(1);
y2 = objectRegion2(2);
w2 = objectRegion2(3);
h2 = objectRegion2(4);

    
points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion);
points2 = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion2);

% videoFrameTemp = insertMarker(videoFrame, points.Location, '+', ...
%          'Color', 'yellow', 'Size', 5);
% videoFrameTemp = insertMarker(videoFrame, points2.Location, '+', ...
%          'Color', 'green', 'Size', 5);
%      figure; imshow(videoFrameTemp);
     
in = inpolygon(points.Location(:,1), points.Location(:,2),...
    PolygonPoints(:,1), PolygonPoints(:,2));
in2 = inpolygon(points2.Location(:,1), points2.Location(:,2),...
    PolygonPoints2(:,1), PolygonPoints2(:,2));

points = points(in, :); %get inliers only
points = points.selectStrongest(NFeaturesToTrack);

points2 = points2(in2, :); %get inliers only
points2 = points2.selectStrongest(NFeaturesToTrack);

videoFrameTemp = insertMarker(videoFrame, points.Location, '+', ...
         'Color', 'red', 'Size', 5);
videoFrameTemp = insertMarker(videoFrameTemp, points2.Location, '+', ...
         'Color', 'blue', 'Size', 5);     
figure; imshow(videoFrameTemp);

initialize(tracker, points.Location, videoFrame);
initialize(tracker2, points2.Location, videoFrame);

%% Get undistorted image
load('logitechCameraParams.mat');
% load('MSLifeCamParams.mat');
videoFrame = undistortImage(videoFrame, cameraParams, 'OutputView', 'full');
figure; imshow(videoFrame);
title('Undistorted Image');

CentroidZ(1,:) = [x+w/2, y+h/2];
CentroidZ(2,:) = [x2+w2/2, y2+h2/2];
inlierThreshold = single(thresholdScale*max(w,h));
threshold = inlierThreshold;
initFlag = 0; %done initialising
end

[points, isFound] = step(tracker,videoFrame);
visiblePoints = points(isFound, :);

[points2, isFound2] = step(tracker2,videoFrame);
visiblePoints2 = points2(isFound2, :);

CentroidZ = zeros([2,2],'single');
CentroidZ(1,:) = single(mean(visiblePoints)); % Sparse centroid of zumobot
CentroidZ(2,:) = single(mean(visiblePoints2)); % Sparse centroid of zumobot

inlier = isInlier(CentroidZ(1,:), visiblePoints, inlierThreshold);
disp(num2str(size(find(inlier),1)));
tracker.setPoints(visiblePoints, inlier);

%% Detect Sphero centroid (change code to make it yellow if you want)
    % Convert RGB to HSV, to get the saturation & hue value of each pixel.
    % Saturation can differentiate between colour and grayscale pixel. Hue can
    % differentiate between different colours (used for differentiating between
    % spheros)
    
    % Convert from RGB to HSV and get satutation, hue
    temp = rgb2hsv(videoFrame);
    saturation = temp(:,:,2);
    hue = temp(:,:,1);
    
    % Convert saturation into a binary
    threshSat = graythresh(saturation);
%     filteredSat = (saturation > threshSat);
    % figure; imshow(filteredSat);
    % title('Filtered Saturation');
    
    % If it's coloured and in yellow range of hue, then it's the yellow sphero
    % figure; imshow(hue)
    filteredYellow = (hue > 0.15 & hue < 0.25 & saturation > threshSat);
    % figure; imshow(filteredYellow)
    % title('Filtered Yellow');
    
    % If it's coloured and in blue range of hue, then it's the blue sphero
    filteredBlue = (hue > 0.50 & hue < 0.60 & saturation > threshSat);
    % figure; imshow(filteredBlue);
    % title('Filtered Blue');
    
    filteredOrange = (hue > 0 & hue < 0.05 & saturation > threshSat);
    
    % Find connected components
    [AreasBlue, CentersBlue, BoxBlue] = step(blobAnalysis, filteredBlue);
    [AreasYellow, CentersYellow, BoxYellow] = step(blobAnalysis, filteredYellow);
    [AreasOrange, CentersOrange, BoxOrange] = step(blobAnalysis, filteredOrange);
    % Detect centers of blue and yellow spheros (alternative is blob Analysis)
%     [CentersBlue] = imfindcircles(filteredBlue, [50 70], 'Sensitivity', 0.95);
    % viscircles(CentersBlue, RadiiBlue, 'EdgeColor', 'b');
%     [CentersYellow] = imfindcircles(filteredYellow, [50 70], 'Sensitivity', 0.97);
    % viscircles(CentersYellow, RadiiYellow, 'EdgeColor', 'y');
    
    try
        CentroidS = CentersOrange(1,:);
    catch
        CentroidS = [0 0];
    end