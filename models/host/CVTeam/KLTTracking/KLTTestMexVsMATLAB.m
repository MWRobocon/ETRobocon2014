%% Initialize objs
videoFileReader = vision.VideoFileReader('media/BookAndPouch720p.mp4');

NFeaturesToTrack = 50;
videoFrame = step(videoFileReader);
NFrame = 810;

%% Read a video frame and run the detector (Option 1)
figure; 
imshow(videoFrame); 

% Draw a rectangle around the region of interest, and track it
disp('Select rectangular ROI');
objectRegion=round(getPosition(imrect));
objectImage = insertShape(videoFrame,'Rectangle',objectRegion);

sceneImage = rgb2gray(videoFrame);

mode = 10;

%% Use drawing technique for second object. For now.
figure; 
imshow(videoFrame); 
disp('Select rectangular ROI');
objectRegion2 = round(getPosition(imrect));
objectImage2 = insertShape(videoFrame,'Rectangle',objectRegion2);

points = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion);
points = points.selectStrongest(NFeaturesToTrack);

points2 = detectMinEigenFeatures(sceneImage, 'ROI', objectRegion2);
points2 = points2.selectStrongest(NFeaturesToTrack);

%% Call function
% tic
[TimeReader, TimeTracker, MexMean1, MexMean2] = KLTTrackerParallel_mex(points.Location, points2.Location, videoFrame, NFrame);
% toc
TimeTracker = TimeTracker - TimeReader;
% tic
% [MLMean1, MLMean2] = KLTTrackerParallel(points.Location, points2.Location, videoFrame, NFrame);
% toc

%% Plot

videoFileReader = vision.VideoFileReader('media/BookAndPouch720p.mp4');
videoWriter = vision.VideoFileWriter('media/BookAndPouch720p_Tracked.mp4', 'FileFormat', 'MPEG4');
% videoPlayer = vision.VideoPlayer();

for ii= 1:NFrame
    videoFrame = step(videoFileReader);
    videoFrame = insertMarker(videoFrame, MexMean1(ii,:) , 'o', 'Color', 'red', 'Size', 5);
    videoFrame = insertMarker(videoFrame, MexMean2(ii,:) , 'o', 'Color', 'red', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, MLMean1(ii,:) , '+', 'Color', 'blue', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, MLMean2(ii,:) , '+', 'Color', 'blue', 'Size', 5);
    
    step(videoWriter, videoFrame);
end

figure
plot(1:NFrame, TimeReader, 1:NFrame,TimeTracker);
title('Timing for Reader, Tracker');
legend('TimeReader', 'TimeTracker');

figure
plot(1:NFrame, Timing.TimeReader, 1:NFrame, (Timing.TimeReader + Timing.TimeTracker));
legend('Reader', 'Reader + Tracker');
title('Timing for Reader, Reader+Tracker');

AvgComputationPerFrame = sum(Timing.TimeReader(21:end) + Timing.TimeTracker(21:end))/(NFrame-20)
ComputationFrameRate = 1/AvgComputationPerFrame


release(videoFileReader);
release(videoWriter);