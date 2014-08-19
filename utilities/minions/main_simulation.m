clear all; close all; clc;
x0 = [0 0]'; % initial condition of the minion
%% static target @(0,0)
xref = 5;
yref = 5;
[t,y] = ode45(@(t,y)minion_limitCycle(t,y,xref,yref), [0 10], x0);
plot(y(:,1), y(:,2), '*', xref, yref, 'd');
legend('minion', 'target')
title('Minion going around a static target')
%% moving target - run this section later
dt_target = 0.1;
dt_minion = 0.01;
t_target = 0:dt_target:15;
xref = 2 + t_target; %adding 2 (random) to just start at a non-zero x
yref = 3 + sin(xref); % adding 3(random) for moving the output of sine wave above 0

% making sure the first 5 sec the target does not move
t_start_static = find(t_target == 5); %finding the index of t = 5 secs
for i=1:1:t_start_static
    xref(i) = xref(t_start_static);
    yref(i) = yref(t_start_static);
end

% NOTE : Target moves only from 5sec-10sec

% making sure the last 5 sec the target does not move
t_end_static = find(t_target == 10); %finding the index of t = 10 secs
for i=t_end_static:1:length(t_target)
    xref(i) = xref(t_end_static);
    yref(i) = yref(t_end_static);
end

yfinal = x0; %storage variable
x = x0; % initial condition

% capturing the current position of the minion and the target
figure
h_minion = plot(yfinal(1), yfinal(2), '*'); hold on;
h_target = plot(xref(1), yref(1), 'd'); hold on;
legend('minion', 'target')
title('Minion going around a moving target')

for i=1:length(t_target) - 1
    t_minion = t_target(i):dt_minion:t_target(i+1);
    for j = 1:length(t_minion)
        % integrate for one time step only
        dx = minion_limitCycle(t_minion(j), x, xref(i), yref(i));
        x = x + dx*dt_minion;
        % storing the data
        yfinal = [yfinal x];
    end
    set(h_minion, 'XData', yfinal(1,:), 'YData', yfinal(2,:)); 
    set(h_target, 'XData', xref(1:i), 'YData', yref(1:i)); 
    drawnow;
end 