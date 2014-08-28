function multiObjectTracking(locations)

% Load location information of all 6 robots
% load('locations.mat');

% Create system objects used for reading video, detecting moving objects,
% and displaying the results.
obj = setupSystemObjects();

tracks = initializeTracks(); % Create an empty array of tracks.

nextId = 1; % ID of the next track

% Detect moving objects, and track them across video frames.
while true
    tic
    frame = readFrame(obj);
    [centroids, bboxes, mask] = detectObjects(obj,frame);
    predictNewLocationsOfTracks(tracks);
    [assignments, unassignedTracks, unassignedDetections] = ...
        detectionToTrackAssignment(tracks, centroids);

    tracks = updateAssignedTracks(tracks, assignments, centroids, bboxes);
    tracks = updateUnassignedTracks(tracks, unassignedTracks);
    tracks = deleteLostTracks(tracks);
    [tracks, nextId] = createNewTracks(tracks, unassignedDetections, centroids, bboxes, nextId,locations);

    % Undistort frame
    load('logitechCameraParams.mat');
    [im, newOrigin] = undistortImage(frame, cameraParams, 'OutputView', 'full');
%     figure; imshow(im);
%     title('Undistorted Image');
    
    % Display bounding box and object names
    displayTrackingResults(obj, frame, mask, tracks);
    toc
end
obj.videoObj.release;

