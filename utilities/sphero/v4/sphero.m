classdef sphero<handle
    %SPHERO Connect and communicate with Sphero
    %   
    % obj = SPHERO() creates a connection to Sphero and assigns the 
    % connection to a handle. If you do not indicate the name of the device
    % to connect to, it searches for the paired Sphero devices and asks user
    % to select one of them to connect to
    % obj = SPHERO(DEVICENAME) connects to the indicated device through
    % the default communication protocol 
       
    properties
        ResponseTimeout = 1; % Timeout for response to be received from Sphero (in seconds)
        BackLEDBrightness; % Brightness of the LED which indicates the back of the Sphero
        
        % Accelerometer Range
        % 0 indicates a range from -2G to +2G of acceleration, where G represents the acceleration due to gravity. 
        % 1 indicates -4G to 4G
        % 2 indicates -8G to 8G (default value. Required for Collision Detection to be accurate
        % 3 indicates -16G to 16G
        AccRange = 2;
        
        %Timeout for the last motion command (in seconds) (default = 2)
        % Modify this value if you would like the 'roll' commands to keep
        % the sphero rolling, instead of stopping after some time.
        MotionTimeout;  
        
        % Timeout for inactivity (in seconds) (default = 600)
        % Sphero would go to sleep after the specified period of
        % inactivity. The inactivity timer is reset every time an API
        % command is received ver Bluetooth
        InactivityTimeout;
        
        CollisionDetection = 0; % Toggle Collision Detection
        
        %NOTE: To be considered in future
%         PermOptions %would have a set method
%         TempOptions %would have a set method
%        
    end
    
    properties(Hidden=true)
        Api % Object to the CommunicationApi that is used by Sphero
        Listeners % Listeners used for processing asynchronous responses
        SaveLedColor = 1; % Whether LED Color should persist across power cycles 
        CommunicationApi = 'BluetoothApi'; %Specify which child of CommunicationApi class is to be used for the current version       
    end
    
    properties(Access = {?sphero, ?BluetoothApi})
       % Temporarily save the data from the sensors being polled, before saving them to a file
       % It is a struct with the following fields:
       %    filename
       %    sensors
       %    freq
       %    samples
       %    samplesPerPacket
       %    packets
       %    prevValues - a struct with the name of sensors being polled as
       %                the field. Required as the previous values in file
       %                are overwritten when saving the data with same
       %                variable name. Otherwise the file would have to be
       %                read at every iteration, when a new packet has to
       %                be saved to file.
       SensorPolling 
    end
    
    properties (Dependent=true)
        Handshake; %Toggle handshaking between PC and Sphero
        Color; % LED Color on the Sphero

    end
    
     properties (Dependent=true, SetAccess = private)
       Status % Status of connection with Sphero

    end
    
    properties(Access = private, Constant)
        RateResolution = 0.784; % Resolution of Rotation Rate of sphero
        RateMax = 400; % Maximum possible Rotation rate
    end
    
    methods(Static, Access = private)
        function varargout = simpleResponse(response)
        % Checks if received response is valid or not
            % SIMPLERESPONSE(RESPONSE) would error out if the response is invalid
            % valid = SIMPLERESPONSE(RESPONSE) returns 1 if rerponse is
            % invalid, otherwise it will return 0
                if nargout
                if isempty(response)
                    varargout{1} = 1;
                else
                    varargout{1} = 0;
                end
            else
                if ~isempty(response)
                    err = MException('Sphero:InvalidSimpleResponse', 'Invalid response received');
                    throwAsCaller(err);
                end
            end
        end
        
        function [Mask, Mask2] = DataStreamingMask(sensors)
        % Create the Masks that are used to create the command to stream
        % sensor data from Sphero
        
            Mask = uint32(0);
            Mask2 = uint32(0);
                       
            for i=1:length(sensors)
                switch sensors{i}
                    case'accelX'
                        Mask = bitset(Mask, 32);
                    case 'accelY'
                        Mask = bitset(Mask, 31);
                    case 'accelZ'
                        Mask = bitset(Mask, 30);
                    case 'gyroX'
                        Mask = bitset(Mask, 29);
                    case 'gyroY'
                        Mask = bitset(Mask, 28);
                    case 'gyroZ'
                        Mask = bitset(Mask, 27);
                    case 'rmotorEmfRaw'
                        Mask = bitset(Mask, 23);
                    case 'lmotorEmfRaw'
                        Mask = bitset(Mask, 22);
                    case 'lmotorPwmRaw'
                        Mask = bitset(Mask, 21);
                    case 'rmotorPwmRaw'
                        Mask = bitset(Mask, 20);
                    case 'imuPitch'
                        Mask = bitset(Mask, 19);
                    case 'imuRoll'
                        Mask = bitset(Mask, 18);
                    case 'imuYaw'
                        Mask = bitset(Mask, 17);
                    case 'accelXFilt'
                        Mask = bitset(Mask, 16);
                    case 'accelYFilt'
                        Mask = bitset(Mask, 15);
                    case 'accelZFilt'
                        Mask = bitset(Mask, 14);
                    case 'gyroXFilt'
                        Mask = bitset(Mask, 13);
                    case 'gyroYFilt'
                        Mask = bitset(Mask, 12);
                    case 'gyroZFilt'
                        Mask = bitset(Mask, 11);
                    case 'rmotorEmfFilt'
                        Mask = bitset(Mask, 7);
                    case 'lmotorEmfFilt'
                        Mask = bitset(Mask, 6);
                    case 'Q0'
                        Mask2 = bitset(Mask2, 32);
                    case 'Q1'
                        Mask2 = bitset(Mask2, 31);
                    case 'Q2'
                        Mask2 = bitset(Mask2, 30);
                    case 'Q3'
                        Mask2 = bitset(Mask2, 29);
                    case 'distX'
                        Mask2 = bitset(Mask2, 28);
                    case 'distY'
                        Mask2 = bitset(Mask2, 27);
                    case 'accelOne'
                        Mask2 = bitset(Mask2, 26);
                    case 'velX'
                        Mask2 = bitset(Mask2, 25);
                    case 'velY'
                        Mask2 = bitset(Mask2, 24);
                    otherwise
                        err = MException('pollSensors:IncorrectInput', ...
                            'Undefined sensor name');
                        throw(err);
                end
            end
        end
        
       
        function powerNotify(~, eventdata) 
        % Callback for Listener for PowerNotification property of
        % CommunicationApi. By default it will just display a warning.
        %src.Name will be 'PowerNotification'
        
            warning(eventdata.AffectedObject.PowerNotification);
            lastwarn(''); %Added so that instrcb.m does not display the warning again
        end
        
        function preSleepWarning(~, eventdata)
        % Callback for Listener for PreSleepWarning property of
        % CommunicationApi. By default it will just display a warning.
        
            if eventdata.AffectedObject.PreSleepWarning
                warning('Sphero is about to sleep due to inactivity');
                lastwarn(''); %Added so that instrcb.m does not display the warning again
            end
               
        end
        
        function collisionDetection(~, eventdata)
        % Callback for Listener for CollisionDetection property of
        % CommunicationApi. By default it will just display a warning
        
            warning('Collision occured along %c-direction', eventdata.AffectedObject.CollisionDetected);
            lastwarn(''); %Added so that instrcb.m does not display the warning again
        end
        
        function gyroAxisLimitExceed(~, ~)
        % Callback for Listener for GyroAxisLimitExceed property of
        % CommunicationApi. By default it will just display a warning
        
            warning('Gyro Axis Limit Exceeded');
            lastwarn(''); %Added so that instrcb.m does not display the warning again
        end
    end
    
    methods(Access = private)
                      
        function sensorDataStreaming(obj, ~, ~)
        %Callback for Listener for the SensorData property, for Logging the
        %sensor data

            if isempty(obj.SensorPolling.filename)
                warning(['Sphero is sending Sensor Data that is to be polled'...
                    ', but settings for saving the sensor data have'...
                    ' not been set.']);
                return
            end
            
            if isempty(obj.Api.SensorData)
%                 warning('SensorData property not set')
                return
            end
            
            %Loop through the list of sensors, add the current packet data
            %to obj.SensorPolling.prevValues and save the sensor data to file
            for i=1:length(obj.SensorPolling.sensors)
                if ~isfield(obj.Api.SensorData, obj.SensorPolling.sensors{i})
                    return
                end
                    
                currData = obj.Api.SensorData.(obj.SensorPolling.sensors{i});
                prevData = obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i});
                
                prevData(end+1:end+length(currData)) = currData;
                
                values.(obj.SensorPolling.sensors{i}) = prevData;
                obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i}) = prevData;
           end
            
            save(obj.SensorPolling.filename, 'values', '-append');

            samplesRemaining = obj.SensorPolling.samples-length(values.(obj.SensorPolling.sensors{1}));
             
             if samplesRemaining<=0
                 obj.SensorPolling.filename =[];
                 obj.SensorPolling.freq = [];
                 obj.SensorPolling.samples = [];
                 obj.SensorPolling.samplesPerPacket = [];
                 obj.SensorPolling.packets = [];
                 obj.SensorPolling.sensors = [];
                 obj.SensorPolling.prevValues = [];
                 delete(obj.Listeners.SensorDataList);
                 
             end

        end
        
         function varargout = heading(obj, angle)
         % Adjust the heading direction of the sphero
            % HEADING(SPH, ANGLE) sets the new heading to ANGLE, where ANGLE
            % is in degrees
         
            nargoutchk(0, 1)
             
            angle = mod(angle, 360);
            [responseexpected, seq] = sendCmd(obj.Api, 'setcal', [], [], [], angle);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
        
        function varargout = stabilization(obj, flag)
        % Toggle the stabilization
            % STABILIZATION(SPH, FLAG) toggles the stabilization property
            % of the Sphero based on the FLAG value
            nargoutchk(0, 1)
            p = inputParser;
            addRequired(p, 'flag', @(x) isnumeric(x) && (x==0 || x==1));
            parse(p, flag);
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setstabiliz', [], [], [], flag);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
    
        function varargout = configureCollisionDetection(obj, method, xt, xspd, yt, yspd, dead)
        % Configure the options for Collision Detection
            % CONFIGURECOLLISIONDETECTION(SPH, METHOD, XT, XSPD, YT, YSPD, DEAD)
            % sets the following options for the collision detection
            % METHOD: 0 to disable, 1 to enable collision detection
            % XT, YT: Threshold for X and Y axes of Sphero, at speed 0  
            % XSPD, YSPD: Value added to XT and YT at maximum speed, for
            % the threshold at maximum speed
            % DEAD  : Dead time to prevent retrigerring. Specified in ms 
             p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'method', @(x) isnumeric(x) && (x==0 || x==1));
            addRequired(p, 'xt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'xspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'dead', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8')); %Specified in ms. Sphero requires dead time in 10ms increments
            parse(p, obj, method, xt, xspd, yt, yspd, dead);
            
            nargoutchk(0, 1)
             
            if obj.AccRange~=2
                warning(['Collision detection feature relies on accelerometer'... 
                    ' range being set to +-8Gs. As the accelerometer range'...
                    ' has been modified, collision detection feature might'...
                    '  not work as intended']);
            end
            
            try
                [responseexpected, seq] = sendCmd(obj.Api, 'setcollisiondet', [], [], [],  p.Results.method, p.Results.xt, p.Results.xspd, p.Results.yt, p.Results.yspd, p.Results.dead/10);

                response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);

                [varargout{1:nargout}] = sphero.simpleResponse(response);
            catch exception
                throwAsCaller(exception)
            end
            
        end
    end
    
    methods
        function obj = sphero(varargin)
        %SPHERO    Create an object of class sphero 
            % obj = SPHERO() searches for the paired Sphero devices and asks user
            % to select one of them to connect to
            % obj = SPHERO(DEVICENAME) connects to the indicated device through
            % the communication protocol 
            % obj = SPHERO(DEVICENAME, CONNECT) connects to the device if CONNECT
            % is logically true. Otherwise it just creates an object
            % without connecting to the device
            % obj = SPHERO(DEVICENAME, CONNECT, COMMUNICATIONAPI) connects 
            % to the device using the indicated COMMUNICATIONAPI if 
            % CONNECT is logically true. COMMUNICATIONAPI is a string,
            % which corresponds to the name of a class which inherits from
            % 'Communication' class under sphero.internal package and is
            % present in the package
            
            import('sphero.*') %Import sphero package so that the 
            % classes inside 'internal' package can be accessed through
            % Dynamic Field Referencing
            
            obj.Api = internal.(obj.CommunicationApi);
            
           if nargin>1
               if varargin{2}
                    connect(obj, varargin{1});
               end   
           else
               connect(obj, varargin{:});
           end
           
           % Set the default values of the properties which have associated
           % set Methods
           obj.Handshake = 0;
           obj.BackLEDBrightness = 0;
           obj.MotionTimeout = 2;
           obj.InactivityTimeout = 600;
           obj.AccRange = 2;
           
            obj.SensorPolling = struct('filename', [], 'freq', [], ...
                'samples', [], 'samplesPerPacket', [], 'packets', [], ...
                'sensors', [], 'prevValues', [], 'presentValues', []);
            
           %% Add listeners to the events, with callbacks set to the 
           %default callback functions
           obj.Listeners.PowerNotificationList = addlistener(obj.Api, 'PowerNotification',  'PostSet',  @sphero.powerNotify);
           obj.Listeners.PreSleepWarningList = addlistener(obj.Api, 'PreSleepWarning', 'PostSet', @sphero.preSleepWarning);
           obj.Listeners.CollisionDetectionList = addlistener(obj.Api, 'CollisionDetected', 'PostSet', @sphero.collisionDetection);
           obj.Listeners.GyroAxisLimitExceedList = addlistener(obj.Api, 'GyroAxisLimitExceed', 'PostSet', @sphero.gyroAxisLimitExceed);
           
        end
        
        function result = ping(obj)
        % PING Ping the Sphero to check the connection and whether the Sphero is awake and active
            % RESULT = PING(SPH) returns the result of the ping as 1 if the
            % connection is active. Otherwise it returns 0.
            
            [responseexpected, seq] = sendCmd(obj.Api, 'ping', [], 1);
           
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);

            if isempty(response)
                result = 1;
            else
                result = 0;
            end
            
        end
        
                   
        function connect(obj, varargin)
        % CONNECT Connect to Sphero
            % CONNECT(SPH) would connect to the previous Sphero device if
            % it is detected. Otherwise it will search for paired devices
            % and prompt the user to select one
            % CONNECT(SPH, DEVICENAME) would try to connect to the
            % specified device
             connect(obj.Api, varargin{:});
        end
        
        
        function varargout = roll(obj, speed, heading)
        % ROLL Move the Sphero along a specific direction
            % ROLL(SPH, SPEED, HEADING) would cause the Sphero to move
            % at the angle specified by HEADING, with speed of SPEED.
            % HEADING is specified with regards to the original orientation
            % that is set when the Sphero is first connected, or calibrated
            % to. 
            % SPEED can be between -255 and 255
            %
            % RESULT = ROLL(SPH, SPEED, HEADING) would return 1 if the
            % command succeeds. Otherwise it returns 0.
            
             nargoutchk(0, 1)
             
             if speed>255||speed<-255
                error('Please enter a value for SPEED that is between -255 and 255');
             elseif speed<0
                 heading = heading+180;
                 speed = abs(speed);
            end

            heading = mod(heading, 360);
                          
            [responseexpected, seq] = sendCmd(obj.Api, 'roll', [], [], [], speed, heading, 1);
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
        function varargout = brake(obj)
        % BRAKE Apply optimal braking to stop the Sphero
            % BRAKE(SPH) would apply optimal braking to zero speed
            % RESULT = BRAKE(SPH) returns 1 if the command succeeds,
            % otherwise it returns 0
               nargoutchk(0, 1)
             
              [responseexpected, seq]  = sendCmd(obj.Api, 'roll', [], [], [], 0, 0, 0);
              response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
       
        function pollSensors(obj, rate, varargin)
        % pollSensors Poll the Sphero for specific sensor data, and save the data to a file.
            % POLLSENSORS(sph, rate) saves the data of the distance
            % travelled along x and y direction of the robot (based on
            % initial orientation) in a MAT file that is named log.mat by
            % default. The sensors will be polled indefinitely at the rate 
            % specified by RATE (0-400Hz), with 1 value per packet being 
            % transmitted back to the machine
            %
            % pollSensors(SPH, RATE, FRAMESPERPACKET, PACKETS) can be used
            % to configure the number of frames to be relayed back to the 
            % Sphero per packet, and also specify the number of packets to
            % be returned for the current sensors that are being polled
            % (distX and distY by default)
            %
            %  These input parameters can be followed by  parameter/value 
            %  pairs to specify additional properties, such as:
            % 'sensorname'  : Cell array of sensors to be polled
            % 'filename'    : Name of MAT file to which data should be saved
            % 'append'      : Specify 1 in order to append data to the file
            % 
            % For example: pollSensors(sph, RATE, 'sensorname', {'accelX', 'accelY'}, 'filename', 'myfile.mat', 'append', 1) 
            
            %Arguments
            % 1. Sphero object
            % 2. Rate at which sensors are to be polled 
            % 3. framesPerPacket:Number of frames to be transmitted per
            % packet that is sent (default = 1)
            % 4. packets: Number of packets to be transmitted (default = 0,
            % unlimited)
            % NVP: sensorname, file, format, append
            p = inputParser;
            
            defaultFramesPerPacket = 1;
            defaultPackets = 0;
            defaultSensors = {'distX', 'distY'};
            defaultFilename = 'log.mat';
            
            checkFramesPerPacket = @(x) isnumeric(x) && isscalar(x) && (x>0);
            
            checkPackets = @(x) isnumeric(x) && isscalar(x) && (x>=0) && ...
                (x<=intmax('uint8'));
            
            function valid = checkSensorName(x, validSensors)
                if iscell(x)
                    valid = all(cell2mat(cellfun(@(y) any(validatestring(y, validSensors)), x, 'UniformOutput', false)));
                else
                    valid = any(validatestring(x, validSensors));
                end
            end
            
            function valid = checkFilename(x)
               [pathstr,name,ext] = fileparts(x);
               if isempty(ext)
                   ext = '.mat';
               elseif ~strcmp(ext, '.mat')
                   error('Sphero:FileExt', 'File extension should be MAT');
               end
               
               filename = fullfile(pathstr, [name, ext]);
               fileId = fopen(filename, 'a');
               
               if fileId~=-1
                   valid=1;
                   fclose(fileId);
               else
                   valid = 0;
                   error('Sphero:UnableToOpenFile', 'Cannot open the file %s', filename)
               end
               
               
            end
            validSensors = {'accelX', 'accelY', 'accelZ', 'gyroX', 'gyroY', ...
                'gyroZ', 'rmotorEmfRaw', 'lmotorEmfRaw', 'lmotorPwmRaw', ...
                'rmotorPwmRaw', 'imuPitch', 'imuRoll', 'imuYaw', ...
                'accelXFilt', 'accelYFilt', 'accelZFilt', 'gyroXFilt', ...
                'gyroYFilt', 'gyroZFilt', 'rmotorEmfFilt', 'lmotorEmfFilt', ...
                'Q0', 'Q1', 'Q2', 'Q3', 'distX', 'distY', 'accelOne', ...
                'velX', 'velY'};
            
            addRequired(p, 'objectname')
            addRequired(p, 'rate', @(x) isnumeric(x) && x>=0 && x<=400);
            addOptional(p, 'framesPerPacket', defaultFramesPerPacket, checkFramesPerPacket);
            addOptional(p, 'packets', defaultPackets, checkPackets);
            addParameter(p, 'sensorname', defaultSensors, @(x) checkSensorName(x, validSensors));
            addParameter(p, 'filename', defaultFilename, @(x) checkFilename(x));
            addParameter(p, 'append', 0, @(x) (x==0||x==1));
            
            parse(p, obj, rate, varargin{:});
            
            N = uint16(obj.Api.MaxSensorSampleRate/p.Results.rate);
            M = p.Results.framesPerPacket;
            Pcnt = p.Results.packets;
            
            if ~iscell(p.Results.sensorname) % Convert the sensorname to a cell array
                sensors = cellstr(p.Results.sensorname);
            else
                sensors = p.Results.sensorname;
            end
            
            [Mask, Mask2] = sphero.DataStreamingMask(sensors);
            
            
            %Create a cell array of the sensor names sorted in the order
            %that response is expected.
            sortedSensors = {};
            for i=1:length(validSensors)
              if any(strcmp(sensors, validSensors{i}));
                    sortedSensors{end+1} = validSensors{i}; %#ok<AGROW>
              end
            end
                          
            % If previous polling is already in progress, then wait
            % till it completes
            warncount=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling', ...
                        'which is set to unlimited streaming. ', ...
                        'Disregarding current pollSensors command. ', ...
                        'Please reset the connection in order to disrupt', ...
                        ' the current sensor polling']);
                    return
                elseif warncount<1 % If the warning has not been displayed, then display it
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    warncount=1;
                end
                
            end
            
            
            if exist('filename', 'var') % If the user specified the filename,
                % and it was processed by the checkFilename function, then use the processed filename
                obj.SensorPolling.filename = filename;
            else
                obj.SensorPolling.filename  = p.Results.filename;
            end
            
            % Set the fields of 'SensorPolling' property so that it can be
            % used by the callback function
            obj.SensorPolling.freq = obj.Api.MaxSensorSampleRate/N;
            obj.SensorPolling.samples = M*Pcnt;
            obj.SensorPolling.samplesPerPacket = M;
            obj.SensorPolling.packets = Pcnt;
            obj.SensorPolling.sensors = sortedSensors;
            
            if Pcnt==0
                  obj.SensorPolling.samples = Inf;
                  obj.SensorPolling.packets = Inf;
            end
            
            for i=1:length(sortedSensors) % Initialize the SensorPolling.prevValue field for all the sensors that are to be polled
                obj.SensorPolling.prevValues.(sortedSensors{i}) = [];
                obj.SensorPolling.presentValues.(sortedSensors{i}) = [];
            end
            
            % If the file is to be appended to, check if the file contains
            % data from the same sensors that are to be polled. If they 
            % match, then append the data to the file. Otherwise overwrite 
            % the file
            if p.Results.append
                readData = load(obj.SensorPolling.filename);
                sensorsPolled = fieldnames(readData.values);
                
                if readData.freq==obj.SensorPolling.freq && ...
                    all(strcmp(sensorsPolled, obj.SensorPolling.sensors))
                
                     obj.SensorPolling.prevValues = readData.values;
                     samples = readData.samples+obj.SensorPolling.samples;
                     save(obj.SensorPolling.filename, samples, '-append')
                 
                else
                    %If the previous saved sensor data does not match the
                    %data that is to be polled, then overwrite the file
                    warning(['Cannot append to indicated file due to'...
                        'mismatch between saved data and data to be polled. '...
                        'Overwriting existing file']);
                    
                    freq = obj.SensorPolling.freq;
                    samples = obj.SensorPolling.samples;
                    save(obj.SensorPolling.filename, freq, samples)
                end
                
             else
                 freq = obj.SensorPolling.freq;
                 samples = obj.SensorPolling.samples;
                 save(obj.SensorPolling.filename, 'freq', 'samples')
            end
            
            %Set up listener to save the received Sensor Data, which is 
            % sent through an asynchronous response, to the file
            obj.Listeners.SensorDataList = addlistener(obj.Api, 'SensorData',  'PostSet',  @obj.sensorDataStreaming);
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);
        end
        
        function value = readSensor(obj, sensorname)
        % READSENSOR Read the current value of the indicated sensors
            % VALUE = READSENSOR(SPH, SENSORNAME) returns the current value
            % of the sensors
            
            N = 1;
            M = 1;
            Pcnt = 1;
            
             validSensors = {'accelX', 'accelY', 'accelZ', 'gyroX', 'gyroY', ...
                'gyroZ', 'rmotorEmfRaw', 'lmotorEmfRaw', 'lmotorPwmRaw', ...
                'rmotorPwmRaw', 'imuPitch', 'imuRoll', 'imuYaw', ...
                'accelXFilt', 'accelYFilt', 'accelZFilt', 'gyroXFilt', ...
                'gyroYFilt', 'gyroZFilt', 'rmotorEmfFilt', 'lmotorEmfFilt', ...
                'Q0', 'Q1', 'Q2', 'Q3', 'distX', 'distY', 'accelOne', ...
                'velX', 'velY'};
            
           if iscell(sensorname)
                    valid = all(cell2mat(cellfun(@(y) any(validatestring(y, validSensors)), sensorname, 'UniformOutput', false)));
            else
                    valid = any(validatestring(sensorname, validSensors));
            end
           
            if ~iscell(sensorname)
                sensorname = cellstr(sensorname);
            end
            
            [Mask, Mask2] = sphero.DataStreamingMask(sensorname);
            
            obj.SensorPolling.sensors = sensorname;
            obj.SensorPolling.freq = obj.Api.MaxSensorSampleRate/N;
            obj.SensorPolling.samples = M*Pcnt;
            obj.SensorPolling.samplesPerPacket = M;
            obj.SensorPolling.packets = Pcnt;           

            % If previous polling is already in progress, then wait
            % till it completes            
            warncount=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling', ...
                        'which is set to unlimited streaming. ', ...
                        'Disregarding readSensor command', ...
                        'Please reset the connection in order to disrupt', ...
                        ' the current sensor polling']);
                    return
                elseif warncount<1
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    warncount=1;
                end
                
            end

            % Reset the SensorDataPropertySet property of 'Communicaion' 
            % class before we start polling it to check when the 
            % 'SensorData' property has been set due to data received from
            % the Sphero
            obj.Api.SensorDataPropertySet = 0;
            
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);

            %Wait until SensorData property is set, due to data being 
            %received from sphero
            while ~obj.Api.SensorDataPropertySet

                pause(0.1) % Adding a pause. Otherwise the callback for 
                % asynchronous messages is not trigerred, as this loop 
                % keeps on executing and prevents the callback from being executed
            end
            
            if length(sensorname)==1
                value = obj.Api.SensorData.(sensorname{1});
            else
                value = obj.Api.SensorData; %Retrieve sensor data when it is received
            end
            
            
            %Create listener for SensorData again %NOTE: Not required anymore as
            %deleting listener in sensorDataStreaming itself
