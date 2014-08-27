classdef  ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        OperationModeStatusEnum < Simulink.IntEnumType
    %% OperationModeStatusEnum: This enumeration is used to indicate the
    % current status of an operation mode.
    %
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: 11 $
    % $Date: 2013-01-21 08:26:25 -0500 (Mon, 21 Jan 2013) $
    % $Author: mbiesiad $
    %
    %============== End of Version Control Auto-Text ======================
    
    enumeration
        NOT_STARTED            ( 0 )
        IN_PROGRESS            ( 1 )
        SUCCESSFULLY_COMPLETED ( 2 )
        ABORTED                ( 3 )

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
            
            defaultValue = OperationModeStatusEnum.NOT_STARTED;
            
            return;
        end
        
        function [ descriptionString ] = getDescription( )
            %% getDescription: Returns a description string based on the
            % "help" output for the class.
            %--------------------------------------------------------------
            
            classNameString = OperationModeStatusEnum.getClassNameString( );
            descriptionString = help( classNameString );
            
            return;
        end
        
        function [ headerFileNameString ] = getHeaderFile( )
            %% getHeaderFile: Returns the name of the header file to be
            % used for this enumeration. In this case, it should be
            % "<class name>.h".
            %--------------------------------------------------------------
            
            classNameString = OperationModeStatusEnum.getClassNameString( );
            
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
        
    end
    
end

