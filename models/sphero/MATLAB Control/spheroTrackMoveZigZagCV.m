function [distArr, posArr, angleArr, uArr, time] = spheroTrackMoveZigZagCV(pos,sph)
clf;
%% Move sphero to particular point, based on feedback from camera
try
    tfinal = 30;
    maxspeed = 150; minspeed = -100; restartspeed = 65; 
    stopRadius = 50; 
    % Controller Gains
    Kp = 0.2;
    Ki = 0;
    Kd = 0;   
    
    xdeslist = pos(:,1);
    ydeslist = pos(:,2);
    xdes = xdeslist(1);
    ydes = ydeslist(1);
    
    vid = imaq.VideoDevice('winvideo');
    vid.VideoFormat = 'MJPG_640x480';
    vid.ReturnedDataType = 'single';
    vid.DeviceProperties.FocusMode = 'manual';
    
    frame = step(vid);
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
%     initialPosition = findBall(vid);
     
    %reset detectMinions2 function
    [~, initialPosition] = detectMinions2(frame, 1);

    [stopCircleX,stopCircleY] = getCircleCoordinates([xdes,ydes],stopRadius);
    
    figure(1);
    hold on;
    imagesc(initialFrame);
    plot(initialPosition(1),initialPosition(2),'rx');
    plot(xdes,ydes,'ro');
    plot(stopCircleX,stopCircleY,'r');
    hold off;
    
    keyboard;
    
    moveSphero2(0, 0, 0, 0, 0, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed,1)
%     moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,1);
    idx = 1;
    listnum = length(xdeslist);
    
    t0 = cputime;
    time(1) = cputime-t0;
    while(time(end)<tfinal) && idx<=listnum 
        
        xdes = xdeslist(idx);
        ydes = ydeslist(idx);
        
%         pos = findBall(vid);
        frame = step(vid);
        [~, pos] = detectMinions2(frame);
        xpos = pos(1);
        ypos = pos(2);
        
        if length(distArr)<=5
            avgSpeed = abs(mean(distArr));
        else
            avgSpeed = abs(mean(diff(distArr(end-5:end))));
        end
        if xpos > 0 || ypos > 0
            [dist, angle, u] = moveSphero2(xdes, ydes, xpos, ypos, avgSpeed, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed,0);
            
            roll(sph, u, angle)
            %             [dist, angle, u] = moveSphero(sph, xdes, ydes, xpos, ypos, avgSpeed, stopRadius,0);
        else
            dist = inf;
            angle = 0;
            u=0;
            roll(sph, u, angle);
        end
        
        posArr(end+1, :, idx) = pos;
        distArr(end+1) = dist;
        angleArr(end+1) = angle;
        uArr(end+1) = u;
        
        if dist<stopRadius && avgSpeed<1
            idx = idx+1;
        end
       time(end+1) = cputime-t0;
    end
    
    moveSphero2(0, 0, 0, 0, 0, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed,1)
%     moveSphero(sph, 0, 0, 0, 0, 1,stopRadius,0);
    % stop(vid);
    release(vid);
    clear sph
    
    colors = ['b', 'r', 'y', 'g', 'k', 'c', 'm'];
    
    figure(2);
    hold on;
    for i=1:listnum
        plot(posArr(:,1, i),posArr(:,2, i), [colors(i) 'x']);
        
        plot(xdeslist(i),ydeslist(i),[colors(i) '-']);
        [stopCircleX,stopCircleY] = getCircleCoordinates([xdeslist(i),ydeslist(i)],stopRadius);
        plot(stopCircleX,stopCircleY);

    end
    
    plot(posArr(end,1),posArr(end,2),'gx');
    xlim([0 640]);
    ylim([0 480]);
    hold off;
    
catch exception
    %sph = sphero('Sphero-PGP');
    moveSphero2(0, 0, 0, 0, 0, Kp, Ki, Kd, stopRadius, maxspeed, minspeed, restartspeed,1)
%     if exist('sph', 'var')
%         clear sph
%     end
    if exist('vid', 'var')
        %         stop(vid);
        release(vid);
    end
    rethrow(exception)
end
end

function  [x,y] = getCircleCoordinates(center,r)
    theta = 0:0.01:2*pi;
    x = r*cos(theta) + center(1);
    y = r*sin(theta) + center(2);
end

