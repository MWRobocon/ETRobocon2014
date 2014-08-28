function [tracks, nextId] = createNewTracks(tracks, unassignedDetections, centroids, bboxes, nextId, locations)
        centroids = centroids(unassignedDetections, :);
        bboxes = bboxes(unassignedDetections, :);

        for i = 1:size(centroids, 1)

            centroid = centroids(i,:);
            bbox = bboxes(i, :);

            % Create a Kalman filter object.
            kalmanFilter = configureKalmanFilter('ConstantVelocity', ...
                centroid, [200, 50], [100, 25], 100);

            % Match tracks with objects
            distence = 200; % diagonal length of 160x120
            for j = 1:length(locations)
                diffOfEachDirection = double(locations(j).centroid) - centroid;
                curDistence = sqrt(diffOfEachDirection(1)^2 + diffOfEachDirection(2)^2);
                if curDistence < distence
                    curID = locations(j).name;
                    distence = curDistence;
                end
            end
            
            % Create a new track.
            newTrack = struct(...
                'id', nextId, ...
                'name', curID, ...
                'bbox', bbox, ...
                'centroid', centroid, ...
                'undistortedCentroid', [0 0], ...
                'kalmanFilter', kalmanFilter, ...
                'age', 1, ...
                'totalVisibleCount', 1, ...
                'consecutiveInvisibleCount', 0);

            % Add it to the array of tracks.
            tracks(end + 1) = newTrack;

            % Increment the next id.
            nextId = nextId + 1;
        end
    end