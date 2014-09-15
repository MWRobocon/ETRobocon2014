function [threshold] = initTrackTwoMinions(debug)
    if(nargin == 0)
        debug = 0;
    end
    
    % Camera Parameters
    adapterName = 'winvideo';
    deviceId = 1;
    detectVideoFormatStr = 'MJPG_960x720';
    trackVideoFormatStr = 'MJPG_640x480';
    
    % Frame Parameters
    detectFrameShape = [960,720];
    trackFrameShape = [640,480];
    
    vid = imaq.VideoDevice(adapterName, deviceId);
    vid.VideoFormat = detectVideoFormatStr;
    detectVideoFrame = vid.step();
    vid.release();
        
    vid.VideoFormat = trackVideoFormatStr;
    trackVideoFrame = vid.step();
    vid.release();
    
    template1 = imread('media/Mario.jpg');
    template2 = imread('media/bowser.jpg');
        
    [~, ~, highResPolygonPoints1] = matchWithTemplate_SIFT(detectVideoFrame, template1,debug);
    [~, ~, highResPolygonPoints2] = matchWithTemplate_SIFT(detectVideoFrame, template2,debug);
    
    [objectRegion1,lowResPolygonPoints1] = resizeBox(highResPolygonPoints1,detectFrameShape,trackFrameShape);
    [objectRegion2,lowResPolygonPoints2] = resizeBox(highResPolygonPoints2,detectFrameShape,trackFrameShape);
    
    initFlag = 1;
    [~,~,~,threshold] = trackTwoMinions(trackVideoFrame,initFlag,objectRegion1,objectRegion2,lowResPolygonPoints1,lowResPolygonPoints2);
end