SpheroPos = logsout.getElement('').Values.SpheroOrange.Data;

figure; 
plot(SpheroPos(:,1), SpheroPos(:, 2), 'kx');
% hold on; 
% plot(points(:, 1), points(:, 2), 'ro');
% hold off
axis([0 640 0 480])

% distEnd =  pdist([points(end, :); SpheroPos.signals.values(end, :)])