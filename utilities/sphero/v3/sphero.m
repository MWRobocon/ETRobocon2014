<<<<<<< HEAD
<<<<<<< HEAD:utilities/sphero/v3/sphero.m
=======
>>>>>>> refs/remotes/origin/Minions
classdef sphero<handle
    %SPHERO Summary of this class goes here
    %   Detailed explanation goes here
    
    properties


        ResponseTimeout = 1;
        BackLEDBrightness = 0;
        AccRange = 2;
        MotionTimeout = 10; %Set method
        CollisionDetection = 0;
        PermOptions %set method
        TempOptions %set method
       
    end
    
    properties(Hidden=true)
        Api
        Listeners
        SaveLedColor = 1;
        CommunicationApi = 'BluetoothApi';        
    end
    
    properties(Access = {?sphero, ?BluetoothApi})
       SensorPolling 
    end
    
    properties (Dependent=true)
        Handshake;
        Color;

    end
    
     properties (Dependent=true, SetAccess = private)
       Status

    end
    
    properties(Access = private, Constant)
        RateUnit = 0.784;
        RateMax = 400;
        
    end
    
   methods(Static)
        function varargout = simpleResponse(response)
             
              
%             if nargout>1
%                 err = MException('SpheroMethod:InvalidOutputs', 'Too many output arguments');
%                 throwAsCaller(err)
%             else
              if nargout
                if isempty(response)
                    varargout{1} = 1;
                else
                    varargout{1} = 0;
                end
             end
        end
   end
   
    
    methods(Static, Access = private)
              
        function [Mask, Mask2] = DataStreamingMask(sensors)
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
        
        %Listener to the power notification
        function powerNotify(src, eventdata) %src.Name will be 'PowerNotification'
            disp(eventdata.AffectedObject.PowerNotification);
        end
        
       
        
%         function handleEvemt(src, evnt)
%            switch src.Name
%                case 'PowerNotification'
%                    
%                case '
%         end
    end
    
    methods(Access = private)
        %Listener for the Sensor Data Streaming
        function sensorDataStreaming(obj, ~, ~)
%             len = length(src.SensorData);
              if isempty(obj.SensorPolling.filename)
                  error(['Sphero is sending Sensor Data that is to be polled'...
                      ', but settings for saving the sensor data have'...
                      ' not been set.']);
              end
              
              

            if isempty(obj.Api.SensorData)
                warning('SensorData property not set')
                return
            end
            
            for i=1:length(obj.SensorPolling.sensors)
                if ~isfield(obj.Api.SensorData, obj.SensorPolling.sensors{i})
                    return
                end
                    
                currData = obj.Api.SensorData.(obj.SensorPolling.sensors{i});
                prevData = obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i});
                
                prevData(end+1:end+length(currData)) = currData;
                
                values.(obj.SensorPolling.sensors{i}) = prevData;
                obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i}) = prevData;
                
                
%                 src.SensorData.(obj.SensorPolling.sensors{i});
%                 obj.SensorPolling.presentValues = [];
%                 obj.SensorPolling.prevValues(end+1:end+len)= src.SensorData;
% %             obj.SensorPolling.presentValues = [];
            end
            
            save(obj.SensorPolling.filename, 'values', '-append');
            
