clear all;

greyThreshold = 30;
rgThreshold = 20;
gbThreshold = 20;
rbThreshold = 20;

vidobj = VideoReader('natickTrial1.mp4');

nFrames = vidobj.NumberOfFrames;
vidHeight = vidobj.Height;
vidWidth = vidobj.Width;

% hfred = figure();
% imred = imshow(zeros(144, 176, 3));
% 
% hffull = figure();
% imfull = imshow(zeros(144, 176, 3));


% movred(1 : nFrames) = struct('cdata', zeros(vidHeight, vidWidth, 3, 'uint8'), 'colormap', []);
movfull(1 : nFrames) = struct('cdata', zeros(vidHeight*2, vidWidth, 3, 'uint8'), 'colormap', []);
f1_f = zeros(vidHeight, vidWidth, 3);
for k = 1 : nFrames
    f1 = read(vidobj, k);
    
    
    f1_f(:, :, 1) = redTracker(f1);
    
    movfull(k).cdata = [f1_f; f1];
%     movfull(k).cdata = f1;
%     set(imred, 'CData', f1_f);
%     set(imfull, 'CData', f1);
end
% figure;
% imshow(f1);
% figure;
% imshow(f1_f);

% hf = figure;
% set(hf, 'position', [150 150 vidWidth vidHeight]);
% movie(hf, movred, 1, vidobj.FrameRate);
% 
hf2 = figure;
set(hf2, 'position', [150 400 vidWidth vidHeight*2]);
movie(hf2, movfull, 1, vidobj.FrameRate);

