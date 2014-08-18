function varargout = ZumoBluetoothStore(command, varargin)
% ZUMOBLUETOOTHSTORE Core API for communication with Zumo via Bluetooth
%
% Usages:
% Initialize Bluetooth Connection :        comms.ZumoBluetoothStore();
% Close Bluetooth Connection :             comms.ZumoBluetoothStore('reset') 
%
% Send data :                                comms.ZumoBluetoothStore('write',byteArray)
% Receive available data : [rxLength,data] = comms.ZumoBluetoothStore('read')
% Enable debug messges :                     comms.ZumoBluetoothStore('enableDebug')
% Disable debug messages :                   comms.ZumoBluetoothStore('disableDebug') 
%
% Description:
% Reading Data
% When reading data there are two output arguments "rxLength" and "data". 
% The output "rxLength" is the number of bytes returned in "data" corresponding
% to received data.  For example if rxLength = 1, and numel(data) == 3 then
% the first element of "data" corresponds to received data.  The remaining
% two elements should be ignored.

    function dprintf(str)
        if(debugMode)
            fprintf(str);
        end
    end
    
    function [rxLength,data] = doRead(varargin)
        dprintf('Reading Data\n');
        availLength = b.BytesAvailable;
        if availLength > 0
            rxLength = availLength;
            data = uint8(fread(b, availLength));
        else
            rxLength = 0;
            data = uint8(0);
        end
        dprintf('Done Reading Data\n');
    end

    function doWrite(data)
        dprintf('Writing Data\n');
        fwrite(b, data);
    end

if(nargin == 0)
    command = 'initialize';
end

persistent isInit b debugMode;

if(isempty(debugMode))
    debugMode = false;
end

if(isempty(isInit) && any(strcmp(command,{'initialize','read','write'})))
    dprintf('Initializing Bluetooth\n');
    b = Bluetooth('Adafruit EZ-Link 32b0', 1);
    if(~strcmp(b.Status,'open'))
        dprintf('Opening connection\n');
        fopen(b);
    end
    isInit = 1;
    dprintf('Done Initializing\n');
    pause(1);
end

switch command
    case 'read'
        [rxLength,data] = doRead(varargin);
        varargout{1} = uint8(rxLength);
        varargout{2} = uint8(data);
    case 'write'
        doWrite(uint8(varargin{1}));
    case 'reset'
        if(~isempty(b) && strcmp(b.Status,'open'))
            fclose(b);
        end
        clear isInit;
    case 'enableDebug'
        debugMode = true;
    case 'disableDebug'
        debugMode = false;
end
end