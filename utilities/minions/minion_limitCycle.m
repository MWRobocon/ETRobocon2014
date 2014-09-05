function dx = minion_limitCycle(t, x, xref, yref)
dx = zeros(2,1);
% radius of 1 unit around the target point (xref, yref)
dx(1) = x(2) - yref + (x(1) - xref)*(1 - (x(1) - xref)^2 - (x(2) - yref)^2);
dx(2) = -(x(1) - xref) + (x(2) - yref)*(1 - (x(1) - xref)^2 - (x(2) - yref)^2);