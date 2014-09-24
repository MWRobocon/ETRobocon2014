sphOrange = comms.SpheroStore.get(RobotID.SPHERO_ORANGE);
sphBlue = comms.SpheroStore.get(RobotID.SPHERO_BLUE);

colors = ['b', 'g', 'r', 'c', 'm', 'y', 'w'];

for i=1:length(colors)
    sphBlue.Color = colors(i);
    pause(1);
end

sphBlue.Color = 'k';

roll(sphBlue, 70, 0);