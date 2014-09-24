function isInlier = isInlier(centroid,points,inlierThreshold)
    distX = abs(points(:,1) - centroid(1));
    distY = abs(points(:,2) - centroid(2));
    isInlier = (distX < inlierThreshold) & (distY < inlierThreshold);
end