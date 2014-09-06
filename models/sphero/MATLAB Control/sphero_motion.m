% sph = sphero('Sphero-PGP');

speed = 70; % can be from 0 to 255
delay = 1;

for angle = 0:90:270 % angle in degrees
    sph.roll(speed, angle)
    pause(delay);
end

sph.brake;