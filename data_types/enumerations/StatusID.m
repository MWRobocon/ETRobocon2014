classdef  ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        StatusID < Simulink.IntEnumType
    % StatusID: This enumeration is used to indicate the ID of
    % robots available in the ET Robocon Architect performance.
    
    enumeration
        
        % DO NOT USE THESE NUMBERS
        % They did not work for whatever reason.
        DO_NOT_USE_0                   ( 0  )
        DO_NOT_USE_1                   ( 1  )
        DO_NOT_USE_2                   ( 2  )
        DO_NOT_USE_3                   ( 3  )
        DO_NOT_USE_4                   ( 4  )
        DO_NOT_USE_5                   ( 5  )
        DO_NOT_USE_6                   ( 6  )
        DO_NOT_USE_7                   ( 7  )
        DO_NOT_USE_8                   ( 8  )
        DO_NOT_USE_9                   ( 9  )
        DO_NOT_USE_10                  ( 10 )
        DO_NOT_USE_13                  ( 13 )
        DO_NOT_USE_17                  ( 17 )
        
        % NXT1 ENUMS (11-39)
        NXT1_ON_SEESAW                 ( 11 )
        NXT1_WAITING                   ( 12 )
        NXT1_ON_PIVOT                  ( 16 )
        NXT1_OFF_SEESAW                ( 14 )
        NXT1_TURNED                    ( 15 )
        NXT1_AT_STAGE                  ( 120 )
        NXT1_OFF_RAMP                  ( 121 )
        
        NXT1_GO_BACK                   ( 20 )
        NXT1_SPEED_UP                  ( 21 )
        NXT1_PARK                      ( 22 )
        
        NXT1_GO_DOWN_RAMP              ( 25 )
        
        % NXT2 ENUMS (40-69)
        NXT2_ON_SEESAW                 ( 40 )
        NXT2_IN_HURRY                  ( 41 )
        NXT2_READY_TO_PARK             ( 42 )
        
        NXT2_STAND                     ( 50 )
        NXT2_START                     ( 51 )
        NXT2_FOLLOW                    ( 52 )
        NXT2_WAIT                      ( 53 )
        NXT2_LEAVE                     ( 54 )
        
        % ROVER ENUMS (70 - 99)
        ROVER_SENSED_RAMP              ( 70 )
               
        % LED CUBE ENUMS (100-160)
        STAR                           ( 100 )
        HEART                          ( 101 )
        FIREWORKS                      ( 102 )
        
    end
    
end