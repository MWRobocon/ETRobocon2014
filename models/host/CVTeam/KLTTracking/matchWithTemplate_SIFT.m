function [objectRegion, NMatchedPoints, newBoxPolygon] = matchWithTemplate_SIFT(scene, template, varargin)
%% Get features from template image

if isempty(varargin)
    debug = 0;
else
    debug = varargin{1};
end

template = single(rgb2gray(template)) ;
scene = single(rgb2gray(scene)) ;
ROI = [0 0 size(template,1) size(template,2)];
row = size(scene, 1);
col = size(scene, 2);

[fa, da] = vl_sift(template) ;
[fb, db] = vl_sift(scene) ;

if debug
   figure; imshow(template);
   h1 = vl_plotframe(fa) ;   
   title('All template features');
   
   figure; imshow(scene);
   h2 = vl_plotframe(fb) ;   
   title('All videoFrame features');
end

[matches, ~] = vl_ubcmatch(da, db) ;
sela = matches(1,:);
% h1 = vl_plotframe(fa(:,sela)) ;
selb = matches(2,:);
% h2 = vl_plotframe(fb(:,selb)) ;
NMatchedPoints = size(selb,2);

% if debug
% figure; imshow(scene)
% hold on; plot(scenePoints);
% end

matchedPoints1 = fa(1:2,sela)';
matchedPoints2 = fb(1:2,selb)';

if debug
    figure; imshow(template);
    hold on; 
    h1 = vl_plotframe(fa(:,sela));
    title('Matched points on template');
    
    figure; imshow(scene);
    hold on; 
    h2 = vl_plotframe(fb(:,selb));
    title('Matched points on videoFrame');
        
end

[tform, inlierTemplatePoints, ~] = estimateGeometricTransform(matchedPoints1, matchedPoints2, 'affine');

if debug
    NInlierTemplate = ['Correct matched Points = ', num2str(size(inlierTemplatePoints,1))];
    disp(NInlierTemplate);
end
    

% figure;
% showMatchedFeatures(template, scene, inlierBoxPoints, inlierScenePoints, 'montage');
% title('Matched Points (Inliers Only)');

% Convert ROI params into corners of a box
boxPolygon = [ROI(1), ROI(2); ... %top-left
    ROI(1)+ ROI(3), ROI(2); ... %top-right
    ROI(1)+ ROI(3), ROI(2)+ ROI(4); ... %bottom right
    ROI(1), ROI(2)+ ROI(4); ... bottom-left
    ROI(1), ROI(2)]; %top-left again to close the loop

newBoxPolygon = transformPointsForward(tform, boxPolygon);

if debug
    figure; imshow(scene);
    hold on;
    line(newBoxPolygon(:, 1), newBoxPolygon(:, 2), 'Color', 'y');
    MyTitle = ['Detected Template (HIGHRES), no of points matched: ', num2str(NMatchedPoints)];
    title(MyTitle);
end

%{
lowResSize = size(lowResScene);
origFrameShape = [col,row];
newFrameShape = [lowResSize(2),lowResSize(1)];
[objectRegion,newBoxPolygon] = resizeBox(newBoxPolygon,origFrameShape,newFrameShape);
%}

%{
newBoxPolygon(:,1) = newBoxPolygon(:,1)*640/col;
newBoxPolygon(:,2) = newBoxPolygon(:,2)*480/row;
%}

%{
if(debug)
    figure; imshow(lowResScene);
    hold on;
    line(newBoxPolygon(:, 1), newBoxPolygon(:, 2), 'Color', 'y');
    MyTitle = ['Detected Template (LOWRES), no of points matched: ', num2str(NMatchedPoints)];
    title(MyTitle);
end
%}

xmax = max(newBoxPolygon(:,1));
ymax = max(newBoxPolygon(:,2));
xmin = min(newBoxPolygon(:,1));
ymin = min(newBoxPolygon(:,2));
w = xmax - xmin;
h = ymax - ymin;

objectRegion = uint16([xmin, ymin, w, h]); % Use this ROI to get features

end