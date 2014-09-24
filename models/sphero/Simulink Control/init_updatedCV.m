clc
fprintf('Start initializing Sphero and CV\n');

if ~exist('sphOrangeName', 'var')
    sphOrangeName = 'Sphero-PGP';
else
    sphOrangeName = char(sphOrangeName);
end

if ~exist('sphBlueName', 'var')
    sphBlueName = 'Sphero-PRB';
else
    sphBlueName = char(sphBlueName);
end

fprintf('Sphero init\n');

sphero_init(sphOrangeName, sphBlueName);

fprintf('Init trackTwoMinions\n')
detectVideoFormatStr = 'RGB24_1600x1200';
trackVideoFormatStr = 'RGB24_640x480';

initTrackTwoMinions(0, detectVideoFormatStr, trackVideoFormatStr)

fprintf('Done initializing Sphero and CV\n');