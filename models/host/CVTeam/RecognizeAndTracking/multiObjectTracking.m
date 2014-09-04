function multiObjectTracking(locations)

% Load camera parameter
load('logitechCameraParams.mat');

% Create system objects used for reading video, detecting moving objects,
% and displaying the results.
obj = setupSystemObjects();

% Create an empty array of tracks.
tracks = initializeTracks();

% ID of the next track
nextId = 1;

% # of the frame
count = 0;

% Detect moving objects, and track them across video frames.
while(count<101)
    
    % Frame # increases 1
    count = count + 1;
    
    % Timing for processing each frame
    tic
    
    frame = readFrame(obj);
    [centroids, bboxes, mask] = detectObjects(obj,frame);
    predictNewLocationsOfTracks(tracks);
    [assignments, unassignedTracks, unassignedDetections] = ...
        detectionToTrackAssignment(tracks, centroids);

    % Update trackes
    tracks = updateAssignedTracks(tracks, assignments, centroids, bboxes);
    tracks = updateUnassignedTracks(tracks, unassignedTracks);
    tracks = deleteLostTracks(tracks);
    [tracks, nextId] = createNewTracks(tracks, unassignedDetections, centroids, bboxes, nextId,locations);

    % Undistort frame
%     [im, newOrigin] = undistortImage(frame, cameraParams, 'OutputView', 'full');
%     figure; imshow(im);
%     title('Undistorted Image');
    
    % Display bounding box and object names
    displayTrackingResults(obj, frame, mask, tracks);
    
    toc
    
end

obj.videoObj.release;

