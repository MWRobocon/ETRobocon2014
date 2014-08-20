function varargout = NXTBluetoothStore(command, varargin)
% NXTBLUETOOTHSTORE Core API for communicating with NXT via Bluetooth
%
% Usages:
% Initialize Bluetooth Connection :        comms.NXTBluetoothStore();
% Close Bluetooth Connection :             comms.NXTBluetoothStore('reset') 
%
% Send data :                      comms.NXTBluetoothStore('write',dataBytes)
% Receive available data : [rxLength,data] = comms.NXTBluetoothStore('read')
% Enable debug messges :                     comms.NXTBluetoothStore('enableDebug')
% Disable debug messages :                   comms.NXTBluetoothStore('disableDebug') 
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
            availData = uint8(fread(b, availLength));
            
            % This logic is broken if multiple packets exist in the buffer
            payloadSize = availData(1);
            rxLength = payloadSize - 1;
            
            startData = 4;
            endData = startData + (rxLength - 1);
            
            data = availData(startData:endData);
        else
            rxLength = uint8(0);
            data = uint8(0);
        end
        dprintf('Done Reading Data\n');
    end

    function doWrite(data)
        dprintf('Writing Data\n');
        payloadSize = 1 + numel(data);
        packet = uint8([payloadSize 0 1 data]);
        fwrite(b, packet);
    end

% Parse Input Arguments
if(nargin == 0)
    command = 'initialize';
end
    
persistent isInit b debugMode;

if(isempty(debugMode))
    debugMode = false;
end

if(isempty(isInit) && any(strcmp(command,{'initialize','read','write'})))
    dprintf('Initializing Bluetooth\n');
    b = Bluetooth('BEN', 1);
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
        [rxLength,data] = doRead(varargin{:});
        varargout{1} = rxLength;
        varargout{2} = data;
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



