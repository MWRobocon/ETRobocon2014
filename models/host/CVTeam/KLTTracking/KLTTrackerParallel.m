% function [botMean, botMean2] = KLTTrackerParallel(pointsLocation, points2Location, firstFrame, NFrame)
function [TimeReader, TimeTracker, botMean, botMean2] = KLTTrackerParallel(pointsLocation, points2Location, firstFrame, NFrame)
%#codegen
coder.extrinsic('tic', 'toc'); %Another possible option
coder.cinclude('time.h');
botMean = zeros(NFrame,2);
botMean2 = zeros(NFrame,2);
TimeReader = zeros(NFrame,1);
TimeTracker = zeros(NFrame,1);
time = coder.opaque('clock_t');
time2 = coder.opaque('clock_t');

videoFileReader = vision.VideoFileReader('media/BookAndPouch480p.mp4');

tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, pointsLocation, firstFrame);

tracker2 = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker2,points2Location, firstFrame);


videoFrame = firstFrame;

for ii = 1:NFrame
    
    coder.ceval('time = clock');
    videoFrame = step(videoFileReader);
    coder.ceval('time2 = clock');
    TimeReader(ii) = coder.ceval('((double)(time2 - time))/CLOCKS_PER_SEC');
    
    [points, isFound] = step(tracker,videoFrame);
    [points2, isFound2] = step(tracker2,videoFrame);
    time2 = coder.ceval('clock');
    TimeTracker(ii) = coder.ceval('((double)(time2 - time))');
    
    visiblePoints = points(isFound, :);
    visiblePoints2 = points2(isFound2, :);

    botMean(ii,:) = mean(visiblePoints); % Mean of all the features
    botMean2(ii,:) = mean(visiblePoints2); % Mean of all the features

end



end