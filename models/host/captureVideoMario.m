% Test script to track mario only

vid = imaq.VideoDevice('winvideo');

pause(3);

z1.write(20,1);
z2.write(20,1);
pause(5);
z1.write(0,1);
z2.write(0,1);
pause(2);
z1.write(20,1);
z2.write(20,1);
pause(8);
z1.write(0,1);
z2.write(0,1);