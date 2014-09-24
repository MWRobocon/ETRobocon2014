classdef  ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        RobotID < Simulink.IntEnumType
    % RobotID: This enumeration is used to indicate the ID of
    % robots available in the ET Robocon Architect performance.
    
    enumeration
        ZUMO_32B0          ( 0 );
        ZUMO_329B          ( 1 );
        NXT                ( 2 );
        SPHERO_ORANGE      ( 3 );
        SPHERO_BLUE        ( 4 );
    end
end