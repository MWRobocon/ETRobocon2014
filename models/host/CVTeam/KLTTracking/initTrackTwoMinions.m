function [threshold] = initTrackTwoMinions(debug, detectVideoFormatStr, trackVideoFormatStr)
    if(nargin == 0)
        debug = 0;
    end
    
    % Camera Parameters
    adapterName = 'winvideo';
    deviceId = 1;
%     detectVideoFormatStr = 'RGB24_1600x1200';
%     trackVideoFormatStr = 'RGB24_640x480';
    
    % Frame Parameters
    detectFrameShape = [1600,1200];
    trackFrameShape = [640,480];
    
    vid = imaq.VideoDevice(adapterName, deviceId);
    vid.VideoFormat = detectVideoFormatStr;
    detectVideoFrame = vid.step();
    vid.release();

    vid.VideoFormat = trackVideoFormatStr;
    trackVideoFrame = vid.step();
    vid.release();
    
    template1 = imread('media/Mario.jpg');
    template2 = imread('media/bowserFace.png');
        
    [~, ~, highResPolygonPoints1, fvideoFrame, dvideoFrame] = matchWithTemplate_SIFT(detectVideoFrame, template1, debug);
    [~, ~, highResPolygonPoints2] = matchWithTemplate_SIFT(detectVideoFrame, template2,debug, fvideoFrame, dvideoFrame);
    
    [objectRegion1,lowResPolygonPoints1] = resizeBox(highResPolygonPoints1,detectFrameShape,trackFrameShape);
    [objectRegion2,lowResPolygonPoints2] = resizeBox(highResPolygonPoints2,detectFrameShape,trackFrameShape);
    
    initFlag = 1;
    [CentroidsZ,~,~,threshold] = trackTwoMinions(trackVideoFrame,initFlag,objectRegion1,objectRegion2,lowResPolygonPoints1,lowResPolygonPoints2);
    
    vectOrange =[[155;142] calculateStopPosition(CentroidsZ)];
    vectBlue = [[102; 127] vectOrange(:,2) vectOrange(:,3)-[20; 20]];
    gcf; hold on;
    plot(vectOrange(1,:), vectOrange(2,:), 'or');
    plot(vectBlue(1,:), vectBlue(2,:), 'xb');
    hold off;
    
    
    dd = Simulink.dd.open('hostData.sldd');
    dd.assignin('zumoInitCentroids',CentroidsZ');
    dd.assignin('posVectOrange',vectOrange);
    dd.assignin('posVectBlue', vectBlue);
    dd.saveChanges;
end