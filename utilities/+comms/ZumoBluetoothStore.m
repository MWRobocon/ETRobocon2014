function varargout = ZumoBluetoothStore(command, varargin)

persistent isInit b;

if(isempty(isInit))
    fprintf('Initializing Bluetooth\n');
    b = Bluetooth('Adafruit EZ-Link 32b0', 1);
    if(~strcmp(b.Status,'open'))
        fprintf('Opening connection');
        fopen(b);
    end
    isInit = 1;
    fprintf('Done Initializing\n');
    pause(1);
end

switch command
    case 'read'
        length = b.BytesAvailable;
        data = uint8(0);
        if length > 0
            fprintf('Reading Data\n');
            data = uint8(fread(b, length));
            length = 1;
            fprintf('Done Reading Data\n');
        end
        varargout{1} = length;
        varargout{2} = data;
    case 'write'
        packet = uint8(varargin{1});
        fprintf('Writing Data\n');
        fwrite(b, packet);
    case 'reset'
        if(strcmp(b.Status,'open'))
            fclose(b);
        end
        clear isInit;
end
