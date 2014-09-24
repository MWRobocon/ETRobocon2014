function [distArr, posArr, angleArr, uArr] = spheroTrackMoveZigZag(pos,sph)
clf;
%% Move sphero to particular point, based on feedback from camera
stopRadius = 50;

try
    tfinal = 20;
    xdeslist = pos(:,1);
    ydeslist = pos(:,2);
    xdes = xdeslist(1);
    ydes = ydeslist(1);
    
    vid = imaq.VideoDevice('winvideo');
    vid.VideoFormat = 'MJPG_640x480';
    vid.ReturnedDataType = 'single';
    vid.DeviceProperties.FocusMode = 'manual';
    
    step(vid);
    % vid = webcam(1);
    % sph = sphero(sphName);
    %sph = sphero('Sphero-PGP');
    %
    %
    sph.BackLEDBrightness = 255;
    
    
    posArr = [];
    distArr = [];
    angleArr = [];
    uArr = [];
    
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
    idx = 1;
    listnum = length(xdeslist);
    
    t0 = cputime;
    while(cputime-t0<tfinal)
        xdes = xdeslist(idx);
        ydes = ydeslist(idx);
        
        pos = findBall(vid);
        xpos = pos(1);
        ypos = pos(2);
        
        if length(distArr)<=5
            avgSpeed = abs(mean(distArr));
        else
            avgSpeed = abs(mean(diff(distArr(end-5:end))));
        end
        if xpos > 0 || ypos > 0
            [dist, angle, u] = moveSphero(sph, xdes, ydes, xpos, ypos, avgSpeed, stopRadius,0);
        else
            dist = inf;
            angle = 0;
            u=0;
            roll(sph, u, angle);
        end
        
        if dist<stopRadius && idx<listnum && avgSpeed<1
            idx = idx+1;
        end
        posArr(end+1, :) = pos;
        distArr(end+1) = dist;
        angleArr(end+1) = angle;
        uArr(end+1) = u;
    end
    
    moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,0);
    % stop(vid);
    release(vid);
    clear sph
    
    
    figure(2);
    hold on;
    plot(posArr(:,1),posArr(:,2),'r--');
    xlim([0 640]);
    ylim([0 480]);
    for i=1:listnum
        plot(xdeslist(i),ydeslist(i),'bo');
        [stopCircleX,stopCircleY] = getCircleCoordinates([xdeslist(i),ydeslist(i)],stopRadius);
        plot(stopCircleX,stopCircleY);
    end
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

