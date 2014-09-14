% sphName = 'Sphero-PGP';
% 
% sph = sphero(sphName);
% while strcmp(sph.Status, 'closed')
%     sph = sphero(sphname);
% end

sph = comms.SpheroStore.get(RobotID.SPHERO_ORANGE);

sph.Color = 'k';

vid = imaq.VideoDevice('winvideo');
vid.VideoFormat = 'MJPG_640x480';
vid.ReturnedDataType = 'single';
vid.DeviceProperties.FocusMode = 'manual';

try
    [ sph_calibration_angle ] = sphero_calib( sph, vid );
catch exception
    clear vid sph
    
    rethrow(exception)
end
clear vid sph
