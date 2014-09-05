function [distArr, posArr, angleArr] = spheroTrackMove(pos,sph)
clf;
%% Move sphero to particular point, based on feedback from camera
stopRadius = 50;

try
    tfinal = 10;
    xdes = pos(1);
    ydes = pos(2);
    
    vid = imaq.VideoDevice('winvideo');
    vid.VideoFormat = 'MJPG_640x480';
    vid.ReturnedDataType = 'single';
    step(vid);
    % vid = webcam(1);
    % sph = sphero(sphName);
    %sph = sphero('Sphero-PGP');
    %
    %
    sph.BackLEDBrightness = 255;
    
    t0 = cputime;
    posArr = [];
    distArr = [];
    angleArr = [];
    
    initialFrame = vid.step();
    initialPosition = findBall(vid);
    [stopCircleX,stopCircleY] = getCircleCoordinates([xdes,ydes],stopRadius);
    
    figure(1);
    hold on;
    imagesc(initialFrame);
    plot(initialPosition(1),initialPosition(2),'rx');
    plot(xdes,ydes,'ro');
    plot(stopCircleX,stopCircleY,'r');
    hold off;
    
    keyboard;
    
    moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,1);
    while(cputime-t0<tfinal)
        pos = findBall(vid);
        xpos = pos(1);
        ypos = pos(2);
        
        if length(distArr)<=5
            avgSpeed = mean(distArr);
        else
            avgSpeed = mean(diff(distArr(end-5:end)));
        end
        if xpos > 0 || ypos > 0
            [dist, angle, u] = moveSphero(sph, xdes, ydes, xpos, ypos, avgSpeed, stopRadius,0);
        else
            dist = inf;
            angle = 0;
            u=0;
        end
        posArr(end+1, :) = pos;
        distArr(end+1) = dist;
        angleArr(end+1) = angle;
    end
    
    moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,0);
    % stop(vid);
    release(vid);
    clear sph
    
    
    figure(2);
    hold on;
    plot(posArr(:,1),posArr(:,2),'r--');
    xlim([0 480]);
    ylim([0 640]);
    plot(xdes,ydes,'bo');
    plot(stopCircleX,stopCircleY);
    plot(posArr(end,1),posArr(end,2),'gx');
    hold off;
    
catch exception
    %sph = sphero('Sphero-PGP');
    moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,0);
%     if exist('sph', 'var')
%         clear sph
%     end
    if exist('vid', 'var')
        %         stop(vid);
        release(vid);
    end
    throw(exception)
end
end

function  [x,y] = getCircleCoordinates(center,r)
    theta = 0:0.01:2*pi;
    x = r*cos(theta) + center(1);
    y = r*sin(theta) + center(2);
end

    