%             readData = load(obj.SensorPolling.filename);
%             sensorsPolled = fieldnames(readData.values);
             samplesRemaining = obj.SensorPolling.samples-length(values.(obj.SensorPolling.sensors{1}));
             if samplesRemaining<=0
                 obj.SensorPolling.filename =[];
                 obj.SensorPolling.freq = [];
                 obj.SensorPolling.samples = [];
                 obj.SensorPolling.samplesperPacket = [];
                 obj.SensorPolling.packets = [];
                 obj.SensorPolling.sensors = [];
                 obj.SensorPolling.prevValues = [];
                 delete(obj.Listeners.SensorData);
                 
             end

        end
        
         function varargout = heading(obj, angle)
             nargoutchk(0, 1)
             
            angle = mod(angle, rad2deg(2*pi));
            [responseexpected, seq] = sendCmd(obj.Api, 'setcal', [], [], [], angle);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
        
        function varargout = stabilization(obj, flag)
             nargoutchk(0, 1)
             
            [responseexpected, seq] = sendCmd(obj.Api, 'setstabiliz', [], [], [], flag);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
    
        function varargout = configureCollisionDetection(obj, method, xt, xspd, yt, yspd, dead)
             p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'method', @(x) isnumeric(x) && (x==0 || x==1));
            addRequired(p, 'xt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'xspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'dead', @(x) isnumeric(x) && x>=10*intmin('int16') && x<=10*intmax('int16')); %Specified in ms. Sphero requires dead time in 10ms increments
            parse(p, obj, method, xt, xspd, yt, yspd, dead);
            
            nargoutchk(0, 1)
             
            if obj.AccRange~=2
                warning(['Collision detection feature relies on accelerometer'... 
                    ' range being set to +-8Gs. As the accelerometer range'...
                    ' has been modified, collision detection feature might'...
                    '  not work as intended']);
            end
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setcollisiondet', [], [], [],  method, xt, xspd, yt, yspd, dead);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
            
        end
    end
    
    methods
        function obj = sphero(varargin)
        %SPHERO    Create an object of class sphero 
            % SPHERO(DEVICENAME) connects to the indicated device through
            % the communication protocol 
            % SPHERO(DEVICENAME, CONNECT) connects to the device if CONNECT
            % is logically true
            
            import('sphero.*')
            obj.Api = internal.(obj.CommunicationApi);
            
%             obj.Api = sphero.(obj.CommunicationApi); 
%             obj.Api = sphero.BluetoothApi;
           
           if nargin>1
               if varargin{2}
                    connect(obj, varargin{1});
               end   
           else
               connect(obj, varargin{:});
           end
           
           
           obj.Handshake = 0;
           obk.BackLEDBrightness = 0;
           
            obj.SensorPolling = struct('filename', [], 'freq', [], ...
                'samples', [], 'samplesPerPacket', [], 'packets', [], ...
                'sensors', [], 'prevValues', [], 'presentValues', []);
            
           %Set default Color property to color that is at present
           
           %Add listeners to the events
%            obj.Listeners(1) = event.listener(obj.Api,
%            'PowerNotification', 'PostSet', @sphero.powerNotify);

%             idx = strcmp('sensor', obj.Api.ApiInfo.RspAsync);
                        
%            obj.Listeners(idx)  
           
        end
        
        function result = ping(obj)
            [responseexpected, seq] = sendCmd(obj.Api, 'ping', [], 1);
           
            
%             if responseexpected
%                 idx = indexOfResponseSequence(obj.Api, seq);
%                 
%                  t = cputime;
%                  
%                 while (isinf(obj.Api.SequenceList.response{idx}))
%                     if cputime-t>obj.ResponseTimeout
%                         throw('Response Timeout');
%                     end
%                     
%                     idx = indexOfResponseSequence(obj.Api, seq);
%                 end
                
%                 response = readResponse(obj.Api, idx);
                
                response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);

                if isempty(response)
                    result = 1;
                else
                    result = 0;
                end
%             else
%                 result = 0;
%             end
            
        end
        
                   
        function connect(obj, varargin)
             connect(obj.Api, varargin{:});
        end
        
        
        function varargout = roll(obj, speed, heading)
             nargoutchk(0, 1)
