<<<<<<< HEAD
function objectRegion = matchWithTemplate(scene, template)

%% Get features from template image

bwTemplate = rgb2gray(template);
scene = rgb2gray(scene);
% Region of interest = [xmin ymin width height]. hard coded for each image
% ROI = [200 130 210 200]; %For LomographyTemplate.jpg
% ROI = [84   139   480   205]; %For Gautam.jpg
% ROI = [244 181 106 130]; %For Gautam.jpg 640 x 480
ROI = [0 0 size(template,1) size(template,2)];
% imshow(template);
% disp('Select rectangular ROI for Template');
% ROI = round(getPosition(imrect));

pointsTemplate = detectSURFFeatures(bwTemplate); %, 'ROI', ROI);
imshow(template);
hold on;
plot(pointsTemplate);
title('Template image with detected features');

% Get objectRegion from features and RegionOfInterest of template
scenePoints = detectSURFFeatures(scene);
boxPoints = pointsTemplate; %converting to variables of demo

% Extract features from both and match
[boxFeatures, boxPoints] = extractFeatures(bwTemplate, boxPoints);
[sceneFeatures, scenePoints] = extractFeatures(scene, scenePoints);
boxPairs = matchFeatures(boxFeatures, sceneFeatures);

matchedBoxPoints = boxPoints(boxPairs(:, 1), :);
matchedScenePoints = scenePoints(boxPairs(:, 2), :);
[tform, inlierBoxPoints, inlierScenePoints] = estimateGeometricTransform(matchedBoxPoints, matchedScenePoints, 'affine');

figure;
showMatchedFeatures(bwTemplate, scene, inlierBoxPoints, inlierScenePoints, 'montage');
title('Matched Points (Inliers Only)');

boxPolygon = [ROI(1), ROI(2); ... %top-left
    ROI(1)+ ROI(3), ROI(2); ... %top-right
    ROI(1)+ ROI(3), ROI(2)+ ROI(4); ... %bottom right
    ROI(1), ROI(2)+ ROI(4); ... bottom-left
    ROI(1), ROI(2)]; %top-left again to close the loop

newBoxPolygon = transformPointsForward(tform, boxPolygon);
figure; imshow(scene);
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

=======
function [objectRegion NMatchedPoints] = matchWithTemplate(scene, template)
%% Get features from template image

bwTemplate = rgb2gray(template);
scene = rgb2gray(scene);
% Template region of interest = [xmin ymin width height]
ROI = [0 0 size(template,1) size(template,2)];
% imshow(template);
% disp('Select rectangular ROI for Template');
% ROI = round(getPosition(imrect));

pointsTemplate = detectSURFFeatures(bwTemplate); %, 'ROI', ROI);
imshow(template);
hold on;
plot(pointsTemplate);
title('Template image with detected features');

% Get objectRegion from features and RegionOfInterest of template
scenePoints = detectSURFFeatures(scene);
boxPoints = pointsTemplate; %converting to variables of demo

% Extract features from both and match
[boxFeatures, boxPoints] = extractFeatures(bwTemplate, boxPoints);
[sceneFeatures, scenePoints] = extractFeatures(scene, scenePoints);
boxPairs = matchFeatures(boxFeatures, sceneFeatures);
NMatchedPoints = size(boxPairs,1);

matchedBoxPoints = boxPoints(boxPairs(:, 1), :);
matchedScenePoints = scenePoints(boxPairs(:, 2), :);
[tform, inlierBoxPoints, inlierScenePoints] = estimateGeometricTransform(matchedBoxPoints, matchedScenePoints, 'affine');

figure;
showMatchedFeatures(bwTemplate, scene, inlierBoxPoints, inlierScenePoints, 'montage');
title('Matched Points (Inliers Only)');

% Convert ROI params into corners of a box
boxPolygon = [ROI(1), ROI(2); ... %top-left
    ROI(1)+ ROI(3), ROI(2); ... %top-right
    ROI(1)+ ROI(3), ROI(2)+ ROI(4); ... %bottom right
    ROI(1), ROI(2)+ ROI(4); ... bottom-left
    ROI(1), ROI(2)]; %top-left again to close the loop

newBoxPolygon = transformPointsForward(tform, boxPolygon);
figure; imshow(scene);
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

>>>>>>> refs/remotes/origin/CVTeam
end