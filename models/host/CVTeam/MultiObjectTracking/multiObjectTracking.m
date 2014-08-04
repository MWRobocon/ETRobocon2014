function multiObjectTracking()
% Create system objects used for reading video, detecting moving objects,
% and displaying the results.
obj = setupSystemObjects();

tracks = initializeTracks(); % Create an empty array of tracks.

nextId = 1; % ID of the next track

% Detect moving objects, and track them across video frames.
nFrames = 0;
while true
    tic
    nFrames = nFrames + 1;
    disp(nFrames);
    frame = readFrame(obj);
    [centroids, bboxes, mask] = detectObjects(obj,frame);
    predictNewLocationsOfTracks(tracks);
    [assignments, unassignedTracks, unassignedDetections] = ...
        detectionToTrackAssignment(tracks, centroids);

    tracks = updateAssignedTracks(tracks, assignments, centroids, bboxes);
    tracks = updateUnassignedTracks(tracks, unassignedTracks);
    tracks = deleteLostTracks(tracks);
    [tracks, nextId] = createNewTracks(tracks, unassignedDetections, centroids, bboxes, nextId);

    displayTrackingResults(obj, frame, mask, tracks);
    toc
end
obj.videoObj.release;