%              p =inputParser;
%              addRequired(p, 'speed', @(x) x>=0);
%              addRequired(p, 'heading', @(x) x>=0 && x<=360);
%              parse(p, speed, heading);

            heading = mod(heading, 360);
                          
            [responseexpected, seq] = sendCmd(obj.Api, 'roll', [], [], [], speed, heading, 1);
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
        function varargout = brake(obj)
             nargoutchk(0, 1)
             
              [responseexpected, seq]  = sendCmd(obj.Api, 'roll', [], [], [], 0, 0, 0);
              response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
        
       
        
        function pollSensors(obj, rate, varargin)
            %Arguments
            % 1. Sphero object
            % 2. Rate at which sensors are to be polled (0-400Hz)
            % 3. framesPerPacket:Number of frames to be transmitted per
            % packet that is sent (default = 1)
            % 4. packets: Number of packets to be transmitted (default = 0,
            % unlimited)
            % %5. resetFlag: 
            % NVP: sensorname, file, format, append
            p = inputParser;
            
            defaultFramesPerPacket = 1;
            checkFramesPerPacket = @(x) isnumeric(x) && isscalar(x) && (x>0);
            
            defaultPackets = 0;
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
                   error('File extension should be MAT');
               end
               
               filename = fullfile(pathstr, [name, ext]);
               fileId = fopen(filename, 'a');
               
               if fileId~=-1
                   valid=1;
                    fclose(fileId);
               else
                   error('Cannot open the file')
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
%             addRequired(p, 'rate', @(x) validateattributes(x, {'numeric'}, ...
%                 {'positive'}));
            addRequired(p, 'rate', @(x) isnumeric(x) && x>=0 && x<=400);
            
            addOptional(p, 'framesPerPacket', defaultFramesPerPacket, checkFramesPerPacket);
            addOptional(p, 'packets', defaultPackets, checkPackets);
            
            addParameter(p, 'sensorname', {'distX', 'distY'}, @(x) checkSensorName(x, validSensors));
            
            addParameter(p, 'filename', 'log.mat', @(x) checkFilename(x));
            
            addParameter(p, 'append', 0, @(x) (x==0||x==1));
            
            parse(p, obj, rate, varargin{:});
            
            
            N = uint16(obj.Api.MaxSensorSampleRate/p.Results.rate);
            
            M = p.Results.framesPerPacket;
            
            Pcnt = p.Results.packets;
            
            
            
            if ~iscell(p.Results.sensorname)
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
                    sortedSensors{end+1} = validSensors{i};
              end
            end
            
%             [pathstr,name,ext] = fileparts(p.Results.filename);
%              if isempty(ext)
%                    ext = '.mat';
%                end
%                
%                filename = fullfile(pathstr, [name, ext]);
%                fileId = fopen(filename, 'a');
              
            %%%%%% If previous polling is already in progress, then wait
            %%%%%% till it completes
            n=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling'...
                        'which is set to unlimited streaming. '...
                        'Disregarding current pollSensors command']);
                    return
                elseif n<1
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    n=1;
                end
                
            end
            

            if exist('filename', 'var')
                obj.SensorPolling.filename = filename;
            else
                obj.SensorPolling.filename  = p.Results.filename;
            end
            
            obj.SensorPolling.freq = obj.Api.MaxSensorSampleRate/N;
            obj.SensorPolling.samples = M*Pcnt;
            obj.SensorPolling.samplesPerPacket = M;
            obj.SensorPolling.packets = Pcnt;
            obj.SensorPolling.sensors = sortedSensors;
            
            if Pcnt==0
                  obj.SensorPolling.samples = Inf;
                  obj.SensorPolling.packets = Inf;
            end
            
            for i=1:length(sortedSensors)
                obj.SensorPolling.prevValues.(sortedSensors{i}) = [];
                obj.SensorPolling.presentValues.(sortedSensors{i}) = [];
            end
            
            if p.Results.append
                readData = load(obj.SensorPolling.filename);
                sensorsPolled = fieldnames(readData.values);
%                 samplesRemaining = readData.samples-length(readData.values.(sensorsPolled{1}));
                
                if readData.freq==obj.SensorPolling.freq && ...
                    all(strcmp(sensorsPolled, obj.SensorPolling.sensors)) %&&...
%                      samplesRemaining==obj.SensorPolling.samples
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
            
            obj.Listeners.SensorData = addlistener(obj.Api, 'SensorData',  'PostSet',  @obj.sensorDataStreaming);
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);
            