%             obj.Listeners.SensorDataList = addlistener(obj.Api, 'SensorData',  'PostSet', @(src) src.sensorDataStreaming);

            
        end
        
        function varargout = rotationRate(obj, rate)
        % rotationRate Set the rotation rate that Sphero uses
            %
            % This Rotation Rate is used by the Sphero when responding to
            % Heading commands. A lower value offers better control but
            % a higher value will yield quick turns.
            %
            % ROTATIONRATE(SPH, RATE) sets the rotation rate of the Sphero
            % to the indicated RATE, which is specified in degrees/sec.
            %
            % RESULT = ROTATIONRATE(SPH, RATE) returns 1 if the command 
            % succeeds, otherwise it returns 0
            nargoutchk(0, 1)
             
            validateattributes(rate, {'numeric'}, {'>=',obj.RateResolution, '<=', obj.RateMax});
            
            rateSend = uint8(rate/obj.RateResolution);
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setrotationrate', [], [], [], rateSend);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function [out1, varargout] = readLocator(obj)
            nargoutchk(0, 5);
             
            [responseexpected, seq] = sendCmd(obj.Api, 'readlocator', [], 1, []);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            
            if nargout <2
                if ~iscell(response) && any(isnan(response))
                    out1 = NaN;
                else
                    result.xpos = response{1};
                    result.ypos = response{2};
                    result.xvel = response{3};
                    result.yvel = response{4};
                    result.speed = response{5};
                    out1 = result;
                end
            else
                if ~iscell(response) && any(isnan(response))
                    out1 = NaN;
                    varargout = num2cell(NaN(1, nargout-1));
                else
                    out1 = response{1};
                    varargout = response(2:nargout);
                end
            end
        end
        
        function varargout = configureLocator(obj, flag, x, y, yawtare)
            nargoutchk(0, 1);
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'flag', @(x) isnumeric(x) && (x==0 || x==1));
            addRequired(p, 'x', @(x) isnumeric(x) && x>=intmin('int16') && x<=intmax('int16'));
            addRequired(p, 'y', @(x) isnumeric(x) && x>=intmin('int16') && x<=intmax('int16'));
            addRequired(p, 'yawtare', @(x) isnumeric(x) && x>=intmin('int16') && x<=intmax('int16'));
            parse(p, obj, flag, x, y, yawtare);
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'locator', [], [], [], p.Results.flag, p.Results.x, p.Results.y, p.Results.yawtare);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function calibrate(obj, angle)
           roll(obj, 0, angle);
           pause(obj.ResponseTimeout);
           heading(obj, 0);
           configureLocator(obj, 0, 0, 0, 0);
           
        end
        
        function varargout = boost(obj, flag)
            nargoutchk(0, 1);
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'flag', @(x) isnumeric(x) && (x==0 || x==1));
            parse(p, obj, flag); 
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'boost', [], [], [], p.Results.flag);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function varargout = rawMotor(obj, varargin)
            nargoutchk(0, 1);
            narginchk(2,8);
            
            validmodes = {'off', 'forward', 'reverse', 'brake', 'ignore'};
            
            p = inputParser;
            addRequired(p, 'objectname');
            addParameter(p, 'left', 0, @(x) isnumeric(x) && (x>=0 && x<=255));
            addParameter(p, 'right', 0, @(x) isnumeric(x) && (x>=0 && x<=255));
            addParameter(p, 'leftmode', 'ignore', @(x) any(validatestring(x, validmodes)));
            addParameter(p, 'rightmode', 'ignore', @(x) any(validatestring(x, validmodes)));
            parse(p, obj, varargin{:}); 
            
            leftpower = p.Results.left;
            rightpower = p.Results.right;
            
            function mode = selectmode(modestring)
                switch modestring
                    case 'off'
                        mode = 0;
                    case 'forward'
                        mode = 1;
                    case 'reverse'
                        mode = 2;
                    case 'brake'
                        mode = 3;
                    case 'ignore'
                        mode = 4;
                end
            end
            
            leftmode = selectmode(p.Results.leftmode);
            rightmode = selectmode(p.Results.rightmode);
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setrawmotors', [], [], [], leftmode, leftpower, rightmode, rightpower);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
            pause(obj.ResponseTimeout);
            
            if obj.Handshake
                result = stabilization(obj, 1);
                
                if ~result
                    error('Sphero:RawMotorStabilization', 'Unable to set stabilization again, after running rawMotor command');
                end
            else
                stabilization(obj, 1);
            end
            
        end
        
   
        function disconnect(obj)
            obj.BackLEDBrightness = 0;
            disconnect(obj.Api);
        end
        
         function varargout = sleep(obj, varargin)
            %%% Add InputParser
             
             wakeup      = 0;
            macro       = 0;
            orbBasic    = 0;
            

            err = MException('Sleep:InvalidProperty', 'Please enter a valid property or value for the Sleep function');

            for i=1:2:length(varargin)
                switch varargin{i}
                    case 'wakeup'
                        wakeup = varargin{i+1};
                    case 'macro'
                        macro = varargin{i+1};
                    case 'orbBasic'
                        orbBasic = varargin{i+1};
                    otherwise
                        throw(err);
                end
             end
                
            if ~isnumeric([wakeup macro orbBasic])
                throw(err)
            end
                
            [responseexpected, seq] = sendCmd(obj.Api, 'sleep', [], [], [], wakeup, macro, orbBasic);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
            disconnect(obj.Api)
            
        end
        
        function delete(obj)
            delete(obj.Listeners.PowerNotificationList);
            delete(obj.Listeners.PreSleepWarningList);
            delete(obj.Listeners.CollisionDetectionList);
            delete(obj.Listeners.GyroAxisLimitExceedList);
            
