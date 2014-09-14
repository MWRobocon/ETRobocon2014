classdef hwinfo < handle & matlab.mixin.CustomDisplay
    %HWINFO Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess = private, GetAccess = public)
        Address
        ConnectionColor

    end
    
    properties
        InternalBluetoothName
        AutoReconnect
    end
    
    properties (Access = private)
        SpheroObj
    end
    
    methods %(Access = private)
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
            
            nargoutchk(1, 4);
            
            err = MException('readPowerState:InvalidResponse', 'Invalid response received.');
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'getpwrstate', [], 1);
            out = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            
            state  = out{2};
            switch state
                case 1
                    powerstate = 'Charging';
                case 2
                    powerstate = 'Battery OK';
                case 3
                    powerstate = 'Battery Low';
                case 4
                    powerstate = 'Battery Critical';
                otherwise
                    throw(err);
            end
            
            voltage     = out{3}/100; % The returned value is in 100ths of a volt
           
            if nargout>1
                varargout{1} = voltage;
                if nargout>2
                    varargout(2:nargout-1) = out(4:nargout+1);
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
            p.addRequired(p, 'flag',  @(x) isnumeric(x) && (x==0 || x==1));
            parse(p, flag);
            
            [responseexpected, seq] = sendCmd(obj.SpheroObj.Api, 'setpwrnotify', [], [], [], flag);
            response = readResponse(obj.SpheroObj.Api, responseexpected, seq, obj.SpheroObj.ResponseTimeout);
            
            [varargout{1:nargout}] = sphero.simpleResponse(response);
            
        end
        
%         function [vlow
    end
    
    methods
        %GET / SET Methods
        function  set.InternalBluetoothName(obj, value)
            
            if ~strcmp(value, obj.InternalBluetoothName)
                if obj.SpheroObj.Handshake
                    result = deviceName(obj, value);

                    if ~result
                        error('InternalBluetoothName:InvalidResponse', ...
                            'Unable to set internal bluetooth name.');
                    end
                else
                    deviceName(obj, value);
                end
            end
            
            obj.InternalBluetoothName = value;
        end
        
        function name = get.InternalBluetoothName(obj)
            name = obj.InternalBluetoothName;
        end
        
        
    end
end