%             saveSensorData(obj, obj.SensorPolling.filename, obj.SensorPolling.sensors);
            
            
        end
        
        function result = readSensor(obj, sensorname)
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

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            %%% Stop the listener for poll sensors. Save the current
            %%% settings of pollSensor, and resume it after readSensor.
            
%             idx = strcmp('sensors', obj.Api.ApiInfo.RspAsync);
            n=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling'...
                        'which is set to unlimited streaming. '...
                        'Disregarding current pollSensors command']);
                    return
                elseif n<1
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    n=1;
                end
                
            end
            
            
%             delete(obj.Listeners.SensorData)
            
            obj.Api.SensorDataPropertySet = 0;
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);
            
            while ~obj.Api.SensorDataPropertySet
                %Wait until SensorData property is set, when data is
                %received from sphero
                pause(0.1)
            end
            
            if length(sensorname)==1
                result = obj.Api.SensorData.(sensorname{1});
            else
                result = obj.Api.SensorData; %Retrieve sensor data when it is received
            end
            
            
            %Create listener for SensorData again %%Not required anymore as
            %deleting listener in sensorDataStreaming itself
%             obj.Listeners.SensorData = addlistener(obj.Api, 'SensorData',  'PostSet', @(src) src.sensorDataStreaming);

            
        end
        
        function varargout = rotationRate(obj, rate)
            nargoutchk(0, 1)
             
            validateattributes(rate, {'numeric'}, {'>=',obj.RateUnit, '<=', obj.RateMax});
            
            rateSend = uint8(rate/obj.RateUnit);
            
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
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'locator', [], [], [], flag, x, y, yawtare);
            
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
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'boost', [], [], [], flag);
            
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
                    error('rawMotor:stabilization', 'Unable to set stabilization again, after running rawMotor command');
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
              
            
        end
        
        function delete(obj)
%             delete(obj.Listeners.SensorData);
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
                 error('Brightness of Back LED could not be set. Please check the connection and retry') 
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
                 error('AccRange:NotSet', 'Acceleration range of Sphero could not be set. Please check the connection and retry') 
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
            dead = 100;
            
            if obj.Handshake
                result = configureCollisionDetection(obj, flag, xt, xspd, yt, yspd, dead);
                if ~result
                    error('CollisionDetection:NoResponse', 'Collision Detection not configured. Please check connection and try again');
                end
            else
                configureCollisionDetection(obj, flag, xt, xspd, yt, yspd, dead);
            end
           
            obj.CollisionDetection = flag;
            
        end
        
        function set.MotionTimeout(obj, time)
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'time', @(x) isnumeric(x) && (x>=0 || x<=intmax('uint16')/1000 || isinf(x)));
            parse(p, obj, time);
            
            if isinf(p.Results.time)
                time = intmax('uint16')/1000;
            end
            
            timeout = time*1000;
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setmotionto', [], [],[], timeout);
              
            result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            if responseexpected && ~isempty(result)
                 error('MotionTimeout:NotSet', 'Motion timeout could not be set. Please check the connection and retry'); 
            end
              
            obj.MotionTimeout = time;
            
        end
            
        
    end
    
end

<<<<<<< HEAD
=======
classdef sphero<handle
    %SPHERO Summary of this class goes here
    %   Detailed explanation goes here
    
    properties


        ResponseTimeout = 1;
        BackLEDBrightness = 0;
        AccRange = 2;
        MotionTimeout = 2; %Set method
        CollisionDetection = 0;
        PermOptions %set method
        TempOptions %set method
       
    end
    
    properties(Hidden=true)
        Api
        Listeners
        SaveLedColor = 1;
        CommunicationApi = 'BluetoothApi';        
    end
    
    properties(Access = {?sphero, ?BluetoothApi})
       SensorPolling 
    end
    
    properties (Dependent=true)
        Handshake;
        Color;

    end
    
    properties(Access = private, Constant)
        RateUnit = 0.784;
        RateMax = 400;
        
    end
    
   methods(Static)
        function varargout = simpleResponse(response)
             
              