%             delete(obj.Listeners.SensorDataList);
%             L = import;
%             i = strcmp(L, 'sphero.*');
%             L(i) = [];
%             
%             clear import
%             import(L{:});
            
             obj.BackLEDBrightness = 0;
             delete(obj.Api);
%             disconnect(obj)
%             disp('Deleting sphero object');
        end
        
        function hwinfoObj = hwinfo(obj, varargin)
            hwinfoObj = sphero.internal.hwinfo(obj, varargin{:});
        end
    end
    
    methods
         % GET / SET methods
        function set.Color(obj, value)
            message = sprintf(['The color should be specified as a RGB value',... 
                '(0 to 1, or 0 to %i) or one of the predefined `s'], ...
                obj.Api.Uint8Max);
            err = MException('Color:Invalild', message);
                    
             if ~isnumeric(value)
                switch value
                    case {'y', 'yellow'}
                        rgb = [1 1 0];
                    case {'m', 'magenta'}
                        rgb = [1 0 1];
                    case {'c', 'cyan'}
                        rgb = [0 1 1];
                    case {'r', 'red'}
                        rgb = [1 0 0];
                    case {'g', 'green'}
                        rgb = [0 1 0];
                    case {'b', 'blue'}
                        rgb = [0 0 1];
                    case {'w', 'white'}
                        rgb = [1 1 1];
                    case {'k', 'black'}
                        rgb = [0 0 0];
                    otherwise
                       throw(err);

                end
            elseif all(value<=(obj.Api.Uint8Max))
                rgb = color;
            else
                 throw(err);
            end
            
            if all(rgb<=1)
                rgb = uint8(uint8(rgb)*(obj.Api.Uint8Max));
            end
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setrgbled', [], [], [], rgb, uint8(obj.SaveLedColor));
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
          
        end
        
        function rgb = get.Color(obj)
           [responseexpected, seq] = sendCmd(obj.Api, 'getrgbled', [], 1);
           
           rgb = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
