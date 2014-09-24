%% Zumobot tracking using Kanade-Lucas-Tomasi point tracker. Sphero detection using colour (HSV)
% It takes live feed from camera and gives video output of zumobot (matched
% against template image) and sphero (HSV colour thresholding)

%% Initialize (setup System objects and variables)

% Initiate camera, video player and video file writer
vid = imaq.VideoDevice('winvideo', 1);
% vid.VideoFormat = 'MJPG_1280x720';
% vid.VideoFormat = 'MJPG_640x480';
vid.VideoFormat = 'MJPG_960x720';
videoPlayer = vision.VideoPlayer();
videoWriter = vision.VideoFileWriter('media/MarioLiveFeedT.mp4', 'FileFormat', 'MPEG4');
tracker = vision.PointTracker('MaxBidirectionalError', 3);
% Blob analysis for sphero
blobAnalysis = vision.BlobAnalysis('AreaOutputPort', false,...
    'CentroidOutputPort', true,...
    'BoundingBoxOutputPort', true,...
    'MinimumBlobArea', 100, 'MaximumBlobArea', 3000, ...
    'ExcludeBorderBlobs', false);

% Load camera distortion parameters (intrinsics)
% load('MSLifeCamParams.mat');
load('logitechCameraParams.mat');

% Other important variables
magnification = 25; %magnification to show image. Doesn't affect algo, can remove
NFeaturesToTrack = 50; % Track strongest N features
NFrame = 800; % Number of frames

% Are you ready?
disp('Press any key when you are ready for first frame capture');
pause;
videoFrame = step(vid); %for videoDevice system object

% Get frame size. These may not be used
r = size(videoFrame,1);
c = size(videoFrame,2);

% Get objectRegion from features and ROI of template
videoFrameBW = rgb2gray(videoFrame);
scenePoints = detectSURFFeatures(videoFrameBW); %This may not be used

mode = 0; % debug flag

%% Run matchWithTemplate() to get ROI in videoFrame corresponding to template image
template = imread('media/Mario.jpg');
objectRegion = matchWithTemplate(videoFrame, template);

mode = 11;

%% Get features within newly obtained objectRegion. Initialize tracker
points = detectMinEigenFeatures(videoFrameBW, 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);
pointImage = insertMarker(videoFrame, points.Location, '+', 'Color', 'yellow'); %Not used?

% Initialize tracker with given points and frame
initialize(tracker, points.Location, videoFrame);

mode = 20; % mode = initializing

%% Get undistorted image
[im, newOrigin] = undistortImage(videoFrame, cameraParams, 'OutputView', 'full');
figure; imshow(im, 'InitialMagnification', magnification);
title('Undistorted Image');

% Detect checkerboard from computing extrinsics
% Use SAME checkerboard in camera frame as the one used during calibration!
[imagePoints, boardSize] = detectCheckerboardPoints(im); %baordSize not used?

% Compute extrinsics, rotation and translation, of the camera
[Rotation, translation] = extrinsics(imagePoints, cameraParams.WorldPoints, cameraParams);

%% Track (and re-detect if necessary) for the whole video
disp('Press any key to start tic-toc');
pause;

% Variables to measure performance of each operation (clean up perf code)
TimeReader = zeros(NFrame,1);
TimeTracker = zeros(NFrame,1);
TimePlayer = zeros(NFrame,1);

tstart = clock; % Could be used in lieu of tic-toc in codegen
% tic
% while ~isDone(videoFileReader)
for ii = 1:NFrame
    
    tic
    videoFrame = step(vid);
    TimeReader(ii) = toc; %Time taken to read image frame
    
    % Track features in the new frame
    [points, isFound] = step(tracker,videoFrame);
    TimeTracker(ii) = toc; %Time taken to read + track points
    
    % Get array of visible points
    visiblePoints = points(isFound, :);
    botMean = mean(visiblePoints); % Sparse centroid of zumobot
    
    % Get the coordinates of the centroid in the real world
    worldCentroid = pointsToWorld(cameraParams, Rotation, translation, botMean);
    
    %% Pure saturation thresholding
    %     temp = rgb2hsv(videoFrame);
    %     saturation = temp(:,:,2);
    %     thresh = graythresh(saturation);
    %     filtered = (saturation > thresh);
    %     % imshow(filtered);
    %     blobAnalysis = vision.BlobAnalysis('AreaOutputPort', false,...
    %         'CentroidOutputPort', true,...
    %         'BoundingBoxOutputPort', true,...
    %         'MinimumBlobArea', 200);
    %     [centroids, boxes] = step(blobAnalysis, filtered);
    %
    %     videoFrame = insertMarker(videoFrame, centroids , 'x', 'Color',...
    %         'red', 'Size', 5);
    %
    
    %% Hue and saturation thresholding with imfindcircles to get spheros
    % Convert RGB to HSV, to get the saturation & hue value of each pixel.
    % Saturation can differentiate between colour and grayscale pixel. Hue can
    % differentiate between different colours (used for differentiating between
    % spheros)
    
    % Show captured image
    % imshow(videoFrame)
    % title('Captured image');
    
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
    
    filteredOrange = (hue > 0 & hue < 0.05 & saturation > threshSat);
    % figure; imshow(filteredOrange);
    % title('Filtered Orange');
    
    % Detect centers of blue and yellow spheros (alternative is blob Analysis)
