function pos = detectSphero(varargin)
%DETECTSPHERO Summary of this function goes here
%   Detailed explanation goes here

persistent isInit vid;

if(isempty(isInit))
    if nargin
        vid = webcam(varargin{1});
    else
        vid = webcam(2);
    end
    start(vid)
    isInit = 1;
end
    
if nargin>1 && ~varargin{2}
    clear sph isInit
    return
end

pos = findBall(vid);

end

