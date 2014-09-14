function [CentroidZ, CentroidS] = detectMinions2(videoFrame, varargin)
% DETECTZUMOANDSPHERO detects Zumobot and Sphero in first frame, given in
% input videoFrame
persistent blobAnalysis tracker NFeaturesToTrack initFlag;
if isempty(initFlag)
    initFlag = 1;
end
if (nargin == 2)
    initFlag = varargin{1};
end

NFeaturesToTrack = 50;

if(initFlag)
    
    blobAnalysis = vision.BlobAnalysis('AreaOutputPort', true,...
        'CentroidOutputPort', true,...
        'BoundingBoxOutputPort', true,...
        'MinimumBlobArea', 100, ...
        'ExcludeBorderBlobs', false);
    tracker = vision.PointTracker('MaxBidirectionalError', 3);
    
%% run MatchWithTemplate to get ROI of zumobot
template = imread('media/Mario.jpg');

try
objectRegion = matchWithTemplate_SIFT(videoFrame, template);
catch exception
    rethrow(exception)
   objectRegion = uint16([0 0 10 10]);
end

x = objectRegion(1);
y = objectRegion(2);
w = objectRegion(3);
h = objectRegion(4);

points = detectMinEigenFeatures(rgb2gray(videoFrame), 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);

initialize(tracker, points.Location, videoFrame);
CentroidZ = [x+w/2, y+h/2];
initFlag = 0; %done initialising
end

[points, isFound] = step(tracker,videoFrame);
visiblePoints = points(isFound, :);
CentroidZ = mean(visiblePoints); % Sparse centroid of zumobot

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
    if isempty(CentersOrange)
        CentroidS = [-1 -1];
    else
        CentroidS = CentersOrange(1,:);
    end
    
    if isempty(CentersBlue)
        CentroidB = [-1 -1];
    else
        