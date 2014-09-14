%% Zumobot tracking using Kanade-Lucas-Tomasi point tracker. Sphero detection using colour (HSV)
% It takes live feed from camera and gives video output of zumobot (matched
% against template image) and sphero (HSV colour thresholding)

%% Initialize (setup System objects and variables)

clear;
% Parameters
detectVideoFormat = 'MJPG_960x720';
trackVideoFormat = 'MJPG_640x480';

% Initiate camera, video player and video file writer
vid = imaq.VideoDevice('winvideo', 1);
% vid.VideoFormat = 'MJPG_1280x720';

% Setup Camera for Detection
vid.VideoFormat = detectVideoFormat;
% vid.VideoFormat = 'MJPG_960x720';
videoPlayer = vision.VideoPlayer();
NFrame = 800; % Number of frames to track performance

%% Are you ready?
disp('Press any key when you are ready for first frame capture');
pause;
videoFrame = step(vid); %for videoDevice system object

%% Run the detector
[objectRegion, ~, highResPolygonPoints] = matchWithTemplate_SIFT(videoFrame, imread('media/Mario.jpg'));
[objectRegion2, ~, highResPolygonPoints2] = matchWithTemplate_SIFT(videoFrame, imread('media/bowser.jpg'));

[objectRegion,lowResPolygonPoints] = resizeBox(highResPolygonPoints,[960,720],[640,480]);
[objectRegion2,lowResPolygonPoints2] = resizeBox(highResPolygonPoints2,[960,720],[640,480]);

%% Setup Camera for Tracker
vid.release();
vid.VideoFormat = trackVideoFormat;
videoFrame = vid.step();

%% Initialize
[~,~,~,threshold] = trackTwoMinions(videoFrame,1,objectRegion,objectRegion2,lowResPolygonPoints,lowResPolygonPoints2);
%detectTwoMinions(videoFrame,1); %initialize blob analyser, point tracker
mode = 11;

%% Track for the whole video
disp('Press any key to start tic-toc');
pause;

% Variables to measure performance of each operation (clean up perf code)
TimeReader = zeros(NFrame,1);
TimeTracker = zeros(NFrame,1);
TimePlayer = zeros(NFrame,1);

tstart = clock; % Could be used in lieu of tic-toc in codegen
ii=0;
% tic
% while ~isDone(videoFileReader)
while(1)
    ii = ii+1;
    tic
    videoFrame = step(vid);
    TimeReader(ii) = toc; %Time taken to read image frame
    
    %[botMean, ~,visiblePoints] = detectTwoMinions(videoFrame,0);
    [botMean,~,visiblePoints] = trackTwoMinions(videoFrame,0);
    TimeTracker(ii) = toc; %Time taken to read + track points
    
    %%  Add all annotations to video frame

    % Display KLT tracked points
    if ~isempty(visiblePoints)
        videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
            'Color', 'yellow', 'Size', 5);
    end
    Box = [single(botMean(1,1))-threshold, single(botMean(1,2))-threshold, 2*threshold, 2*threshold];
    videoFrame = insertShape(videoFrame, 'Rectangle', Box);
    
%     position =  [50 50]; % [x y]
%     videoFrame = insertText(videoFrame, position, int2str(worldCentroid));
    
    % Show the points on the output video
    videoFrame = insertMarker(videoFrame, botMean , 'o', ...
        'Color', 'red', 'Size', 5);
    
    % Show blue and yellow spheros
%     if ~isempty(CentersBlue)
% %         videoFrame = insertShape(videoFrame, 'circle', ...
% %             [CentersBlue(1,:) RadiiBlue(1)], 'LineWidth', 5, 'Color', 'blue');
%         videoFrame = insertMarker(videoFrame, CentersBlue , 'x', 'Color',...
%             'blue', 'Size', 5);
%     end
%     
%     if ~isempty(CentersYellow)
% %         videoFrame = insertShape(videoFrame, 'circle', ...
% %             [CentersYellow(1,:) RadiiYellow(1)], 'LineWidth', 5, 'Color', 'yellow');
%         videoFrame = insertMarker(videoFrame, CentersYellow, 'x', 'Color',...
%             'yellow', 'Size', 5);
%     end
    
    try
        videoFrame = insertMarker(videoFrame, spheroMean, 'x', 'Color',...
            'black', 'Size', 5);
    catch
        failedFrame = videoFrame;
        
%         disp('Could not find orange sphero in frame');
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
% release(videoWriter);
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