%% Tracking an interesting part of the BOT using the Kanade-Lucas-Tomasi algorithm

%% Setup System objects and variables
NFeaturesToTrack = 50; % Track strongest N features

% TODO: Define RGB videoFrame here

% Get objectRegion from features and ROI of template (for Option 2)
sceneImage = rgb2gray(videoFrame);
% boxImage = rgb2gray(template);
scenePoints = detectMinEigenFeatures(sceneImage);
% boxPoints = pointsTemplate; %converting to variables of demo

mode = 0;

% %% Read a video frame and run the detector (Option 1)
% figure; 
% imshow(videoFrame); 
% 
% % Draw a rectangle around the region of interest, and track it
% disp('Select rectangular ROI');
% objectRegion=round(getPosition(imrect));
% objectImage = insertShape(videoFrame,'Rectangle',objectRegion);
% 
% mode = 10;
% 
% %% Use drawing technique for second object. For now.
% figure; 
% imshow(videoFrame); 
% disp('Select rectangular ROI');
% objectRegion2 = round(getPosition(imrect));
% objectImage2 = insertShape(videoFrame,'Rectangle',objectRegion2);


%% Get features from template image (Option 2)
% TODO: Define new template image
template = imread('media/LomographyTemplate.jpg');
bwTemplate = rgb2gray(template);

%TODO: HardCode new ROI based on template image of bot
ROI = [200 130 210 200]; % Region of interest = [xmin ymin width height]. hard coded for each image
pointsTemplate = detectMinEigenFeatures(bwTemplate, 'ROI', ROI);

% Show image and points on template
imshow(template);
hold on;
plot(pointsTemplate);

% Get objectRegion from features and RegionOfInterest of template (Option 2 continued)
sceneImage = rgb2gray(videoFrame);
boxImage = bwTemplate;
scenePoints = detectMinEigenFeatures(sceneImage);
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

% TODO: Replace sceneImage with your live feed snapshot
points = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'yellow');

%% run MatchWithTemplate to get ROI of zumobot