%             rgb = [255 0 0];
        end
        
        function set.Handshake(obj, value)
           obj.Api.Handshake = value;
        end
        
        function handshaking = get.Handshake(obj)
            handshaking = obj.Api.Handshake;
        end
          
        function status = get.Status(obj)
            status = obj.Api.Bt.status;
        end
        
        function set.BackLEDBrightness(obj, brightness)
            
            if brightness>0 && brightness<1
                brightness = uint8(brightness*(obj.Api.Uint8Max));
            end
            
             [responseexpected, seq] = sendCmd(obj.Api, 'setbackled', [], [],[], brightness);
              
              result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              if responseexpected && ~isempty(result)
                 error('Sphero:BackLEDBrightnessNotSet', 'Brightness of Back LED could not be set. Please check the connection and retry') 
              end
              
              obj.BackLEDBrightness = brightness;
        end
        
        function set.AccRange(obj, acc)
            if acc>3 || acc<0
                error('The range for the index for acceleration range is 0 to 3')
            end
            
             [responseexpected, seq] = sendCmd(obj.Api, 'setaccelero', [], [],[], acc);
              
              result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              if responseexpected && ~isempty(result)
                 error('Sphero:AccRangeNotSet', 'Acceleration range of Sphero could not be set. Please check the connection and retry') 
              end
              
              obj.AccRange = acc;
              
        end
        
        function set.SensorPolling(obj,val)
            obj.SensorPolling = val;
           obj.Api.Sensors = obj.SensorPolling.sensors;
           obj.Api.SamplesPerPacket = obj.SensorPolling.samplesPerPacket;
           
        end
        
        function set.CollisionDetection(obj, flag)
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'flag', @(x) isnumeric(x) && (x==0 || x==1));
            parse(p, obj, flag);
            
            %Default values for collision detection parameters
            xt = 100;
            xspd = 100;
            yt = 100;
            yspd = 100;
            dead = 1000; % 1 second
            
            if obj.Handshake
                result = configureCollisionDetection(obj, p.Results.flag, xt, xspd, yt, yspd, dead);
                if ~result
                    error('Sphero:CollisionDetectionNoResponse', 'Collision Detection not configured. Please check connection and try again');
                end
            else
                configureCollisionDetection(obj, flag, xt, xspd, yt, yspd, dead);
            end
           
            obj.CollisionDetection = flag;
            
        end
        
        function set.MotionTimeout(obj, time)
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'time', @(x) isnumeric(x) && ((x>=0 && x<=intmax('uint16')/1000) || isinf(x)));
            parse(p, obj, time);
            
            if isinf(p.Results.time)
                time = intmax('uint16')/1000;
            end
            
            timeout = time*1000;
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setmotionto', [], [],[], timeout);
              
            result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            if responseexpected && ~isempty(result)
                 error('Sphero:MotionTimeoutNotSet', 'Motion timeout could not be set. Please check the connection and retry'); 
            end
              
            obj.MotionTimeout = time;
            
        end
        
        function set.InactivityTimeout(obj, time)
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'time', @(x) isnumeric(x) && (x>=60 && x<=intmax('uint16')));
            parse(p, obj, time);
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setinactivetimer', [], [],[], time);
              
            result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            if responseexpected && ~isempty(result)
                 error('Sphero:InactivityTimeoutNotSet', 'Inactivity timeout could not be set. Please check the connection and retry'); 
            end
              
            obj.InactivityTimeout = time;
        end
            
        
    end
    
end
