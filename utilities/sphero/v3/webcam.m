function out = webcam(cam)
%WEBCAM M-Code for creating a video input object.
%   
%   This is the machine generated representation of a video input object.
%   This M-file, WEBCAM.M, was generated from the OBJ2MFILE function.
%   A MAT-file is created if the object's UserData property is not 
%   empty or if any of the callback properties are set to a cell array  
%   or to a function handle. The MAT-file will have the same name as the 
%   M-file but with a .MAT extension. To recreate this video input object,
%   type the name of the M-file, webcam, at the MATLAB command prompt.
%   
%   The M-file, WEBCAM.M and its associated MAT-file, WEBCAM.MAT (if
%   it exists) must be on your MATLAB path.
%   
%   Example: 
%       vidobj = webcam;
%   
%   See also VIDEOINPUT, IMAQDEVICE/PROPINFO, IMAQHELP, PATH.
%   

% Check if we can check out a license for the Image Acquisition Toolbox.
canCheckoutLicense = license('checkout', 'Image_Acquisition_Toolbox');

% Check if the Image Acquisition Toolbox is installed.
isToolboxInstalled = exist('videoinput', 'file');

if ~(canCheckoutLicense && isToolboxInstalled)
    % Toolbox could not be checked out or toolbox is not installed.
    errID = 'imaq:obj2mfile:invalidToolbox';
    error(errID, 'Image Acquisition Toolbox is not installed.');
end

% Load the MAT-file containing UserData and CallBack property values.
try
    MATvar = load('webcam');
    MATLoaded = true;
catch
    warnMsg = (['MAT-file could not be loaded. Object Properties whose values',...
        'were saved in the MAT-file will instead be configured to their default value.']);
    warning(warnMsg, 'imaq:obj2mfile:MATload');
   MATLoaded = false;
end


% Device Properties.
if cam ==1

    adaptorName = 'winvideo';
    deviceID = 1;
    vidFormat = 'RGB24_320x240';
    tag = '';
elseif cam==2
     adaptorName = 'winvideo';
    deviceID = 1;
    vidFormat = 'MJPG_320x240';
    tag = '';
end
% Search for existing video input objects.
existingObjs1 = imaqfind('DeviceID', deviceID, 'VideoFormat', vidFormat, 'Tag', tag);

if isempty(existingObjs1)
    % If there are no existing video input objects, construct the object.
    vidObj1 = videoinput(adaptorName, deviceID, vidFormat);
else
    % There are existing video input objects in memory that have the same
    % DeviceID, VideoFormat, and Tag property values as the object we are
    % recreating. If any of those objects contains the same AdaptorName
    % value as the object being recreated, then we will reuse the object.
    % If more than one existing video input object contains that
    % AdaptorName value, then the first object found will be reused. If
    % there are no existing objects with the AdaptorName value, then the
    % video input object will be created.

    % Query through each existing object and check that their adaptor name
    % matches the adaptor name of the object being recreated.
    for i = 1:length(existingObjs1)
        % Get the object's device information.
        objhwinfo = imaqhwinfo(existingObjs1{i});
        % Compare the object's AdaptorName value with the AdaptorName value
        % being recreated.
        if strcmp(objhwinfo.AdaptorName, adaptorName)
            % The existing object has the same AdaptorName value as the
            % object being recreated. So reuse the object.
            vidObj1 = existingObjs1{i};
            % There is no need to check the rest of existing objects.
            % Break out of FOR loop.
            break;
        elseif(i == length(existingObjs1))
            % We have queried through all existing objects and no
            % AdaptorName values matches the AdaptorName value of the
            % object being recreated. So the object must be created.
            vidObj1 = videoinput(adaptorName, deviceID, vidFormat);
        end %if
    end %for
end %if

% Configure properties whose values are saved in C:\MyStuff\Work\Demos2009b\BallTrackingDemo\demo\work\MLIntro\webcam.mat.
if (MATLoaded)
    % MAT-file loaded successfully. Configure the properties whose values
    % are saved in the MAT-file.
    set(vidObj1, 'ErrorFcn', MATvar.errorfcn1);
else
   % MAT-file could not be loaded. Configure properties whose values were
   % saved in the MAT-file to their default value.
    set(vidObj1, 'ErrorFcn', @imaqcallback);
end

% Configure vidObj1 properties.
% set(vidObj1, 'FramesPerTrigger', Inf);

set(vidObj1, 'FramesAcquiredFcnCount', 100);
set(vidObj1, 'FramesAcquiredFcn', @(h, e) flushdata(h));

set(vidObj1, 'TriggerRepeat', Inf);

% Configure vidObj1's video source properties.
% if exist('cameraSettings.mat', 'file')
%   s = load('cameraSettings.mat');
%   src = get(vidObj1, 'Source');
%   set(src, s.cameraSettings);
% end

out = vidObj1 ;
