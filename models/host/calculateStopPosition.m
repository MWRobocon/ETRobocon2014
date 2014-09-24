function p = calculateStopPosition(zumoCentroid)

zumo1_x = zumoCentroid(1,1);
zumo1_y = zumoCentroid(1,2);
zumo2_x = zumoCentroid(2,1);
zumo2_y = zumoCentroid(2,2);
scale = 1;

delta_x = abs(zumo1_x - zumo2_x);
delta_y = abs(zumo1_y - zumo2_y);

middlePos_x = (zumo1_x + zumo2_x)/2;
middlePos_y = (zumo1_y + zumo2_y)/2;

p1_x = middlePos_x - scale*delta_y;
p1_y = middlePos_y - scale*delta_x;

p2_x = middlePos_x + scale*delta_y;
p2_y = middlePos_y + scale*delta_x;

p = [p1_x p2_x; p1_y p2_y];
end

