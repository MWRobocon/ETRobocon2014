function [botMean, botMean2] = KLTTrackerParallel(pointsLocation, points2Location, firstFrame, NFrame)
%#codegen
botMean = zeros(NFrame,2);
botMean2 = zeros(NFrame,2);
videoFileReader = vision.VideoFileReader('media/BookAndPouch480p.mp4');

tracker = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker, pointsLocation, firstFrame);

tracker2 = vision.PointTracker('MaxBidirectionalError', 3);
initialize(tracker2,points2Location, firstFrame);
videoFrame = firstFrame;

for ii = 1:NFrame
    videoFrame = step(videoFileReader);

    [points, isFound] = step(tracker,videoFrame);
    [points2, isFound2] = step(tracker2,videoFrame);
    
    
    visiblePoints = points(isFound, :);
    visiblePoints2 = points2(isFound2, :);

    botMean(ii,:) = mean(visiblePoints); % Mean of all the features
    botMean2(ii,:) = mean(visiblePoints2); % Mean of all the features

end


end