%     [CentersBlue, RadiiBlue] = imfindcircles(filteredBlue, [50 70], 'Sensitivity', 0.95);
    % viscircles(CentersBlue, RadiiBlue, 'EdgeColor', 'b');
    [CentersBlue, BoxBlue] = step(blobAnalysis, filteredBlue);
    
%     [CentersYellow, RadiiYellow] = imfindcircles(filteredYellow, [50 70], 'Sensitivity', 0.97);
    % viscircles(CentersYellow, RadiiYellow, 'EdgeColor', 'y');
    [CentersYellow, BoxYellow] = step(blobAnalysis, filteredYellow);
<<<<<<< HEAD
=======
    
    [CentersOrange, BoxOrange] = step(blobAnalysis, filteredOrange);
    
>>>>>>> 49348b51a63c56d87ba47b68ef106e265e871506
    
    %%  Add all annotations to video frame
    
    % Display KLT tracked points
    if ~isempty(visiblePoints)
        videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
            'Color', 'green', 'Size', 5);
    end
    
    position =  [50 50]; % [x y]
    videoFrame = insertText(videoFrame, position, int2str(worldCentroid));
    
    % Show the points on the output video
    videoFrame = insertMarker(videoFrame, botMean , 'x', ...
        'Color', 'red', 'Size', 5);
    
    % Show blue and yellow spheros
    if ~isempty(CentersBlue)
%         videoFrame = insertShape(videoFrame, 'circle', ...
%             [CentersBlue(1,:) RadiiBlue(1)], 'LineWidth', 5, 'Color', 'blue');
        videoFrame = insertMarker(videoFrame, CentersBlue , 'x', 'Color',...
            'blue', 'Size', 5);
    end
    
    if ~isempty(CentersYellow)
%         videoFrame = insertShape(videoFrame, 'circle', ...
%             [CentersYellow(1,:) RadiiYellow(1)], 'LineWidth', 5, 'Color', 'yellow');
        videoFrame = insertMarker(videoFrame, CentersYellow, 'x', 'Color',...
            'yellow', 'Size', 5);
<<<<<<< HEAD
=======
    end
    
    if ~isempty(CentersOrange)
        videoFrame = insertMarker(videoFrame, CentersOrange, 'x', 'Color',...
            'black', 'Size', 5);
    else
        failedFrame = videoFrame;
        disp('Could not find orange sphero. Exiting');
        return;
>>>>>>> 49348b51a63c56d87ba47b68ef106e265e871506
    end
    
    % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
    TimePlayer(ii) = toc; %Time taken to read+track points, and show video
    
    %     step(videoWriter, videoFrame); % write to video file
    
end
% tend = toc;
tLoop = etime(clock, tstart);
fprintf('Loop time taken: %f\n', tLoop);

%% Release system objects
release(videoPlayer);
% release(videoFileReader);
release(videoWriter);
release(vid);
clear vid videoPlayer videoWriter;

mode = 30; % end game

Timing = struct('TimeReader', TimeReader, 'TimeTracker', (TimeTracker - TimeReader), 'TimePlayer', (TimePlayer - TimeTracker));
figure
plot(1:NFrame, Timing.TimeReader, 1:NFrame,Timing.TimeTracker,1:NFrame, Timing.TimePlayer);
title('Timing for Reader, Tracker, Player');
legend('TimeReader', 'TimeTracker', 'TimePlayer');

figure
plot(1:NFrame, Timing.TimeReader, 1:NFrame, (Timing.TimeReader + Timing.TimeTracker));
legend('Reader', 'Reader + Tracker');
title('Timing for Reader, Reader+Tracker');

% Avg computation time with reader and tracker ONLY; display not counted
% removing initial overhead of first few frames. this is steady state avg
AvgComputationPerFrame = sum(Timing.TimeReader(21:end) + Timing.TimeTracker(21:end))/(NFrame-20)

% Computational fps for reading and tracking ONLY
ComputationFrameRate = 1/AvgComputationPerFrame