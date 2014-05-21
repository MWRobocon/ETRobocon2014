function status = UpdateMAC(ip,varargin)
% Help document for UpdateMAC
% 
% UpdateMAC is used to create a rfcomm.config file that specifies the MAC
% addresses of all the devices that we want to setup with the Raspberry Pi
%
% First argument "ip" is the IP Address of the Pi
% Subsequent input arguments are the name value pairs of the device name
% and the device MAC address.
% 
% Examples:
%
% For the See-Saw task you will need to configure one NXT as Mario and the
% other NXT as Princess. Suppose the MAC addresses of your 2 NXTs are
% '00:16:53:16:E6:43' and '00:16:53:16:12:10' then you would execute the
% following
%
% UpdateMAC('192.168.2.2','Mario','00:16:53:16:E6:43','Princess','00:16:53:16:12:10');
%
%
pvpair = varargin(:);
Mario = [];
Princess = [];
Yoshi = [];
Cube = [];


if(isempty(pvpair))
    disp('Nothing specified...')
    return;
end
sigutils.pvparse(pvpair{:});

% Connect to Raspberry Pi
h = raspberrypi(ip);
h.connect;

% Copy rfcomm.conf to current dir
h.getFile('/etc/bluetooth/rfcomm.conf');

fileContent = fileread('rfcomm.conf');

if ~isempty(Mario)
    fileContent = replaceMACAddr(fileContent, Mario, 'Mario');
end

if ~isempty(Princess)
    fileContent = replaceMACAddr(fileContent, Princess, 'Princess');
end

if ~isempty(Yoshi)
    fileContent = replaceMACAddr(fileContent, Yoshi, 'Yoshi');
end

if ~isempty(Cube)
    fileContent = replaceMACAddr(fileContent, Cube, 'Cube');
end

fid = fopen('rfcomm.conf','w');
if fid~=-1
    fprintf(fid,'%s',fileContent);
    fclose(fid);
else
    error('Failed to open local copy of rfcomm.conf');
end

% Put file to home directory 
try    
    h.putFile('rfcomm.conf','/home/pi');
catch
    disp('Failed to put the new config file into home directory!')
end
% Move file from home dir to /etc/bluetooth
try
    % Back up old file
    h.execute('echo "raspberry"| sudo -s mv /etc/bluetooth/rfcomm.conf /etc/bluetooth/rfcomm.conf_bak');
    h.execute('echo "raspberry"| sudo -s mv /home/pi/rfcomm.conf /etc/bluetooth/rfcomm.conf');
catch
    disp('Failed to copy the new config file to /etc/bluetooth directory!')
end

% Restart Bluetooth service
try
    h.execute('echo "raspberry"| sudo -s /etc/init.d/bluetooth restart');
catch
    disp('Failed to restart the bluetooth service after modifying RF comm');
end
status = 1;
% echo "raspberry"| sudo -s /etc/init.d/bluetooth restart   
end

function outStr = replaceMACAddr(inStr, MACAddr, entityName)
% Validate MAC address
MACPat = '^([0-9A-F]{2}[:-]){5}([0-9A-F]{2})$';
switch entityName
    case 'Mario'
        userID = 1; % Mario is the 1st occurance
    case 'Princess'
        userID = 2; % Princess is the 2nd occurance
    case 'Yoshi'
        userID = 3; % Yoshi is the 3rd occurance
    case 'Cube'
        userID = 4; % Cube is the 4th occurance
end
if isempty(regexp(MACAddr,MACPat,'once'))
    warningMsg = ['The MAC Address ' MACAddr ' specified for ' entityName ' is invalid'];
    warning(warningMsg);
    outStr = inStr;
else
    pat = '\n\s*[^#]\s*device \S+;';
    outStr = regexprep(inStr,pat,['\n\t\tdevice ' MACAddr ';'], userID);
end
end
    
