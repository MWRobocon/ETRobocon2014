%% Troubleshooting Connection Issues with Sphero
%% Sphero does not show up in the list of available devices
% Sphero is not listed under available devices when creating the
% *sphero* object, or the following error is received:
sph = sphero
%% 
%%
%  Error using sphero (line 502)
%  No Sphero device available. Please make sure your Sphero device is switched on and is in vicinity
%%
% * Check whether the Sphero device has been paired with the machine
% * Make sure that the Sphero is awake and ready for connection. It should 
% blink with 3 unique colors when it is awake and not connected to another 
% device.
% * Try creating the *sphero* object again. 
% * If you are still unable to connect to the device, try updating the 
% Sphero firmware by connecting to the Sphero app on an Android or 
% iOS device.
% * If the problem persists, unpair (or remove) the device from the 
% computer and then pair it again.

%% Unable to connect to device
% Creating a connection to a Sphero device, or trying to reconnect to a 
% previously connected device produces the following error:
sph = sphero('Sphero-GPG');
%%
connect(sph);
%%
%  Error using sphero (line 502)
%  Unable to connect to device. Please check that the device name is correct and the device is discoverable
% 
%  Caused by:
%     Error using icinterface/fopen (line 83)
%     Unsuccessful open: Cannot connect to the device. Possible reasons are another application is connected
%     or the device is not available.
%%
% * Make sure that the device is paired to your computer, is awake and not
% currently connected to another device
% * Check the device name that is specified when creating the *sphero* object
% * Try connecting once again

%% Warning received when connecting to device
% Creating a connection to Sphero device produces the following warning,
% and the Status of the connection is 'closed':
sph = sphero('Sphero-GPG');
%%
%  Warning: Error occured when reading Asynchronous message: Received response is not valid 
%  Warning: The BytesAvailableFcn is being disabled. To enable the callback property
%  either connect to the hardware with FOPEN or set the BytesAvailableFcn property.
%  
%  > In BluetoothApi>BluetoothApi.readResponse at 1059
%   In sphero>sphero.get.Color at 1257
%%
% This might occur when the Sphero responds with an invalid response when
% trying to connect to it initially. Please try connecting to it once
% again. 
%%
% If the problem persists, reset the Sphero device by placing it on the 
% charger, and then try again.

%% See Also
% <matlab:showdemo('sphero_examples') Sphero Connectivity Package Examples>