%             if nargout>1
%                 err = MException('SpheroMethod:InvalidOutputs', 'Too many output arguments');
%                 throwAsCaller(err)
%             else
              if nargout
                if isempty(response)
                    varargout{1} = 1;
                else
                    varargout{1} = 0;
                end
             end
        end
   end
   
    
    methods(Static, Access = private)
              
        function [Mask, Mask2] = DataStreamingMask(sensors)
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
        
        %Listener to the power notification
        function powerNotify(src, eventdata) %src.Name will be 'PowerNotification'
            disp(eventdata.AffectedObject.PowerNotification);
        end
        
       
        
%         function handleEvemt(src, evnt)
%            switch src.Name
%                case 'PowerNotification'
%                    
%                case '
%         end
    end
    
    methods(Access = private)
        %Listener for the Sensor Data Streaming
        function sensorDataStreaming(obj, ~, ~)
%             len = length(src.SensorData);
              if isempty(obj.SensorPolling.filename)
                  error(['Sphero is sending Sensor Data that is to be polled'...
                      ', but settings for saving the sensor data have'...
                      ' not been set.']);
              end
              
              

            if isempty(obj.Api.SensorData)
                warning('SensorData property not set')
                return
            end
            
            for i=1:length(obj.SensorPolling.sensors)
                if ~isfield(obj.Api.SensorData, obj.SensorPolling.sensors{i})
                    return
                end
                    
                currData = obj.Api.SensorData.(obj.SensorPolling.sensors{i});
                prevData = obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i});
                
                prevData(end+1:end+length(currData)) = currData;
                
                values.(obj.SensorPolling.sensors{i}) = prevData;
                obj.SensorPolling.prevValues.(obj.SensorPolling.sensors{i}) = prevData;
                
                
%                 src.SensorData.(obj.SensorPolling.sensors{i});
%                 obj.SensorPolling.presentValues = [];
%                 obj.SensorPolling.prevValues(end+1:end+len)= src.SensorData;
% %             obj.SensorPolling.presentValues = [];
            end
            
            save(obj.SensorPolling.filename, 'values', '-append');
            
