classdef hwinfo < handle & matlab.mixin.CustomDisplay
    %HWINFO Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess = private, GetAccess = public)
        Address
        ConnectionColor

    end
    
    properties
        InternalBluetoothName
    end
    
    properties (Access = private)
        SpheroObj
    end
    
    methods (Access = private)
        function [internalname, btaddress, idcolors] = btInfo(obj)
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'getbtname', [], 1);
            out = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            if length(out)<3
                error('btInfo:InvalidResponse', 'Invalid response received');
            else
                internalname = deblank(out(1, :));
                btaddress = deblank(out(2, :));
                idcolors = deblank(out(3, :));
            end
            
            
        end
        
        function varargout = deviceName(obj, name)
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'setbtname', [], [], [], name);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function powerstate = decodePowerState(obj, stateID)
            err = MException('Hwinfo:DecodePowerState:InvalidResponse', 'Invalid response received.');
            
             switch stateID
                    case 1
                        powerstate = 'Charging';
                    case 2
                        powerstate = 'Battery OK';
                    case 3
                        powerstate = 'Battery Low';
                    case 4
                        powerstate = 'Battery Critical';
                    otherwise
                        throwAsCaller(err);
             end
        end
        
        
    end
    
    methods
        function obj = hwinfo(spheroObj)
            obj.SpheroObj = spheroObj;
            [internalname, btaddress, idcolors] = btInfo(obj);
            
            obj.InternalBluetoothName = internalname;
            obj.Address = btaddress;
            obj.ConnectionColor = idcolors;
            
        end
            
        function ver = version(obj)
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'version', [], 1);
            ver = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
        end
        
        function [powerstate, varargout] = readPowerState(obj)
        %READPOWERSTATE receive the power state of the sphero
            % POWERSTATE = READPOWERSTATE(HWINFOOBJECT) returns the current 
            % power state of the sphero as a string
            % [POWERSTATE, VOLTAGE] = READPOWERSTATE(HWINFOOBJECT) also
            % returns the current battery voltage
            % [POWERSTATE, VOLTAGE, CHARGES] = READPOWERSTATE(HWINFOOBJECT)
            % returns the Number of battery recharges in the life of the
            % Sphero, besides the power state and voltage
            % [POWERSTATE, VOLTAGE, CHARGES, TIMEAWAKE]  = READPOWERSTATE(HWINFOOBJECT)
            % returns the time (in seconds) since last recharge as well
            
            nargoutchk(0, 4);
            
            err = MException('Hwinfo:ReadPowerState:InvalidResponse', 'Invalid response received.');
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'getpwrstate', [], 1);
            out = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            try
                state  = out{2};
               
                powerstate = decodePowerState(state);
           
                voltage     = out{3}/100; % The returned value is in 100ths of a volt

                if nargout>1
                    varargout{1} = voltage;
                    if nargout>2
                        varargout(2:nargout-1) = out(4:nargout+1);
                    end
                end
                
            catch exception
                if strncmp('Sphero', exception.identifier, 6)||strncmp('Hwinfo', exception.identifier, 6)
                    rethrow(exception)
                else
                    exception2 = addCause(err, exception);
                    throw(exception2);
                end
                
            end
                
            
        end
        
        function varargout = powerNotification(obj, flag)
        %POWERNOTIFICATION Set whether the Sphero should send asynchronous 
        %message with the power state periodically, or when the power state changes
            % RESULT = POWERNOTIFICATION(HWINFOOBJECT, FLAG) enables the
            % periodic power state notification when FLAG is 1, and
            % disables it when FLAG is 0
            
            nargoutchk(0,1);
            
            p = inputParser;
            addRequired(p, 'flag',  @(x) isnumeric(x) && (x==0 || x==1));
            parse(p, flag);
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'setpwrnotify', [], [], [], flag);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
        function [vlow, vcrit] = getVoltageTripPoints(obj)
        % GETVOLTAGETRIPPOINTS Get the voltage points for what Sphero
        % considers Low Battery and Critical battery
            % [VLOW, VCRITICAL] = GETVOLTAGETRIPPOINTS(HWINFOOBJECT)
            % returns the voltage points for low battery and critical
            % battery
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'getpowertrips', [], 1);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            vlow = double(response(1))/100; % The returned value is in 100ths of a volt
            vcrit = double(response(2))/100; % The returned value is in 100ths of a volt
 
        end
        
        function varargout = setVoltageTripPoints(obj, vlow, vcrit)
        % SETVOLTAGETRIPPOINTS Set the voltage points for what Sphero
        % considers Low Battery and Critical battery
            % RESULT = SETVOLTAGETRIPPOINTS(HWINFOOBJECT, VLOW, VCRITICAL)
            % sets the low and critical battery voltage levels for the 
            % Sphero. The low battery voltage should be in the range 6.5V
            % to 7.5V. The critical battery voltage should be in the range
            % 6.0V to 7.0V, and there must be a minimum separation of 0.25V
            % between the two values.
            
            p = inputParser;
            addRequired(p, 'objectname');
            addRequired(p, 'vlow',  @(x) isnumeric(x) && (x>=6.5&&x<=7.5));
            addRequired(p, 'vcrit',  @(x) isnumeric(x) && (x>=6&&x<=7));
            parse(p, obj, vlow, vcrit);
            
            if vlow-vcrit<0.25
                error(['There must be a minimum separation of 0.25V '...
                    'between the low and critical battery voltage values']);
            end
            
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'setpowertrips', [], [], [], vlow*100, vcrit*100);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
       
    end
    
    methods
        %GET / SET Methods
        function  set.InternalBluetoothName(obj, value)
            
            if ~strcmp(value, obj.InternalBluetoothName)
                result = deviceName(obj, value);
                
                if ~result
                    error('InternalBluetoothName:InvalidResponse', ...
                        'Unable to set internal bluetooth name.');
                end
                
            end
            
            obj.InternalBluetoothName = value;
        end
        
        function name = get.InternalBluetoothName(obj)
            name = obj.InternalBluetoothName;
        end
        
        
    end
    
    methods (Hidden = true)
        function devicemode = deviceMode(obj)
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'getdevicemode', [], 1);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            switch response
                case 0
                    devicemode='Normal';
                case 1
                    devicemode = 'User Hack';
                otherwise
                    devicemode = 'error';
            end
        end 
        
        function diag = diagnostics(obj)
            err = MException('Hwinfo:Diagnostics:InvalidResponse', 'Invalid response received.');
            
            try
                [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'runl2diags', [], 1);
                response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);

                diag.RecordVersion = response{1};
                diag.GoodPacketsReceived = response{2};
                diag.BadDeviceIDPackets = response{3};
                diag.BadDataLengthPackets = response{4};
                diag.BadCommandIDPackets = response{5};
                diag.BadChecksumPackets = response{6};
                diag.ReceiveBufferOverruns = response{7};
                diag.MessagesTransmitted = response{8};
                diag.TransmitBufferOverruns = response{9};
                diag.ChargeCycles = response{12};
                diag.SecondsSinceCharge = response{13};
                diag.SecondsOn = response{14};
                diag.DistanceRolled = response{15};
                diag.SensorFailures = response{16};
                diag.GyroAdjustCount = response{17};
                
            catch exception
                
                if strncmp('Sphero', exception.identifier, 6)||strncmp('Hwinfo', exception.identifier, 6)||isnan(response)
                    rethrow(exception)
                else
                    exception2 = addCause(err, exception);
                    throw(exception2);
%                      throw(exception)
                end
                
            end
        end
        
        function varargout = clearCounters(obj)
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'clearcounters', [], [], []);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
        end
        
        function delete(obj)
           powerNotification(obj, 0) 
        end
    end
end

