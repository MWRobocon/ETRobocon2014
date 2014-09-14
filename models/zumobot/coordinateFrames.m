th_d = 120;
th_r = th_d*pi/180;


R_rc = [1 0;0 -1];
R_rm = RotZ(th_r);
% R_rc = R_rm*R_mc;
% R_mc = R_rc\R_rm;
R_mc = R_rc\R_rm;

% camera frame coordinate
r_c = [1; 1];

r_r = R_rm*R_mc*r_c;



