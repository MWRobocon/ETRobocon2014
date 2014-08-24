classdef Bt
% Bt Core API for communication via Bluetooth
%
% Usage:
% robot = comms.Bt('deviceName',channelNum)
% robot.init();
% robot.write(byteArray,txLength);
% [byteArray,rxLength] = robot.read(numBytes);
%
% Debugging Output is controlled via
% robot.debug = true/false;
%

    properties(Access = public)
        debug;
    end
    
    properties(GetAccess = public, SetAccess = private)
        deviceName; 
        channelNum; 
    end
    
    methods(Access = public)
        function this = Bt(aDeviceName,aChannelNum)
            this.debug = false;
            this.deviceName = aDeviceName;
            this.channelNum = aChannelNum;
        end
        
        function init(this)
            fprintf('Start Initializing\n');
            comms.BluetoothStore.add(this.deviceName,this.channelNum);
            b = comms.BluetoothStore.get(this.deviceName);
            if(~strcmp(b.Status,'open'))
                fprintf('Opening connection to %s on channel %u\n',this.deviceName,this.channelNum);
                fopen(b);
            end
            pause(1);
            fprintf('Done Initializing\n');
        end

        function [byteArray,rxLength] = read(this,numBytes)
            this.dprintf('Reading Data\n');
            rxLength = 0;
            byteArray = zeros([1,numBytes],'uint8');

            b = comms.BluetoothStore.get(this.deviceName);

            availLength = b.BytesAvailable;
            if availLength > 0
                rxLength = double(min([availLength,double(numBytes)]));
                byteArray(1:rxLength) = uint8(fread(b, rxLength));
            end
            this.dprintf('Done Reading Data\n');
        end

        function write(this,byteArray,txLength)
            this.dprintf('Writing Data\n');
            if(txLength > 0)
                fwrite(comms.BluetoothStore.get(this.deviceName), uint8(byteArray(1:txLength)));
            end
        end

        function reset(this)
            b = comms.BluetoothStore.get(this.deviceName);
            if(~isempty(b) && strcmp(b.Status,'open'))
                fclose(b);
            end
        end
    end
    
    methods(Access = private)
        function dprintf(this,str)
            if(this.debug)
                fprintf(str);
            end
        end
    end
end

