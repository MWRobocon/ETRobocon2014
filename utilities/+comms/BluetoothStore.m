classdef BluetoothStore < handle
    methods(Static, Access = public)
        function add(deviceName,channelNum)
            if(~comms.BluetoothStore.getInstance().hasKey(deviceName))
                b = Bluetooth(deviceName,channelNum);
                comms.BluetoothStore.getInstance().addImpl(deviceName,b);
            end
        end
        
        function b = get(key)
            b = comms.BluetoothStore.getInstance().getImpl(key);
        end
        
        function closeAllOpen()
            % TODO
        end
        
        function forceReset()
            comms.BluetoothStore.getInstance(true);
        end
    end
    
    methods(Static, Access = private)
        function instance = getInstance(forceReset)
            if(nargin == 0)
                forceReset = false;
            end
            
            persistent theInstance;
            
            if(forceReset || isempty(theInstance))
                theInstance = comms.BluetoothStore();
            end
            instance = theInstance;
        end
    end
    
    properties(Access = public)
        btHash;
    end
    
    methods(Access = private)
        function this = BluetoothStore()
            this.btHash = containers.Map('keyType','char','ValueType','any');
        end
        
        function addImpl(this,key,bluetoothObj)
            this.btHash(key) = bluetoothObj;
        end
        
        function  b = getImpl(this,key)
            b = this.btHash(key);
        end
        
        function tf = hasKey(this,key)
            tf = this.btHash.isKey(key);
        end
    end
end