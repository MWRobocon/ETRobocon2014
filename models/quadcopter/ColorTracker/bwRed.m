clear all;



vidobj = VideoReader('natickTrial2.mp4');

nFrames = vidobj.NumberOfFrames;
vidHeight = vidobj.Height;
vidWidth = vidobj.Width;

movred(1 : nFrames) = struct('cdata', zeros(vidHeight, vidWidth, 3, 'uint8'), 'colormap', []);

for k = 1 : nFrames
    f1 = read(vidobj, k);
    
    f1_f = 255*uint8(redTracker(f1));
    
    movred(k).cdata = f1_f;
end
% figure;
% imshow(f1);
% figure;
% imshow(f1_f);

hf = figure;
set(hf, 'position', [150 150 vidWidth vidHeight]);
movie(hf, movred, 1, vidobj.FrameRate);