%             readData = load(obj.SensorPolling.filename);
%             sensorsPolled = fieldnames(readData.values);
             samplesRemaining = obj.SensorPolling.samples-length(values.(obj.SensorPolling.sensors{1}));
             if samplesRemaining<=0
                 obj.SensorPolling.filename =[];
                 obj.SensorPolling.freq = [];
                 obj.SensorPolling.samples = [];
                 obj.SensorPolling.samplesperPacket = [];
                 obj.SensorPolling.packets = [];
                 obj.SensorPolling.sensors = [];
                 obj.SensorPolling.prevValues = [];
                 delete(obj.Listeners.SensorData);
                 
             end

        end
        
         function varargout = heading(obj, angle)
             nargoutchk(0, 1)
             
            angle = mod(angle, rad2deg(2*pi));
            [responseexpected, seq] = sendCmd(obj.Api, 'setcal', [], [], [], angle);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
        
        function varargout = stabilization(obj, flag)
             nargoutchk(0, 1)
             
            [responseexpected, seq] = sendCmd(obj.Api, 'setstabiliz', [], [], [], flag);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
    
        function varargout = configureCollisionDetection(obj, method, xt, xspd, yt, yspd, dead)
             p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'method', @(x) isnumeric(x) && (x==0 || x==1));
            addRequired(p, 'xt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'xspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yt', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'yspd', @(x) isnumeric(x) && x>=intmin('uint8') && x<=intmax('uint8'));
            addRequired(p, 'dead', @(x) isnumeric(x) && x>=10*intmin('int16') && x<=10*intmax('int16')); %Specified in ms. Sphero requires dead time in 10ms increments
            parse(p, obj, method, xt, xspd, yt, yspd, dead);
            
            nargoutchk(0, 1)
             
            if obj.AccRange~=2
                warning(['Collision detection feature relies on accelerometer'... 
                    ' range being set to +-8Gs. As the accelerometer range'...
                    ' has been modified, collision detection feature might'...
                    '  not work as intended']);
            end
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setcollisiondet', [], [], [],  method, xt, xspd, yt, yspd, dead);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
              
            
        end
    end
    
    methods
        function obj = sphero(varargin)
        %SPHERO    Create an object of class sphero 
            % SPHERO(DEVICENAME) connects to the indicated device through
            % the communication protocol 
            % SPHERO(DEVICENAME, CONNECT) connects to the device if CONNECT
            % is logically true
            
            import('sphero.*')
            obj.Api = internal.(obj.CommunicationApi);
            
%             obj.Api = sphero.(obj.CommunicationApi); 
%             obj.Api = sphero.BluetoothApi;
           
           if nargin>1
               if varargin{2}
                    connect(obj, varargin{1});
               end   
           else
               connect(obj, varargin{:});
           end
           
           
           obj.Handshake = 0;
           obk.BackLEDBrightness = 0;
           
            obj.SensorPolling = struct('filename', [], 'freq', [], ...
                'samples', [], 'samplesPerPacket', [], 'packets', [], ...
                'sensors', [], 'prevValues', [], 'presentValues', []);
            
           %Set default Color property to color that is at present
           
           %Add listeners to the events
%            obj.Listeners(1) = event.listener(obj.Api,
%            'PowerNotification', 'PostSet', @sphero.powerNotify);

%             idx = strcmp('sensor', obj.Api.ApiInfo.RspAsync);
                        
%            obj.Listeners(idx)  
           
        end
        
        function result = ping(obj)
            [responseexpected, seq] = sendCmd(obj.Api, 'ping', [], 1);
           
            
%             if responseexpected
%                 idx = indexOfResponseSequence(obj.Api, seq);
%                 
%                  t = cputime;
%                  
%                 while (isinf(obj.Api.SequenceList.response{idx}))
%                     if cputime-t>obj.ResponseTimeout
%                         throw('Response Timeout');
%                     end
%                     
%                     idx = indexOfResponseSequence(obj.Api, seq);
%                 end
                
%                 response = readResponse(obj.Api, idx);
                
                response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);

                if isempty(response)
                    result = 1;
                else
                    result = 0;
                end
%             else
%                 result = 0;
%             end
            
        end
        
                   
        function connect(obj, varargin)
             connect(obj.Api, varargin{:});
        end
        
        
        function varargout = roll(obj, speed, heading)
             nargoutchk(0, 1)
%              p =inputParser;
%              addRequired(p, 'speed', @(x) x>=0);
%              addRequired(p, 'heading', @(x) x>=0 && x<=360);
%              parse(p, speed, heading);

            heading = mod(heading, 360);
                          
            [responseexpected, seq] = sendCmd(obj.Api, 'roll', [], [], [], speed, heading, 1);
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
        function varargout = brake(obj)
             nargoutchk(0, 1)
             
              [responseexpected, seq]  = sendCmd(obj.Api, 'roll', [], [], [], 0, 0, 0);
              response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              [varargout{1:nargout}] = sphero.simpleResponse(response);
              
        end
        
       
        
        function pollSensors(obj, rate, varargin)
            %Arguments
            % 1. Sphero object
            % 2. Rate at which sensors are to be polled (0-400Hz)
            % 3. framesPerPacket:Number of frames to be transmitted per
            % packet that is sent (default = 1)
            % 4. packets: Number of packets to be transmitted (default = 0,
            % unlimited)
            % %5. resetFlag: 
            % NVP: sensorname, file, format, append
            p = inputParser;
            
            defaultFramesPerPacket = 1;
            checkFramesPerPacket = @(x) isnumeric(x) && isscalar(x) && (x>0);
            
            defaultPackets = 0;
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
                   error('File extension should be MAT');
               end
               
               filename = fullfile(pathstr, [name, ext]);
               fileId = fopen(filename, 'a');
               
               if fileId~=-1
                   valid=1;
                    fclose(fileId);
               else
                   error('Cannot open the file')
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
%             addRequired(p, 'rate', @(x) validateattributes(x, {'numeric'}, ...
%                 {'positive'}));
            addRequired(p, 'rate', @(x) isnumeric(x) && x>=0 && x<=400);
            
            addOptional(p, 'framesPerPacket', defaultFramesPerPacket, checkFramesPerPacket);
            addOptional(p, 'packets', defaultPackets, checkPackets);
            
            addParameter(p, 'sensorname', {'distX', 'distY'}, @(x) checkSensorName(x, validSensors));
            
            addParameter(p, 'filename', 'log.mat', @(x) checkFilename(x));
            
            addParameter(p, 'append', 0, @(x) (x==0||x==1));
            
            parse(p, obj, rate, varargin{:});
            
            
            N = uint16(obj.Api.MaxSensorSampleRate/p.Results.rate);
            
            M = p.Results.framesPerPacket;
            
            Pcnt = p.Results.packets;
            
            
            
            if ~iscell(p.Results.sensorname)
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
                    sortedSensors{end+1} = validSensors{i};
              end
            end
            
