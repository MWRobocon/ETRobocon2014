<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/Minions
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
<<<<<<< HEAD
=======
classdef BluetoothStore < handle
    methods(Static, Access = public)        
        function registerRobot(robotId,deviceName,channelNum)
            comms.BluetoothStore.getInstance().registerRobotImpl(robotId,deviceName,channelNum);
        end
        
        function viewRegistry()
            comms.BluetoothStore.getInstance().viewRegistryImpl();
        end
        
        function init(robotId)
            comms.BluetoothStore.getInstance().initRobotImpl(robotId);
        end
        
        function b = get(robotId)
            b = comms.BluetoothStore.getInstance().getImpl(robotId);
        end
        
        function closeAllOpen()
            comms.BluetoothStore.getInstance().closeAllOpenImpl();
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
        robotRegistry;
    end
    
    methods(Access = private)
        function this = BluetoothStore()
            this.btHash = containers.Map('keyType','char','ValueType','any');
            this.robotRegistry = containers.Map('keyType','int32','ValueType','any');
        end
        
        function initRobotImpl(this,robotId)
            robotInfo = this.robotRegistry(int32(robotId));
            deviceName = robotInfo{1};
            channelNum = robotInfo{2};
            
            if(~this.hasKey(deviceName))
                b = Bluetooth(deviceName,channelNum);
                this.addImpl(deviceName,b);
            end
        end
        
        function addImpl(this,key,bluetoothObj)
            this.btHash(key) = bluetoothObj;
        end
        
        function  b = getImpl(this,robotId)
            robotInfo = this.robotRegistry(int32(robotId));
            deviceName = robotInfo{1};
            
            b = this.btHash(deviceName);
        end
        
        function tf = hasKey(this,key)
            tf = this.btHash.isKey(key);
        end
        
        function registerRobotImpl(this,robotId,deviceName,channelNum)
            this.robotRegistry(int32(robotId)) = {deviceName,channelNum};
        end
        
        function viewRegistryImpl(this)
            keys = this.robotRegistry.keys();
            
            for k = 1:numel(keys)
                robotName = strtrim(evalc('disp(RobotID(keys{k}));'));
                robotInfo = this.robotRegistry(keys{k});
                
                fprintf('ID:%s DeviceName:%s ChannelNum:%u\n',robotName,robotInfo{1},robotInfo{2});
            end
        end
        
        function closeAllOpenImpl(this)
            bluetoothCell = this.btHash.values();
            
            for k = 1:numel(bluetoothCell)
                if(strcmp(bluetoothCell{k}.Status,'open'))
                    fclose(bluetoothCell{k});
                end
            end
        end
    end
>>>>>>> refs/remotes/origin/master
=======
>>>>>>> refs/remotes/origin/Minions
end