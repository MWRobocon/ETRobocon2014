function colorsPlot(red, green, blue, justGreen)
%CREATEFIGURE(red,green,blue,justGreen)
%  red:  image cdata
%  green:  image cdata
%  blue:  image cdata
%  justGreen:  image cdata

%  Auto-generated by MATLAB on 12-Nov-2007 09:55:06

% Create figure
figure1 = figure('Colormap',...
    [0 0 0;0.01587 0.01587 0.01587;0.03175 0.03175 0.03175;0.04762 0.04762 0.04762;0.06349 0.06349 0.06349;0.07937 0.07937 0.07937;0.09524 0.09524 0.09524;0.1111 0.1111 0.1111;0.127 0.127 0.127;0.1429 0.1429 0.1429;0.1587 0.1587 0.1587;0.1746 0.1746 0.1746;0.1905 0.1905 0.1905;0.2063 0.2063 0.2063;0.2222 0.2222 0.2222;0.2381 0.2381 0.2381;0.254 0.254 0.254;0.2698 0.2698 0.2698;0.2857 0.2857 0.2857;0.3016 0.3016 0.3016;0.3175 0.3175 0.3175;0.3333 0.3333 0.3333;0.3492 0.3492 0.3492;0.3651 0.3651 0.3651;0.381 0.381 0.381;0.3968 0.3968 0.3968;0.4127 0.4127 0.4127;0.4286 0.4286 0.4286;0.4444 0.4444 0.4444;0.4603 0.4603 0.4603;0.4762 0.4762 0.4762;0.4921 0.4921 0.4921;0.5079 0.5079 0.5079;0.5238 0.5238 0.5238;0.5397 0.5397 0.5397;0.5556 0.5556 0.5556;0.5714 0.5714 0.5714;0.5873 0.5873 0.5873;0.6032 0.6032 0.6032;0.619 0.619 0.619;0.6349 0.6349 0.6349;0.6508 0.6508 0.6508;0.6667 0.6667 0.6667;0.6825 0.6825 0.6825;0.6984 0.6984 0.6984;0.7143 0.7143 0.7143;0.7302 0.7302 0.7302;0.746 0.746 0.746;0.7619 0.7619 0.7619;0.7778 0.7778 0.7778;0.7937 0.7937 0.7937;0.8095 0.8095 0.8095;0.8254 0.8254 0.8254;0.8413 0.8413 0.8413;0.8571 0.8571 0.8571;0.873 0.873 0.873;0.8889 0.8889 0.8889;0.9048 0.9048 0.9048;0.9206 0.9206 0.9206;0.9365 0.9365 0.9365;0.9524 0.9524 0.9524;0.9683 0.9683 0.9683;0.9841 0.9841 0.9841;1 1 1]);

% Create subplot
subplot1 = subplot(2,2,1,'Parent',figure1,'YDir','reverse','Layer','top');
% Uncomment the following line to preserve the X-limits of the axes
 xlim([0.5 320.5]);
% Uncomment the following line to preserve the Y-limits of the axes
 ylim([0.5 240.5]);
box('on');
hold('all');

% Create image
image(red,'Parent',subplot1,'CDataMapping','scaled');

% Create title
title('Red');

% Create subplot
subplot2 = subplot(2,2,2,'Parent',figure1,'YDir','reverse','Layer','top');
% Uncomment the following line to preserve the X-limits of the axes
 xlim([0.5 320.5]);
% Uncomment the following line to preserve the Y-limits of the axes
 ylim([0.5 240.5]);
box('on');
hold('all');

% Create title
title('Green');

% Create image
image(green,'Parent',subplot2,'CDataMapping','scaled');

% Create subplot
subplot3 = subplot(2,2,3,'Parent',figure1,'YDir','reverse','Layer','top');
% Uncomment the following line to preserve the X-limits of the axes
 xlim([0.5 320.5]);
% Uncomment the following line to preserve the Y-limits of the axes
 ylim([0.5 240.5]);
box('on');
hold('all');

% Create title
title('Blue');

% Create image
image(blue,'Parent',subplot3,'CDataMapping','scaled');

% Create subplot
subplot4 = subplot(2,2,4,'Parent',figure1,'YDir','reverse','Layer','top');
% Uncomment the following line to preserve the X-limits of the axes
 xlim([0.5 320.5]);
% Uncomment the following line to preserve the Y-limits of the axes
 ylim([0.5 240.5]);
box('on');
hold('all');

% Create title
title('Just Green');

% Create image
image(justGreen,'Parent',subplot4,'CDataMapping','scaled');