%             [pathstr,name,ext] = fileparts(p.Results.filename);
%              if isempty(ext)
%                    ext = '.mat';
%                end
%                
%                filename = fullfile(pathstr, [name, ext]);
%                fileId = fopen(filename, 'a');
              
            %%%%%% If previous polling is already in progress, then wait
            %%%%%% till it completes
            n=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling'...
                        'which is set to unlimited streaming. '...
                        'Disregarding current pollSensors command']);
                    return
                elseif n<1
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    n=1;
                end
                
            end
            

            if exist('filename', 'var')
                obj.SensorPolling.filename = filename;
            else
                obj.SensorPolling.filename  = p.Results.filename;
            end
            
            obj.SensorPolling.freq = obj.Api.MaxSensorSampleRate/N;
            obj.SensorPolling.samples = M*Pcnt;
            obj.SensorPolling.samplesPerPacket = M;
            obj.SensorPolling.packets = Pcnt;
            obj.SensorPolling.sensors = sortedSensors;
            
            if Pcnt==0
                  obj.SensorPolling.samples = Inf;
                  obj.SensorPolling.packets = Inf;
            end
            
            for i=1:length(sortedSensors)
                obj.SensorPolling.prevValues.(sortedSensors{i}) = [];
                obj.SensorPolling.presentValues.(sortedSensors{i}) = [];
            end
            
            if p.Results.append
                readData = load(obj.SensorPolling.filename);
                sensorsPolled = fieldnames(readData.values);
%                 samplesRemaining = readData.samples-length(readData.values.(sensorsPolled{1}));
                
                if readData.freq==obj.SensorPolling.freq && ...
                    all(strcmp(sensorsPolled, obj.SensorPolling.sensors)) %&&...
%                      samplesRemaining==obj.SensorPolling.samples
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
            
            obj.Listeners.SensorData = addlistener(obj.Api, 'SensorData',  'PostSet',  @obj.sensorDataStreaming);
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);
            
%             saveSensorData(obj, obj.SensorPolling.filename, obj.SensorPolling.sensors);
            
            
        end
        
        function result = readSensor(obj, sensorname)
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

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            %%% Stop the listener for poll sensors. Save the current
            %%% settings of pollSensor, and resume it after readSensor.
            
%             idx = strcmp('sensors', obj.Api.ApiInfo.RspAsync);
            n=0;
            while ~isempty(obj.SensorPolling.filename)
                if isinf(obj.SensorPolling.packets)
                    warning(['Cannot disrupt current sensor polling'...
                        'which is set to unlimited streaming. '...
                        'Disregarding current pollSensors command']);
                    return
                elseif n<1
                    warning(['Other sensors are being polled at present. '...
                    'Waiting till that completes. \n']);
                    n=1;
                end
                
            end
            
            
