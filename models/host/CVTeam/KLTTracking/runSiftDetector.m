function [objectRegion1,highResPolygonPoints1,objectRegion2,highResPolygonPoints2] = runSiftDetector(camera,template1,template2)    
    [objectRegion1, ~, highResPolygonPoints1] = matchWithTemplate_SIFT(videoFrame, template1);
    [objectRegion2, ~, highResPolygonPoints2] = matchWithTemplate_SIFT(videoFrame, template2);
end