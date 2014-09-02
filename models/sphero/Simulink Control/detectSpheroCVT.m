function pos = detectSpheroCVT( frame, varargin )
%DETECTSPHEROCVT Summary of this function goes here
%   Detailed explanation goes here

persistent isInit blobAnalysis;

if(isempty(isInit))
    blobAnalysis = vision.BlobAnalysis('AreaOutputPort', false,...
        'CentroidOutputPort', true,...
        'BoundingBoxOutputPort', true,...
        'MinimumBlobArea', 100, ...
        'ExcludeBorderBlobs', false);
    isInit = 1;
end
    
if nargin>1 && ~varargin{1}
    clear blobAnalysis isInit
    return
end

[CentroidZ, pos] = detectZumoAndSphero(frame, blobAnalysis);

end

