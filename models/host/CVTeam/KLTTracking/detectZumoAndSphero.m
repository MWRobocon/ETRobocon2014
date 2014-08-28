function [CentroidZ, CentroidS] = detectZumoAndSphero(videoFrame)
% DETECTZUMOANDSPHERO detects Zumobot and Sphero in first frame, given in
% input videoFrame

%% run MatchWithTemplate to get ROI of zumobot
template = imread('media/Mario.jpg');
objectRegion = matchWithTemplate(videoFrame, template);
x = objectRegion(1);
y = objectRegion(2);
w = objectRegion(3);
h = objectRegion(4);

CentroidZ = [x+w/2, y+h/2];

%% Detect BLUE Sphero centroid (change code to make it yellow if you want)
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
    filteredSat = (saturation > threshSat);
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
    
    % Detect centers of blue and yellow spheros (alternative is blob Analysis)
    [CentersBlue] = imfindcircles(filteredBlue, [50 70], 'Sensitivity', 0.95);
    % viscircles(CentersBlue, RadiiBlue, 'EdgeColor', 'b');
    
    [CentersYellow] = imfindcircles(filteredYellow, [50 70], 'Sensitivity', 0.97);
    % viscircles(CentersYellow, RadiiYellow, 'EdgeColor', 'y');
    
    CentroidS = CentersBlue(1,:);