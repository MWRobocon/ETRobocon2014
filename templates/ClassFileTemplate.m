classdef ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        ClassFileTemplate
    %% ClassFileTemplate:
    %
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: 8 $
    % $Date: 2013-01-10 12:57:58 -0500 (Thu, 10 Jan 2013) $
    % $Author: mbiesiad $
    %
    %============== End of Version Control Auto-Text ======================
    
    
    %% CONSTANT PROPERTIES:
    %======================================================================
    properties ( ...
            AbortSet      = false,     ... % = [false]|true
            Abstract      = false,     ... % = [false]|true
            Constant      = true,      ... % = [false]|true
            Dependent     = false,     ... % = [false]|true
            GetAccess     = private,   ... % = [public]|protected|private
            GetObservable = false,     ... % = [false]|true
            Hidden        = false,     ... % = [false]|true
            SetObservable = false,     ... % = [false]|true
            Transient     = false      ... % = [false]|true
            )

        
    end
    
    %% PUBLIC, STATIC METHODS:
    %======================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = false      ... % = [false]|true
            )
        
        function [ ] = someMethod( )
            %% someMethod:
            %
            %--------------------------------------------------------------

            return;
        end
        
    end
    
end

