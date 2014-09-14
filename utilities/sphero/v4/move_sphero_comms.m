function move_sphero_comms( sphero_RobotID, speed, angle)
%MOVE_SPHERO_COMMS Move the indicated Sphero with desired speed and angle

sph = comms.SpheroStore.get(sphero_RobotID);

if ~strcmp(sph.Status, 'open')
    error('Sphero not connected');
end

roll(sph, speed, angle);

end


