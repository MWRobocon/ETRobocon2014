function move( sphName, speed, angle)
%MOVE Summary of this function goes here
%   Detailed explanation goes here

persistent isInit sph;

if(isempty(isInit))
    sph = sphero(sphName);
end
    
if ~strcmp(sph.Status, 'open')
    error('Sphero not connected');
end

if u==0
    brake(sph);
else
    roll(sph, speed, angle);
end


end

