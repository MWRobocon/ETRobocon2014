%% Initialise
% videoPlayer = vision.VideoPlayer();
vid = imaq.VideoDevice('winvideo', 1);
vid.VideoFormat = 'MJPG_1280x720'
NFrame = 800;
magnification = 25;
imOrig = step(vid);

%% Run camera calibration to get world points and cameraParams
% CalibrateLogitechNormalCam;
load('MSLifeCamParams.mat');

%% Undistort the Image

[im, newOrigin] = undistortImage(imOrig, MSLifeCamCinemaParams, 'OutputView', 'full');
figure; imshow(im, 'InitialMagnification', magnification);
title('Undistorted Image');

%% Segment Coins
% Convert the image to the HSV color space.
imHSV = rgb2hsv(im);

% Get the saturation channel.
saturation = imHSV(:, :, 2);

% Threshold the image
t = graythresh(saturation);
imCoin = (saturation > t);

% figure; imshow(imCoin, 'InitialMagnification', magnification);
% title('Segmented Coins');

se = strel('square', 3);
filteredForeground = imopen(imCoin, se);
figure; imshow(filteredForeground); title('Clean Foreground');

imCoin = filteredForeground;
%% Detect Coins
% Find connected components.
blobAnalysis = vision.BlobAnalysis('AreaOutputPort', true,...
    'CentroidOutputPort', false,...
    'BoundingBoxOutputPort', true,...
    'MinimumBlobArea', 200, 'MaximumBlobArea', 3000, ...
    'ExcludeBorderBlobs', true);
[areas, boxes] = step(blobAnalysis, imCoin);

% Sort connected components in descending order by area
[~, idx] = sort(areas, 'Descend');

% Get the two largest components.
boxes = double(boxes(idx, :));
areas = areas(idx);

% Adjust for coordinate system shift caused by undistortImage
boxes(:, 1:2) = bsxfun(@plus, boxes(:, 1:2), newOrigin);

% Reduce the size of the image for display.
scale = magnification / 100;
imDetectedCoins = imresize(im, scale);

% Insert labels for the coins.
imDetectedCoins = insertObjectAnnotation(imDetectedCoins, 'rectangle', ...
    scale * boxes, 'penny');
figure; imshow(imDetectedCoins);
title('Detected Coins');

%% Compute Extrinsics
% Detect the checkerboard.
[imagePoints, boardSize] = detectCheckerboardPoints(im);

% Compute rotation and translation of the camera.
[R, t] = extrinsics(imagePoints, MSLifeCamCinemaParams.WorldPoints, MSLifeCamCinemaParams);

%% Measure the First Coin
% Get the top-left and the top-right corners.
box1 = double(boxes(1, :));
imagePoints1 = [box1(1:2); ...
                box1(1) + box1(3), box1(2)];

% Get the world coordinates of the corners
worldPoints1 = pointsToWorld(MSLifeCamCinemaParams, R, t, imagePoints1);

% Compute the diameter of the coin in millimeters.
d = worldPoints1(2, :) - worldPoints1(1, :);
diameterInMillimeters = hypot(d(1), d(2));
fprintf('Measured diameter of one circle = %0.2f mm\n', diameterInMillimeters);

%% Measure the Distance to The First Coin
% Compute the center of the first coin in the image.
center1_image = box1(1:2) + box1(3:4)/2;

% Convert to world coordinates.
center1_world  = pointsToWorld(MSLifeCamCinemaParams, R, t, center1_image);

% Remember to add the 0 z-coordinate.
center1_world = [center1_world 0];

% Compute the distance to the camera.
distanceToCamera = norm(center1_world + t);
fprintf('Distance from the camera to the first penny = %0.2f mm\n', ...
    distanceToCamera);