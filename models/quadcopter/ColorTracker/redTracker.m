function [bwRed] = redTracker(f1)
%#codegen

greyThreshold = 30;
rgThreshold = 20;
gbThreshold = 20;
rbThreshold = 20;

vidHeight = 144;
vidWidth = 176;

%RG channel
frg = f1(:, :, 1 : 2);
%GB channel
fgb = f1(:, :, 2 : 3);
%RB channel
frb = zeros(vidHeight, vidWidth, 2);
frb(:, :, 1) = f1(:, :, 1);
frb(:, :, 2) = f1(:, :, 3);

%null indexes
greynull = max(f1, [], 3) - min(f1, [], 3) < greyThreshold;
rgnull = max(frg, [], 3) - min(frg, [], 3) < rgThreshold;
gbnull = max(fgb, [], 3) - min(fgb, [], 3) < gbThreshold;
rbnull = max(frb, [], 3) - min(frb, [], 3) < rbThreshold;

%dominant indexes (GB null)
rdom = (max(f1, [], 3) - f1(:, :, 1)) < 1;


% f1_f = zeros(vidHeight, vidWidth, 2);
%red----------------------------
% fcred = f1(:, :, 1);
fcred = zeros(vidHeight, vidWidth);
fcred(rdom) = 1;

%strip greyscale
fcred(greynull) = 0;

%strip RG
fcred(rgnull) = 0;

%strip GB
fcred(gbnull & ~rdom) = 0;

%strip RB
fcred(rbnull) = 0;

%filter for R dominance
fcred(~rdom) = 0;

%reconstruct image
% f1_f(:, :, 1) = fcred;
bwRed = fcred;

% %green--------------------------
% fcgreen = f1(:, :, 2);
% 
% %strip greyscale
% fcgreen(greynull) = 0;
% 
% %strip RG
% fcgreen(rgnull) = 0;
% 
% %strip GB
% fcgreen(gbnull & ~rdom) = 0;
% 
% %strip RB
% fcgreen(rbnull) = 0;
% 
% %filter for R dominance
% fcgreen(~rdom) = 0;
% 
% %reconstruct image
% f1_f(:, :, 2) = fcgreen;
% 
% 
% 
% %blue---------------------------
% fcblue = f1(:, :, 3);
% 
% %strip greyscale
% fcblue(greynull) = 0;
% 
% %strip RG
% fcblue(rgnull) = 0;
% 
% %strip GB
% fcblue(gbnull & ~rdom) = 0;
% 
% %strip RB
% fcblue(rbnull) = 0;
% 
% %filter for R dominance
% fcblue(~rdom) = 0;
% 
% %reconstruct image
% f1_f(:, :, 3) = fcblue;
% 
