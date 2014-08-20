function runModel(ip, modelName, modelPath)
% runModel(ip, modelName, modelPath) - Function to run a specific model on Raspberry Pi 
% ip - the IP address for Raspberry Pi
% modelName - the name of executable, optional (default is 'etrobocon_host')
% modelPath - path of the executable on raspberry Pi, optional (deafult is '/home/pi/etrobocon_host_rtt/MW/')
% Examples:
%
% runModel('192.168.2.5','etrobocon_host','/home/pi/etrobocon_host_rtt/MW/')
%
%

if nargin == 0
    error('Need to specify ip address as first input');
end
if nargin == 1
    modelPath = '/home/pi/etrobocon_host_rtt/MW/';
    modelName = 'etrobocon_host';
end
if nargin == 2
    modelPath = ['/home/pi/' modelName '_rtt/MW/'];
end

try
% Connect to Raspberry Pi
h = raspberrypi(ip);
h.connect;

% Kill the process for any previous run
h.execute(['echo "raspberry"| sudo -s pkill ' modelName]);

% Start the model
h.execute(['echo "raspberry"| sudo ' modelPath modelName '&']);
catch
end
end