classdef ApiInfo<hgsetget
    %APIINFO Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (SetAccess = 'private')
        Constants
        ClientCommand
        SpheroResponse
    end
    
    methods
        function obj = ApiInfo(ApiRev)
            obj.Constants = [];
            
            fileName = ['sphero.internal.spheroApiRev' ApiRev];
            obj.deserialize(fileName);
        end
        
        function set(obj, property, value)
            obj.(property) = value;
        end 
        
        function deserialize(h, fileName, varargin)
            deserializeM(h, fileName, varargin{:});
        end
        
    end
    
    methods (Access = 'private')
         function deserializeM(h, fileName, varargin)
            try
                info = feval(fileName, varargin{:});
                infofields = fields(info);
                for i=1:length(infofields)
                    set(h, (infofields{i}), info.(infofields{i}));
                end
            catch ME  %#ok<NASGU>
                % OK, means no data of this type registered
            end  
         end
    end
    
        
    
end

