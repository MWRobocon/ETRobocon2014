%% Initialize objs
videoFileReader = vision.VideoFileReader('media/BookAndPouch480p.mp4');

NFeaturesToTrack = 50;
videoFrame = step(videoFileReader);
NFrame = 800;

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
tic
[MexMean1, MexMean2] = KLTTrackerParallel_mex(points.Location, points2.Location, videoFrame, NFrame);
toc

tic
[MLMean1, MLMean2] = KLTTrackerParallel(points.Location, points2.Location, videoFrame, NFrame);
toc

%% Plot

videoFileReader = vision.VideoFileReader('media/BookAndPouch480p.mp4');
videoWriter = vision.VideoFileWriter('media/BookAndPouch480p_Tracked.mp4', 'FileFormat', 'MPEG4');
% videoPlayer = vision.VideoPlayer();

for ii= 1:NFrame
    videoFrame = step(videoFileReader);
    videoFrame = insertMarker(videoFrame, MexMean1(ii,:) , 'o', 'Color', 'red', 'Size', 5);
    videoFrame = insertMarker(videoFrame, MexMean2(ii,:) , 'o', 'Color', 'red', 'Size', 5);
    videoFrame = insertMarker(videoFrame, MLMean1(ii,:) , '+', 'Color', 'blue', 'Size', 5);
    videoFrame = insertMarker(videoFrame, MLMean2(ii,:) , '+', 'Color', 'blue', 'Size', 5);
    
    step(videoWriter, videoFrame);
end

release(videoFileReader);
release(videoWriter);