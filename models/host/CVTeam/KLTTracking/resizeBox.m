function [objectRegion,boxCorners] = resizeBox(boxCorners,origFrameShape,newFrameShape)
% Usage:
% [boxRegion,resizedBoxCorners] = resizeBox(boxCorners,origFrameShape,newFrameShape)
%
% Input Arguments:
% boxCorners : (2 X N) Matrix of box (x,y) corners in the original frame
% origFrameShape : [width height] Shape of the original frame
% newFrameShape : [width height] Shape of the new frame the box is being resized to
%
% Output Arguments:
% objectRegion : [xmin,ymin,width,height] ROI of box in newFrame
% resizedBoxCorners : (2 X N) Matrix of box (x,y) corners in the new frame
%
% Description :
% Resizes corners of a box in an original frame of shape 'origFrameShape'
% into a new frame of shape 'newFrameShape'.  Returns an ROI for the box in
% the new frame along with the corner positions.

    boxCorners(:,1) = boxCorners(:,1)*newFrameShape(1)/origFrameShape(1);
    boxCorners(:,2) = boxCorners(:,2)*newFrameShape(2)/origFrameShape(2);

    xmax = max(boxCorners(:,1));
    ymax = max(boxCorners(:,2));
    xmin = min(boxCorners(:,1));
    ymin = min(boxCorners(:,2));
    w = xmax - xmin;
    h = ymax - ymin;

    objectRegion = uint16([xmin, ymin, w, h]); % Use this ROI to get features
end
