classdef Standard < handle
    properties(Access = protected)
        repositoryRoot;
    end
    
    methods
        function this = Standard(aRepositoryRoot)
            this.repositoryRoot = aRepositoryRoot;
        end
    end
            
    methods(Abstract)
        checkStandard(this);
    end
end