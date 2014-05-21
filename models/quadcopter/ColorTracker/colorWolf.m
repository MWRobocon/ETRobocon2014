clear all;

greyThreshold = 30;
rgThreshold = 20;
gbThreshold = 20;
rbThreshold = 20;

vidobj = VideoReader('natickTrial2.mp4');

nFrames = vidobj.NumberOfFrames;
vidHeight = vidobj.Height;
vidWidth = vidobj.Width;

movred(1 : nFrames) = struct('cdata', zeros(vidHeight, vidWidth, 3, 'uint8'), 'colormap', []);

for k = 1 : nFrames
    f1 = read(vidobj, k);
    
    %RG channel
    frg = f1(:, :, 1 : 2);
    %GB channel
    fgb = f1(:, :, 2 : 3);
    %RB channel
    frb(:, :, 1) = f1(:, :, 1);
    frb(:, :, 2) = f1(:, :, 3);
    
    %null indexes
    greynull = max(f1, [], 3) - min(f1, [], 3) < greyThreshold;
    rgnull = max(frg, [], 3) - min(frg, [], 3) < rgThreshold;
    gbnull = max(fgb, [], 3) - min(fgb, [], 3) < gbThreshold;
    rbnull = max(frb, [], 3) - min(frb, [], 3) < rbThreshold;
    
    %dominant indexes (GB null)
    rdom = (max(f1, [], 3) - f1(:, :, 1)) < 1;
    
    for i = 1 : 3
        %separate channels
        %1 = R
        %2 = G
        %3 = B
        fc{i} = f1(:, :, i);
        
        %strip greyscale
        fc{i}(greynull) = 0;
        
        %strip RG
        fc{i}(rgnull) = 0;
        
        %strip GB
        fc{i}(gbnull & ~rdom) = 0;
        
        %strip RB
        fc{i}(rbnull) = 0;
        
        %filter for R dominance
        fc{i}(~rdom) = 0;
        
        %reconstruct image
        f1_f(:, :, i) = fc{i};
    end
    
    movred(k).cdata = f1_f;
end
% figure;
% imshow(f1);
% figure;
% imshow(f1_f);

hf = figure;
set(hf, 'position', [150 150 vidWidth vidHeight]);
movie(hf, movred, 1, vidobj.FrameRate);

