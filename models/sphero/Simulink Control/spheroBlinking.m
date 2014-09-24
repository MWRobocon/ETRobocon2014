function spheroBlinking(robot, idx)

sph = comms.SpheroStore.get(robot);

colors = ['b', 'g', 'r', 'c', 'm', 'y', 'w', 'k'];

sph.Color = colors(idx);
