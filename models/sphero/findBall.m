function pos = findBall(vid)
%% Find Green Object
% This script reads in an image file and then attempts to find a green
% object in the image. It is designed to find one green ball and highlight
% that ball on the original image

% Copyright 2010 The MathWorks, Inc.

% vid = webcam;

snapshot = getsnapshot(vid);
figure
imagesc(snapshot);

%% Read in Image
% First we read the specified image from the file and bring it into MATLAB
% as a variable. We also display the image to ensure it is correct.

% greenBall1 = imread('greenBall1.jpg');
% image(greenBall1);

%% Extract each color
% Next we using indexing to extract three 2D matrices from the 3D image
% data corresponding to the red, green, and blue components of the image.
r = snapshot(:, :, 1);
g = snapshot(:, :, 2);
b = snapshot(:, :, 3);

%% Calculate Orange
% Then we perform an arithmetic operation on the matrices as a whole to try
% to create one matrix that represents an intensity of green.
justGreen = r - g - b/1.1;
% colorsPlot(r, g, b, justGreen);
%%
close

%% Threshold the image
% Now we can set a threshold to separate the parts of the image that we
% consider to be green from the rest.
bw = justGreen > 60;
% imagesc(bw);
% colormap(gray);

%% Find center
% Find the row and column location of the pixels and calculate the mean to get
% the approximate center of the ball.
[r,c] = find(bw);
if isempty(r)
    pos = [-1 -1];
else
    pos = [mean(c) mean(r)];
end
% hold on, plot(pos(1),pos(2),'r.','MarkerSize',30), hold off
% 
% %% Show marker on original image
% % Finally we will plot the center on the original image to clearly evaluate
% % how well we have found the center.
% image(snapshot);
% hold on, plot(pos(1),pos(2),'r.','MarkerSize',30), hold off