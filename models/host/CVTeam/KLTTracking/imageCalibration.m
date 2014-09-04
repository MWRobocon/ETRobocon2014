function [calibratedImg, tform] = imageCalibration (distorted,original)
load captured_signs_more1.mat;
original  = rgb2gray(imread('media/roadsigns50pc.png'));

imshow(original); 
title('Base image');

% vidObj = imaq.VideoDevice('winvideo',1,'RGB24_960x720');
% distorted = step(vidObj);
distorted = rgb2gray(distorted2);
figure; 
imshow(distorted);

title('Transformed image');

%% Detect and extract features from both images.

ptsOriginal  = detectSURFFeatures(original);
ptsDistorted = detectSURFFeatures(distorted);

% ptsStop  = detectSURFFeatures(stopImg);
% ptsYield  = detectSURFFeatures(yieldImg);
% ptsStone  = detectSURFFeatures(stoneImg);
% ptsNoEnter  = detectSURFFeatures(noEnterImg);
% ptsNoPed  = detectSURFFeatures(noPedImg);
% ptsBridge  = detectSURFFeatures(bridgeImg);

% ptsOriginal  = detectBRISKFeatures(original);
% ptsDistorted = detectBRISKFeatures(distorted);
% 
% ptsOriginal  = detectFASTFeatures(original);
% ptsDistorted = detectFASTFeatures(distorted);
% 
% ptsOriginal  = detectHarrisFeatures(original);
% ptsDistorted = detectHarrisFeatures(distorted);
% 
% ptsOriginal  = detectMSERFeatures(original);
% ptsDistorted = detectMSERFeatures(distorted);
% 
% ptsOriginal  = detectMinEigenFeatures(original);
% ptsDistorted = detectMinEigenFeatures(distorted);

[featuresOriginal,   validPtsOriginal] = extractFeatures(original,  ptsOriginal);
[featuresDistorted, validPtsDistorted] = extractFeatures(distorted, ptsDistorted);

% [featuresStop,   validPtsStop] = extractFeatures(stopImg,  ptsStop);
% [featuresYield,   validPtsYield] = extractFeatures(yieldImg,  ptsYield);
% [featuresStone,   validPtsStone] = extractFeatures(stoneImg,  ptsStone);
% [featuresNoEnter,   validPtsNoEnter] = extractFeatures(noEnterImg,  ptsNoEnter);
% [featuresNoPed,   validPtsNoPed] = extractFeatures(noPedImg,  ptsNoPed);
% [featuresBridge,   validPtsBridge] = extractFeatures(bridgeImg,  ptsBridge);


%% Match features.
index_pairs = matchFeatures(featuresOriginal, featuresDistorted);
matchedPtsOriginal  = validPtsOriginal(index_pairs(:,1));
matchedPtsDistorted = validPtsDistorted(index_pairs(:,2));
figure; 
showMatchedFeatures(original,distorted,matchedPtsOriginal,matchedPtsDistorted);
title('Matched SURF points, including outliers');

%% Exclude the outliers, and compute the transformation matrix.
[tform,inlierPtsDistorted,inlierPtsOriginal] = estimateGeometricTransform(matchedPtsDistorted,matchedPtsOriginal,'projective');
figure; 
showMatchedFeatures(original,distorted,inlierPtsOriginal,inlierPtsDistorted);
title('Matched inlier points');

%% Recover the original image from the distorted image.
outputView = imref2d(size(original));
calibratedImg = imwarp(distorted, tform, 'OutputView', outputView);
figure; 
imshow(calibratedImg); 
title('Recovered image');

% close all;