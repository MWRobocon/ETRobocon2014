function [length, data] = readZumoBluetooth()

[length, data] = comms.ZumoBluetoothStore('read');

end