%             delete(obj.Listeners.SensorData)
            
            obj.Api.SensorDataPropertySet = 0;
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            sendCmd(obj.Api, 'setdatastreaming', [], [], [], N, M, Mask, Pcnt, Mask2);
            
            while ~obj.Api.SensorDataPropertySet
                %Wait until SensorData property is set, when data is
                %received from sphero
                pause(0.1)
            end
            
            if length(sensorname)==1
                result = obj.Api.SensorData.(sensorname{1});
            else
                result = obj.Api.SensorData; %Retrieve sensor data when it is received
            end
            
            
            %Create listener for SensorData again %%Not required anymore as
            %deleting listener in sensorDataStreaming itself
%             obj.Listeners.SensorData = addlistener(obj.Api, 'SensorData',  'PostSet', @(src) src.sensorDataStreaming);

            
        end
        
        function varargout = rotationRate(obj, rate)
            nargoutchk(0, 1)
             
            validateattributes(rate, {'numeric'}, {'>=',obj.RateUnit, '<=', obj.RateMax});
            
            rateSend = uint8(rate/obj.RateUnit);
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setrotationrate', [], [], [], rateSend);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function [out1, varargout] = readLocator(obj)
            nargoutchk(0, 4);
             
            [responseexpected, seq] = sendCmd(obj.Api, 'readlocator', [], 1, []);
            
            response = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            result.xpos = response{1};
            result.ypos = response{2};
            result.xvel = response{3};
            result.yvel = response{4};
            result.speed = response{5};
            
            if nargout == 0
                out1 = result;
            else
                out1 = response(1);
                varargout = response(2:nargout+1);
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
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'locator', [], [], [], flag, x, y, yawtare);
            
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
                        
            [responseexpected, seq] = sendCmd(obj.Api, 'boost', [], [], [], flag);
            
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
                    error('rawMotor:stabilization', 'Unable to set stabilization again, after running rawMotor command');
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
              
            
        end
        
        function delete(obj)
%             delete(obj.Listeners.SensorData);
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
          
        function set.BackLEDBrightness(obj, brightness)
            
            if brightness>0 && brightness<1
                brightness = uint8(brightness*(obj.Api.Uint8Max));
            end
            
             [responseexpected, seq] = sendCmd(obj.Api, 'setbackled', [], [],[], brightness);
              
              result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
              if responseexpected && ~isempty(result)
                 error('Brightness of Back LED could not be set. Please check the connection and retry') 
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
                 error('AccRange:NotSet', 'Acceleration range of Sphero could not be set. Please check the connection and retry') 
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
            dead = 100;
            
            if obj.Handshake
                result = configureCollisionDetection(obj, flag, xt, xspd, yt, yspd, dead);
                if ~result
                    error('CollisionDetection:NoResponse', 'Collision Detection not configured. Please check connection and try again');
                end
            else
                configureCollisionDetection(obj, flag, xt, xspd, yt, yspd, dead);
            end
           
            obj.CollisionDetection = flag;
            
        end
        
        function set.MotionTimeout(obj, time)
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'time', @(x) isnumeric(x) && (x>=0 || x<=intmax('uint16')/1000 || isinf(x)));
            parse(p, obj, time);
            
            if isinf(p.Results.time)
                time = intmax('uint16')/1000;
            end
            
            timeout = time*1000;
            
            [responseexpected, seq] = sendCmd(obj.Api, 'setmotionto', [], [],[], timeout);
              
            result = readResponse(obj.Api, responseexpected, seq, obj.ResponseTimeout);
              
            if responseexpected && ~isempty(result)
                 error('MotionTimeout:NotSet', 'Motion timeout could not be set. Please check the connection and retry'); 
            end
              
            obj.MotionTimeout = time;
            
        end
            
        
    end
    
end

>>>>>>> origin/Hydra:models/sphero/sphero.m
=======
>>>>>>> refs/remotes/origin/Minions
