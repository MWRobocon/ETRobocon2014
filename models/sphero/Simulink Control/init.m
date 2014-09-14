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

sphero_init(sphOrangeName, sphBlueName);
