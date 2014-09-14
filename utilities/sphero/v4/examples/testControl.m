Kp = 2; Ki = 0; Kd = 0;
xdes=  100; ydes = 100;
t = 0:100;

stopRadius = 1; maxspeed = Inf; minspeed = -Inf;


x = 0; y = 0;
prevt = 0;

distarr = [];

control_sphero_motion(xdes, ydes, x, y, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, 1);

figure(1)
clf
hold on
plot(x, y, 'r*')
plot(xdes, ydes, 'kx')

for t = 1:100
%     if t>5
%         keyboard
%     end
    [speed, angle, dist] = control_sphero_motion(xdes, ydes, x, y, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, 0);
    
    x = x + speed*(t-prevt)*sin(angle)*0.7;
    y = y + speed*(t-prevt)*cos(angle)*0.7;
    
    prevt = t;
    plot(x, y, 'r*')
    
    distarr(end+1) = dist;
    
end
hold off
control_sphero_motion(xdes, ydes, x, y, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, 1);

    