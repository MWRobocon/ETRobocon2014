%% Initialise
videoPlayer = vision.VideoPlayer();
vid = imaq.VideoDevice('winvideo', 1);
vid.VideoFormat = 'RGB24_1280x720'
NFrame = 800;

%%
videoFrame = step(vid);
[centresDark, radiiDark] = imfindcircles(videoFrame, [30 90], 'ObjectPolarity', 'dark', 'Sensitivity', 0.95);

%%
imshow(videoFrame);
hold on;
viscircles(centresDark, radiiDark,'EdgeColor','r');

disp('Press any key to start camera live feed');
pause();

%% video feed

for ii = 1:NFrame
    
%     tic
videoFrame = step(vid);
% videoFrame = imwarp(videoFrame, MingTForm);
%     TimeReader(ii) = toc;
    
    % Track circle in the new frame
[centresDark, radiiDark] = imfindcircles(videoFrame, [40 80], 'ObjectPolarity', 'dark', 'Sensitivity', 0.95);
%     TimeTracker(ii) = toc;   
    
%     % Display tracked points
%     if ~isempty(visiblePoints)
%         videoFrame = insertMarker(videoFrame, visiblePoints, '+', ...
%             'Color', 'green', 'Size', 5);
%     end
%     
%     botMean = mean(visiblePoints); % Mean of all visible features
    botMean = centresDark(1,:);
%     TBotMean = transformPointsForward(MingTForm, botMean);
    position =  [50 50]; % [x y]
    videoFrame = insertText(videoFrame, position, int2str(botMean)); 
% 
    % Show the points on the output video
    videoFrame = insertMarker(videoFrame, botMean , 'x', 'Color', 'red', 'Size', 5);
%     videoFrame = insertMarker(videoFrame, botMean2 , 'x', 'Color', 'red', 'Size', 5);
%     
%     % Display the annotated video frame using the video player object
    step(videoPlayer, videoFrame);
% step(videoWriter, videoFrame);
%     TimePlayer(ii) = toc;
%     step(videoWriter, videoFrame);

end