function [v1, v2] = detectCollision(r1, v1, r2, v2)
% assuming that using computer vision, we can identify which robot is
% behind, using 1- ahead, 2-behind terminology
persistent robotSlowedDown
if isempty(robotSlowedDown)
    robotSlowedDown = 0;
end

gap = sqrt(sum((r1-r2).^2));
gap_threshold = 30;
collisionDetected = gap < gap_threshold;

if collisionDetected
    if ~robotSlowedDown
        % reduce velocity of the robot behind
        v2 = v2/10;
        robotSlowedDown = 1;
    end
else
    if robotSlowedDown
        v2 = v2*10;
    end
end

