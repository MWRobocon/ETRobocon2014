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
        robotId
    end
    
    methods(Access = public)
        function this = Bt(aRobotId)
            this.debug = false;
            this.robotId = aRobotId;
        end
        
        function init(this)
            fprintf('Start Initializing\n');
            comms.BluetoothStore.init(this.robotId);
            b = comms.BluetoothStore.get(this.robotId);
            if(~strcmp(b.Status,'open'))
                fprintf('Opening connection\n');
                fopen(b);
            end
            pause(1);
            fprintf('Done Initializing\n');
        end

        function [byteArray,rxLength] = read(this,numBytes)
            this.dprintf('Reading Data\n');
            rxLength = 0;
            byteArray = zeros([1,numBytes],'uint8');

            b = comms.BluetoothStore.get(this.robotId);

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
                fwrite(comms.BluetoothStore.get(this.robotId), uint8(byteArray(1:txLength)));
            end
        end

        function reset(this)
            b = comms.BluetoothStore.get(int32(this.robotId));
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