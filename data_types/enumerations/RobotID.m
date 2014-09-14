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
        NXT1                ( 1 )
        NXT2                ( 2 )
        ARDUINO             ( 3 )
        LEDCUBE             ( 4 )
        NXT                 ( 5 );
        ZUMO_ADAFRUIT_32B0 ( 6 );
        SPHERO_ORANGE      ( 7 );
        SPHERO_BLUE        ( 8 );
    end
end