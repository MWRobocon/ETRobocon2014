function [length, data] = readNXTBluetooth()

[length, data] = comms.NXTBluetoothStore('read');

end



