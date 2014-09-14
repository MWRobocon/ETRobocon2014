<<<<<<< HEAD
    %% Setup camera
% cam = webcam; %assuming only 1 camera is connected
%% Set template
% template = img;
template = imread('media/referrals.jpg');
Templatebw = rgb2gray(template);
templatePoints = detectSURFFeatures(Templatebw);
imshow(template);
hold on;
plot(templatePoints);
Templatebw = rgb2gray(template);
templatePoints = detectSURFFeatures(Templatebw);
%% Get scene image

videoReader = vision.VideoFileReader('media/ReferralVideo.mp4');
figure(2)

tic
for i = 1:50
    % frame  = snapshot(cam);
    img = step(videoReader); % read the next video frame
% img = snapshot(cam);
%  imshow(img);
%  hold on;
bw = rgb2gray(img);
points = detectSURFFeatures(bw);
%  plot(points.selectStrongest(50));
disp(points.selectStrongest(1));

[templateFeatures, templatePoints] = extractFeatures(Templatebw, templatePoints);
[imgFeatures, imgPoints] = extractFeatures(bw, points);

matchedPairs = matchFeatures(templateFeatures, imgFeatures);

matchedTemplatePoints = templatePoints(matchedPairs(:,1),:);
matchedImgPoints = points(matchedPairs(:,1),:);
hold on;
showMatchedFeatures(Templatebw, bw, matchedTemplatePoints, matchedImgPoints, 'montage');
title('Matched SURF features including Outliers');

% [tform, inlierTemplatePoints, inlierImgPoints] = estimateGeometricTransform(matchedTemplatePoints, matchedImgPoints, 'affine');

% figure;
% showMatchedFeatures(bwTemplate, bw, inlierTemplatePoints, inlierImgPoints, 'montage');
% title('Matched Points (Inliers Only)');






end
toc

%% Match features

[templateFeatures, templatePoints] = extractFeatures(Templatebw, templatePoints);
[imgFeatures, imgPoints] = extractFeatures(bw, points);

matchedPairs = matchFeatures(templateFeatures, imgFeatures);

matchedTemplatePoints = templatePoints(matchedPairs(:,1),:);
matchedImgPoints = points(matchedPairs(:,1),:);
figure;
showMatchedFeatures(Templatebw, bw, matchedTemplatePoints, matchedImgPoints, 'montage');
title('Matched SURF features including Outliers');

[tform, inlierTemplatePoints, inlierImgPoints] = estimateGeometricTransform(matchedTemplatePoints, matchedImgPoints, 'affine');

figure;
showMatchedFeatures(Templatebw, bw, inlierTemplatePoints, inlierImgPoints, 'montage');
title('Matched Points (Inliers Only)');
=======
    %% Setup camera
% cam = webcam; %assuming only 1 camera is connected
%% Set template
% template = img;
template = imread('media/referrals.jpg');
Templatebw = rgb2gray(template);
templatePoints = detectSURFFeatures(Templatebw);
imshow(template);
hold on;
plot(templatePoints);
Templatebw = rgb2gray(template);
templatePoints = detectSURFFeatures(Templatebw);
%% Get scene image

videoReader = vision.VideoFileReader('media/ReferralVideo.mp4');
figure(2)

tic
for i = 1:50
    % frame  = snapshot(cam);
    img = step(videoReader); % read the next video frame
% img = snapshot(cam);
%  imshow(img);
%  hold on;
bw = rgb2gray(img);
points = detectSURFFeatures(bw);
%  plot(points.selectStrongest(50));
disp(points.selectStrongest(1));

[templateFeatures, templatePoints] = extractFeatures(Templatebw, templatePoints);
[imgFeatures, imgPoints] = extractFeatures(bw, points);

matchedPairs = matchFeatures(templateFeatures, imgFeatures);

matchedTemplatePoints = templatePoints(matchedPairs(:,1),:);
matchedImgPoints = points(matchedPairs(:,1),:);
hold on;
showMatchedFeatures(Templatebw, bw, matchedTemplatePoints, matchedImgPoints, 'montage');
title('Matched SURF features including Outliers');

% [tform, inlierTemplatePoints, inlierImgPoints] = estimateGeometricTransform(matchedTemplatePoints, matchedImgPoints, 'affine');

% figure;
% showMatchedFeatures(bwTemplate, bw, inlierTemplatePoints, inlierImgPoints, 'montage');
% title('Matched Points (Inliers Only)');






end
toc

%% Match features

[templateFeatures, templatePoints] = extractFeatures(Templatebw, templatePoints);
[imgFeatures, imgPoints] = extractFeatures(bw, points);

matchedPairs = matchFeatures(templateFeatures, imgFeatures);

matchedTemplatePoints = templatePoints(matchedPairs(:,1),:);
matchedImgPoints = points(matchedPairs(:,1),:);
figure;
showMatchedFeatures(Templatebw, bw, matchedTemplatePoints, matchedImgPoints, 'montage');
title('Matched SURF features including Outliers');

[tform, inlierTemplatePoints, inlierImgPoints] = estimateGeometricTransform(matchedTemplatePoints, matchedImgPoints, 'affine');

figure;
showMatchedFeatures(Templatebw, bw, inlierTemplatePoints, inlierImgPoints, 'montage');
title('Matched Points (Inliers Only)');
>>>>>>> 49348b51a63c56d87ba47b68ef106e265e871506
