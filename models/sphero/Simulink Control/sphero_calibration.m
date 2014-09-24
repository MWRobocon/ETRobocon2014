% sphName = 'Sphero-PGP';
% 
% sph = sphero(sphName);
% while strcmp(sph.Status, 'closed')
%     sph = sphero(sphname);
% end


vid = imaq.VideoDevice('winvideo');
vid.VideoFormat = 'RGB24_640x480';

% vid.VideoFormat = 'MJPG_640x480';
vid.ReturnedDataType = 'single';
vid.DeviceProperties.FocusMode = 'manual';

sphOrange = comms.SpheroStore.get(RobotID.SPHERO_ORANGE);
sphBlue = comms.SpheroStore.get(RobotID.SPHERO_BLUE);

sphOrange.Color = 'k';
sphOrange.MotionTimeout = 4;
sphOrange.InactivityTimeout = 1800;

sphBlue.Color= 'k';
sphBlue.MotionTimeout = 4;
sphBlue.InactivityTimeout = 1800;

try
    sph_calibration_angle1 = sphero_calib(sphOrange, vid, 1);
    sph_calibration_angle2 = sphero_calib(sphBlue, vid, 0);
catch exception
    clear vid sphOrange sphBlue
    
    rethrow(exception)
end
clear vid sphOrange sphBlue
