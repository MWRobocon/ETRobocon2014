classdef SpheroStore < handle
    methods(Static, Access = public)        
        function registerRobot(robotId,sphObj)
            comms.SpheroStore.getInstance().registerRobotImpl(robotId,sphObj);
        end
        
        function viewRegistry()
            comms.SpheroStore.getInstance().viewRegistryImpl();
        end
                
        function sphObj = get(robotId)
            sphObj = comms.SpheroStore.getInstance().getImpl(robotId);
        end
                
        function forceReset()
            comms.SpheroStore.getInstance(true);
        end
    end
    
    methods(Static, Access = private)
        function instance = getInstance(forceReset)
            if(nargin == 0)
                forceReset = false;
            end
            
            persistent theInstance;
            
            if(forceReset || isempty(theInstance))
                theInstance = comms.SpheroStore();
            end
            instance = theInstance;
        end
    end
    
    properties(Access = public)
        spheroHash;
    end
    
    methods(Access = private)
        function this = SpheroStore()
            this.spheroHash = containers.Map('keyType','int32','ValueType','any');
        end
                        
        function  sph = getImpl(this,robotId)
            sph = this.spheroHash(int32(robotId));
        end
        
        function tf = hasKey(this,robotId)
            tf = this.spheroHash.isKey(int32(robotId));
        end
        
        function registerRobotImpl(this,robotId,sphObj)
            this.spheroHash(int32(robotId)) = sphObj;
        end
        
        function viewRegistryImpl(this)
            keys = this.spheroHash.keys();
            
            for k = 1:numel(keys)
                sph = this.getImpl(int32(keys{k}));
                
                robotName = strtrim(evalc('disp(RobotID(keys{k}));'));
                fprintf('ID:%s \t\t Device Name: %s\n',robotName, sph.DeviceName);
            end
        end
    end
end