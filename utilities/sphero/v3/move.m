function move_sphero( sphName, speed, angle, varargin)
%MOVE Summary of this function goes here
%   Detailed explanation goes here

persistent isInit sph;

if(isempty(isInit))
    sph = sphero(sphName);
    isInit = 1;
end
    
if nargin>3 && ~varargin{1}
    clear sph isInit
    return
end

if ~strcmp(sph.Status, 'open')
    error('Sphero not connected');
end

% if speed==0
%     brake(sph);
% else
    roll(sph, speed, angle);
% end


end

