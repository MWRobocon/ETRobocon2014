classdef  ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        OperationModeEnum < Simulink.IntEnumType
    %% OperationModeEnum: This enumeration is used to indicate available
    % mutually-exclusive modes for the ET Robocon robot.
    %
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: 11 $
    % $Date: 2013-01-21 08:26:25 -0500 (Mon, 21 Jan 2013) $
    % $Author: mbiesiad $
    %
    %============== End of Version Control Auto-Text ======================
    
    enumeration
        % The "SKIP" mode exists so that the inner and outer track task
        % lists can have the same size.
        SKIP                      (  0 )
        GYRO_CALIBRATION          (  1 )
        LIGHT_CALIBRATION_ON_TAIL (  2 )
        LIGHT_CALIBRATION_UP      (  3 )
        LINE_TRACKING             (  4 )
        SEE_SAW                   (  5 )
        LIMBO                     (  6 )
        SEE_SAW_MARIO             (  7 )
        SEE_SAW_PRINCESS          (  8 )
        YOSHI                     (  9 )
        PARKING                   (  10 )
        LIGHT_CALIBRATION_LIMBO   (  11 )
        LINE_TRACKING_LIMBO       (  12 )
        LINE_TRACKING_ON_MAP      (  13 )
        LIGHT_CALIBRATION_UP_FLASHING ( 14 )
        LIGHT_CALIBRATION_UP_FLASHING_ON_MAP ( 15 )
    end
    
    
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        function [ defaultValue ] = getDefaultValue( )
            %% getDefaultValue: returns the default value for the
            % enumeration.
            %--------------------------------------------------------------
            
            defaultValue = OperationModeEnum.LINE_TRACKING;
            
            return;
        end
        
        function [ descriptionString ] = getDescription( )
            %% getDescription: Returns a description string based on the
            % "help" output for the class.
            %--------------------------------------------------------------
            
            classNameString = OperationModeEnum.getClassNameString( );
            descriptionString = help( classNameString );
            
            return;
        end
        
        function [ headerFileNameString ] = getHeaderFile( )
            %% getHeaderFile: Returns the name of the header file to be
            % used for this enumeration. In this case, it should be
            % "<class name>.h".
            %--------------------------------------------------------------
            
            classNameString = OperationModeEnum.getClassNameString( );
            
            headerFileNameString = [ classNameString, '.h' ];
            
            return;
        end
        
        function [ classNameAddition ] = addClassNameToEnumNames( )
            %% addClassNameToEnumNames: indicates whether the class name
            % should be added to the enumerated value names in the
            % generated code. In this case, it should not.
            %--------------------------------------------------------------
            
            classNameAddition = false;
            
            return;
        end
        
        function [ dataScope ] = getDataScope( )
            %% getDataScope: Returns an indicator of whether the code
            % associated with this enumeration should be imported or
            % exported. In this case, it is exported.
            %--------------------------------------------------------------
            
            dataScope = 'Exported';
            
            return;
            
        end
        
        function [ fullTrackModeList ] = getInnerTrackModeList(  )
            %% getInnerTrackModeList: returns a list of OperationModeEnum
            % elements indicating the task sequence for inner track.
            %--------------------------------------------------------------


            commonModeList = OperationModeEnum.getCommonModeList( );
            

                    trackSpecificModeList = ...
                        [ ...
                        OperationModeEnum.SEE_SAW, ...
                        OperationModeEnum.STEP, ...
                        OperationModeEnum.PARKING ...
                        ];
  
            
            fullTrackModeList = ...
                [ ...
                commonModeList, ...
                trackSpecificModeList ...
                ];
            return;
        end

        function [ fullTrackModeList ] = getOuterTrackModeList( )
            %% getInnerTrackModeList: returns a list of OperationModeEnum
            % elements indicating the task sequence for inner track.
            %--------------------------------------------------------------

            
            
            commonModeList = OperationModeEnum.getCommonModeList( );
            

                    trackSpecificModeList = ...
                        [ ...
                        OperationModeEnum.DRIFT_TURN, ...
                        OperationModeEnum.PARKING ...
                        ];

            
            fullTrackModeList = ...
                [ ...
                commonModeList, ...
                trackSpecificModeList ...
                ];
            return;
        end
        
        
    end
    
    
    methods ( ...
            Abstract = false,     ... % = [false]|true
            Access   = private,   ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        
        function [ classNameString ] = getClassNameString( )
            %% getClassNameString: returns a character string of the class
            % name (derived off of the file name).
            %--------------------------------------------------------------
            
            thisFilesName = mfilename();
            
            [ ~, classNameString ] = fileparts( thisFilesName );
            
            return;
        end
        
        
        function [ commonModeList ] = getCommonModeList( )
            commonModeList = ...
                [ ...
                OperationModeEnum.GYRO_CALIBRATION, ...
                OperationModeEnum.LIGHT_SENSOR_CALIBRATION, ...
                OperationModeEnum.LINE_TRACKING, ...
                OperationModeEnum.LIMBO ...
                ];
            return;
        end
    end
    
end

