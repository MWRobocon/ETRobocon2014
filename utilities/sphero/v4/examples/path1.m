r = 25;
xc1 = 0; yc1 = 75;
th1 = 90:30:270;
xdeslist1 = xc1+r*cos(th1*2*pi/360);
ydeslist1 = yc1+r*sin(th1*2*pi/360);

xc2 = 0; yc2 = 25;
th2 = 90:-30:-90;
xdeslist2 = xc2+r*cos(th2*2*pi/360);
ydeslist2 = yc2+r*sin(th2*2*pi/360);

xdeslist = [xdeslist1 xdeslist2];
ydeslist = [ydeslist1 ydeslist2];