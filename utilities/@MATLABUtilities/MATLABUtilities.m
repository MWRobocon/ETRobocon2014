classdef  ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        MATLABUtilities
    %% MATLABUtilities: A collection of tools that are useful within MATLAB.
    % This is a toolbox of useful functions, not a proper "class" per se.
    % Consequently, all methods are static, because instantiation shouldn't
    % be necessary, and sealed, because inheritance shouldn't be necessary.
    %    
    %
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: 12 $
    % $Date: 2013-01-25 15:01:08 -0500 (Fri, 25 Jan 2013) $
    % $Author: mbiesiad $
    %
    %============== End of Version Control Auto-Text ======================
    
    %% Public, static methods:
    %  ====================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        
        function [ aggregateEqualityResult, commonFieldsWithDifferentValuesCellstr, commonFieldsWithMatchingValuesCellstr, objectAExclusiveSubFieldNamesCellstr, objectBExclusiveSubFieldNamesCellstr ] = compareObjectsRecursively( objectA, objectB )
            %% compareObjectsRecursively: Compares two objects' or structures on a field-by-field basis.
            % Returns the following:
            %
            % aggregateEqualityResult: a boolean value that is only "true"
            %   if both objects only have identical sub-field names and
            %   the values of each of those sub-fields are equal.
            %
            % commonFieldsWithDifferentValuesCellstr: a cell array of
            %   strings listing sub-fields that are common to both
            %   "objectA" and "objectB", but whose values are not equal.
            %
            % commonFieldsWithMatchingValuesCellstr: a cell array of
            %   strings listing sub-fields that are commong to both
            %   "objectA" and "objectB" with equal values.
            %
            % objectAExclusiveSubFieldNamesCellstr: A cell array of
            %   strings listing sub-fields that are present in "objectA",
            %   but not in "objectB".
            %
            % objectBExclusiveSubFieldNamesCellstr: A cell array of
            %  strings listing sub-fields that are present in "objectB",
            %  but not in "objectA".
            %
            %--------------------------------------------------------------
            
            aggregateEqualityResult = true;
            
            objectAFieldNamesCellstr = ...
                MATLABUtilities.getFieldNamesCellstr( objectA );
            
            objectBFieldNamesCellstr = ...
                MATLABUtilities.getFieldNamesCellstr( objectB );
            
            % The set operations are computationally expensive, so we
            % shouldn't do them if they aren't going to be used.
            objectAExclusiveSubFieldNamesCellstr = ...
                setdiff( objectAFieldNamesCellstr, objectBFieldNamesCellstr );
            
            if( true == isempty( objectAExclusiveSubFieldNamesCellstr ) )
                % Everything is cool so far.
            else
                aggregateEqualityResult = false;
            end
            
            objectBExclusiveSubFieldNamesCellstr = ...
                setdiff( objectBFieldNamesCellstr, objectAFieldNamesCellstr );
            
            if( true == isempty( objectBExclusiveSubFieldNamesCellstr ) )
                % Everything might be cool, if previous results were cool
                % too.
            else
                aggregateEqualityResult = false;
            end
            
            commonSubFieldNamesCellstr = ...
                intersect( objectAFieldNamesCellstr, objectBFieldNamesCellstr );
            
            commonSubFieldNameQuantity = ...
                numel( commonSubFieldNamesCellstr );
            
            commonFieldsWithMatchingValuesCellstr = { };
            
            commonFieldsWithDifferentValuesCellstr = { };
            
            for commonSubFieldIndex = 1 : commonSubFieldNameQuantity
                currentSubFieldName = ...
                    commonSubFieldNamesCellstr{ commonSubFieldIndex };
                
                objectASubField = ...
                    eval( [ 'objectA.', currentSubFieldName ] );
                
                objectBSubField = ...
                    eval( [ 'objectB.', currentSubFieldName ] );
                
                if( ( true == isempty( objectASubField ) ) && ( true == isempty( objectBSubField ) ) )
                    currentComparisonResult = true;
                else
                    currentComparisonResult = ...
                        ( objectASubField == objectBSubField );
                end
                
                
                if( true == currentComparisonResult )
                    commonFieldsWithMatchingValuesCellstr{ ( end + 1 ) } = ...
                        currentComparisonResult; %#ok<AGROW> We can't anticipate how this will grow.
                else
                    aggregateEqualityResult = false;
                    
                    commonFieldsWithDifferentValuesCellstr{ ( end + 1 ) } = ...
                        currentComparisonResult; %#ok<AGROW> We can't anticipate how this will grow.
                end
                
            end
            
            return;
        end
        
        function [ deletedFilesCellStr ] = deletePCodedFiles( varargin )
            %% deletePCodedFiles: recursively finds all ".p" files and deletes them.
            %
            % Variable argument property-value pairs:
            %
            % 'RootDirectory'[ = pwd ]: The starting directory for the
            %     search.
            %
            % 'DeleteOrphanPCodeFiles' [ = false ]: Force the deletion of
            %     ".p" files even if there is no corresponding ".m" file.
            %
            %--------------------------------------------------------------
            
            %% Parse the variable arguments:
            requiredProperties = ...
                { ...
                };
            
            defaultPropertiesAndValues = ...
                { ...
                'RootDirectory', pwd, ...
                'DeleteOrphanPCodeFiles', false ...
                };
            
            propertyValuesMap = ...
                MATLABUtilities.mapPropertyValuePairs( 'PropertiesAndValues', varargin, ...
                'DefaultPropertiesAndValues', defaultPropertiesAndValues, ...
                'RequiredProperties', requiredProperties );
            
            %% Validate the arguments:
            rootDirectoryExistence = ...
                ( 0 < (exist( propertyValuesMap( 'RootDirectory' ), 'dir' ) ) );
            
            assert( ( true == rootDirectoryExistence ), ...
                [ 'The proposed "RootDirectory", "', propertyValuesMap( 'RootDirectory' ), '" does not exist.' ] );
            
            [ matchingFileFullNameCellStr, ~, matchingFileQuantity ] = ...
                FileSystemUtilities.findDirectoryContents( 'RootDirectory', propertyValuesMap( 'RootDirectory' ), 'MatchPatternRegularExpression', FileSystemUtilities.PCODE_FILE_REGEX );
            
            deletedFilesCellStr = { };
            for fileIndex = 1 : matchingFileQuantity
                currentPFile = matchingFileFullNameCellStr{ fileIndex };
                
                [ currentFilePath, currentFileShortName ] = ...
                    fileparts( currentPFile );
                
                correspondingMATLABFile = ...
                    fullfile( currentFilePath, [ currentFileShortName, '.m' ] );
                
                correspondingMATLABFileExistence = ...
                    ( 0 < exist( correspondingMATLABFile, 'file' ) );
                
                if( ( true == correspondingMATLABFileExistence ) || ...
                        ( true == propertyValuesMap( 'DeleteOrphanPCodeFiles' ) ) )
                    
                    deletedFilesCellStr{ end + 1 } = ...
                        currentPFile; %#ok<AGROW> We can't anticipate how many matches we'll have.
                    
                    delete( currentPFile );
                else
                    % Don't delete files without corresponding
                    % ".m" files.
                    warningMessage = ...
                        [ ...
                        'Not deleting "', ...
                        currentPFile, ...
                        '" because it does not have a corresponding ".m" file. If you want to force deletion of "orphan" ".p" files, please use the "DeleteOrphanPCodeFiles" option.' ...
                        ];
                    warning( warningMessage );
                end
                
            end
            
            return;
        end
                
        function [ structure_field_names_cellstr ] = getFieldNamesCellstr( matlabStructureOrObjectInstance )
            %% getStructureFieldNamesCellstr: returns a cell array of strings containing the sub-fields of the structure or object.
            %--------------------------------------------------------------
            
            assert( ( true == MATLABUtilities.isAggregateType( matlabStructureOrObjectInstance ) ), ...
                'The argument must be a MATLAB structure.' );
            
            structure_field_names_cellstr = ...
                MATLABUtilities.getRecursiveSubFieldsCellstr( '', matlabStructureOrObjectInstance  );
            
            
        end
        
        function [ result ] = isAggregateType( potentialObjectOrStruct )
            %% isAggregateType: returns "true" if the argument is "anything with sub-fields", such as a structure or object.
            % It hasn't been tested, but it likely would return "true" even
            % for objects that happen to lack properties (i.e. an "all
            % methods" object).
            %--------------------------------------------------------------
            
            if( true == isa( potentialObjectOrStruct, 'struct' ) )
                result = true;
            elseif( true == isobject( potentialObjectOrStruct ) )
                result = true;
            elseif( isa( potentialObjectOrStruct, 'handle.handle' ) )
                % This is the check for UDD objects, which was accepted on
                % blind faith in those wiser than me.
                result = true;
            else
                result = false;
            end
            return;
        end
        
        function [ propertyValuesMap ] = mapPropertyValuePairs( varargin )
            %% mapPropertyValuePairs: returns a "containers.Map" object with keys for all properties and values for their values.
            %
            % Variable arguments:
            %
            % * 'PropertiesAndValues'
            %
            % * 'DefaultPropertiesAndValues'
            %
            % * 'RequiredProperties'
            %
            %--------------------------------------------------------------
            
            [ propertiesAndValuesArgument, requiredPropertiesArgument, defaultPropertiesAndValuesArgument ] = ....
                MATLABUtilities.parseVarargin( varargin{ : } );
            
            propertyValuesMap = ...
                containers.Map( 'KeyType', 'char', 'ValueType', 'any' );
            
            %% Populate default values:
            defaultPropertiesAndValuesArgumentExistence = ...
                (~isempty( defaultPropertiesAndValuesArgument ) );
            
            if( defaultPropertiesAndValuesArgumentExistence == true )
                
                assert( ( true == iscell( defaultPropertiesAndValuesArgument ) ), ...
                    '"DefaultPropertiesAndValues" argument must be a cell array.' );
                
                
                % There should be a smooth way to just use
                % "default_properties_and_values_argument" in the containers.Map
                % constructor, but it is unclear.
                
                defaultArgumentQuantity = ...
                    length( defaultPropertiesAndValuesArgument );
                
                for defaultArgumentIndex = 1 : 2: defaultArgumentQuantity
                    
                    if( defaultArgumentIndex < defaultArgumentQuantity )
                        
                        defaultArgumentPropertyName = ...
                            defaultPropertiesAndValuesArgument{ defaultArgumentIndex };
                        
                        defaultArgumentPropertyValue = ...
                            defaultPropertiesAndValuesArgument{ defaultArgumentIndex + 1 };
                        
                        propertyValuesMap( defaultArgumentPropertyName ) = ...
                            defaultArgumentPropertyValue;
                    else
                        error( 'Default properties and values are not evenly paired.' );
                    end
                    
                end
            else
                % This argument is optional.
            end
            
            %% Add/Overwrite property values
            MATLABUtilities.validatePropertiesAndValuesArgument( propertiesAndValuesArgument );
            
            propertyValuePairQuantity = length( propertiesAndValuesArgument );
            
            for propertyValuePairIndex = 1 : 2 : propertyValuePairQuantity
                
                currentPropertyName = propertiesAndValuesArgument{ propertyValuePairIndex };
                
                currentPropertyNameIsString = ischar( currentPropertyName );
                
                if( currentPropertyNameIsString == true )
                    if( propertyValuePairIndex < propertyValuePairQuantity )
                        value = propertiesAndValuesArgument{ propertyValuePairIndex + 1 };
                        
                        propertyValuesMap( currentPropertyName ) = value;
                        
                    else
                        error( '"PropertiesAndValues" names and values are not evenly paired.' );
                    end
                else
                    error( '"PropertiesAndValues" property names must be strings.' );
                end
                
            end
            
            %% Confirm presence of required properties:
            requiredPropertiesArgumentExistence = ...
                (~isempty( requiredPropertiesArgument ) );
            
            if( requiredPropertiesArgumentExistence == true )
                
                %MATLABUtilities.validate_required_properties_argument( requiredPropertiesArgument );
                assert( ( true == iscellstr( requiredPropertiesArgument ) ), ...
                    '"RequiredProperties" must be a cell array of strings.' );
                
                requiredPropertiesQuantity = length( requiredPropertiesArgument );
                for required_properties_index = 1 : requiredPropertiesQuantity
                    
                    currentRequiredProperty = ...
                        requiredPropertiesArgument{ required_properties_index };
                    
                    propertyValuesMapHasProperty = ...
                        propertyValuesMap.isKey( currentRequiredProperty );
                    
                    if( propertyValuesMapHasProperty == true )
                        % OK
                    else
                        error_message = ...
                            [ currentRequiredProperty, ' is a required property.' ];
                        error( error_message );
                    end
                end
            else
                % This argument is optional.
            end
            
            return;
            
        end
        
        function [ pCodedFullFileNamesCellStr, originalMATLABFullFileNamesCellStr ] = pCodeAllMATLABFiles( varargin )
            %% pCodeAllMATLABFiles: recursively finds all ".m" files and p-codes them.
            %
            % Variable argument property-value pairs:
            %
            % 'RootDirectory'[ = pwd ]: The starting directory for the
            %     search.
            %--------------------------------------------------------------
            
            originalDirectory = pwd;
            
            requiredProperties = ...
                { ...
                };
            
            defaultPropertiesAndValues = ...
                { ...
                'RootDirectory', pwd, ...
                };
            
            propertyValuesMap = ...
                MATLABUtilities.mapPropertyValuePairs( 'PropertiesAndValues', varargin, ...
                'DefaultPropertiesAndValues', defaultPropertiesAndValues, ...
                'RequiredProperties', requiredProperties );
            
            [ originalMATLABFullFileNamesCellStr, ~, matlabFileQuantity ] = ...
                FileSystemUtilities.findDirectoryContents( 'RootDirectory', propertyValuesMap( 'RootDirectory' ), 'MatchPatternRegularExpression', FileSystemUtilities.MATLAB_FILE_REGEX );
            
            pCodedFullFileNamesCellStr = cell( 1, matlabFileQuantity );
            
            for matlabFileIndex = 1 : matlabFileQuantity
                currentMATLABFileName = ...
                    originalMATLABFullFileNamesCellStr{ matlabFileIndex };
                [ targetDirectory, shortFileName ] = ...
                    fileparts( currentMATLABFileName );
                cd( targetDirectory );
                
                pcode( currentMATLABFileName );
                
                pCodedFullFileNamesCellStr{ matlabFileIndex } = ...
                    fullfile( targetDirectory, [ shortFileName, '.p' ] );
                
            end
            
            cd( originalDirectory );
            return;
        end
               
    end
    
    %% Private, static methods:
    %  ========================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = private,   ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        
        function [ leafSubFieldNamesCellStr, nonLeafSubFieldNamesCellStr ] = getImmediateSubFieldsCellstr( matlabStructure )
            %% getImmediateSubFieldsCellstr: returns two string cell arrays, separating the sub-fields into leaf nodes and non-leaf nodes.
            %--------------------------------------------------------------
            
            leafSubFieldNamesCellStr     = { };
            
            nonLeafSubFieldNamesCellStr = { };
            
            subFieldNamesCellStr = fieldnames( matlabStructure );
            
            subFieldQuantity = numel( subFieldNamesCellStr );
            
            for subFieldIndex = 1 : subFieldQuantity
                currentSubFieldName = ...
                    subFieldNamesCellStr{ subFieldIndex };
                
                currentSubFieldNameAccessString = ...
                    [ 'matlab_structure.', currentSubFieldName ];
                
                currentSubField = eval( currentSubFieldNameAccessString );
                
                if( true == MATLABUtilities.isAggregateType( currentSubField ) )
                    nonLeafSubFieldNamesCellStr{ ( end + 1 ), 1 } = ...
                        currentSubFieldName; %#ok<AGROW> We cannot predict the number of structure sub-fields
                else
                    leafSubFieldNamesCellStr{ ( end + 1 ), 1 } = ...
                        currentSubFieldName; %#ok<AGROW> We cannot predict the number of non-structure sub-fields
                end
                
            end
            
            return;
        end
        
        function [ subFieldNamesCellStr ] = getRecursiveSubFieldsCellstr( parentStructureNameString, matlabStructure )
            %% getRecursiveSubFieldsCellstr: recursively accumulates a cell array of strings containing the sub-fields of the structure or object.
            %--------------------------------------------------------------
            
            recursiveNonLeafSubFieldNamesCellStr = { };
            
            [ leafSubFieldNamesCellStr, nonLeafSubFieldNamesCellStr ] = ...
                MATLABUtilities.getImmediateSubFieldsCellstr( matlabStructure );
            
            nonLeafSubFieldQuantity = numel( nonLeafSubFieldNamesCellStr );
            
            if( true == isempty( parentStructureNameString ) )
                % This is the "root" of the recursive calls and shouldn't
                % include the ".".
                nonLeafSubFieldFullNamesCellStr = ...
                    strcat( parentStructureNameString, nonLeafSubFieldNamesCellStr );
            else
                nonLeafSubFieldFullNamesCellStr = ...
                    strcat( parentStructureNameString, '.', nonLeafSubFieldNamesCellStr );
            end
            
            for nonLeafSubFieldIndex = 1 : nonLeafSubFieldQuantity
                
                currentSubFieldShortName = ...
                    nonLeafSubFieldNamesCellStr{ nonLeafSubFieldIndex };
                
                currentSubFieldFullName = ...
                    nonLeafSubFieldFullNamesCellStr{ nonLeafSubFieldIndex };
                
                subStructureAccessString = ...
                    [ 'matlab_structure.', currentSubFieldShortName ];
                
                matlabStructureSubStructure = ...
                    eval( subStructureAccessString );
                
                recursiveSubFieldNamesCellStr = ...
                    MATLABUtilities.getRecursiveSubFieldsCellstr( currentSubFieldFullName, matlabStructureSubStructure );
                
                recursiveNonLeafSubFieldNamesCellStr = ...
                    [ recursiveNonLeafSubFieldNamesCellStr; recursiveSubFieldNamesCellStr ]; %#ok<AGROW> We can't anticipate the eventual size of this cell array.
                
            end
            
            if( true == isempty( parentStructureNameString ) )
                % This is the "root" of the recursive calls and shouldn't
                % include the ".".
                leafSubFieldFullNamesCellStr = ...
                    strcat( parentStructureNameString,  leafSubFieldNamesCellStr );
                
            else
                leafSubFieldFullNamesCellStr = ...
                    strcat( parentStructureNameString, '.', leafSubFieldNamesCellStr );
            end
            
            
            subFieldNamesCellStr = ...
                [ recursiveNonLeafSubFieldNamesCellStr; leafSubFieldFullNamesCellStr ];
            
            return;
        end
                        
        function [ propertiesAndValuesArgument, requiredPropertiesArgument, defaultPropertiesAndValuesArgument ] = parseVarargin( varargin )
            %% parseVarargin sorts through the input arguments (this is the way we
            % used to do it before this file's function was created
            %--------------------------------------------------------------
            
            propertiesAndValuesArgument        = [];
            requiredPropertiesArgument         = [];
            defaultPropertiesAndValuesArgument = [];
            
            %% Parse this function's varargin
            for vararginIndex = 1 : 2 : nargin
                
                propertyName = varargin{ vararginIndex };
                
                propertyNameIsString = ischar( propertyName );
                
                if( propertyNameIsString == true )
                    
                    if( vararginIndex < nargin )
                        
                        value = varargin{ vararginIndex + 1 };
                        
                        switch propertyName
                            
                            case 'PropertiesAndValues'
                                
                                propertiesAndValuesArgument = value;
                                
                            case 'RequiredProperties'
                                
                                requiredPropertiesArgument = value;
                                
                            case 'DefaultPropertiesAndValues'
                                
                                defaultPropertiesAndValuesArgument = value;
                                
                            otherwise
                                
                                errorMessage = ...
                                    [ ...
                                    'Invalid function call argument: "', ...
                                    propertyName,                       ...
                                    '".'                                 ...
                                    ];
                                error( errorMessage );
                                
                        end
                        
                    else
                        % This means that the "PropertiesAndValues" argument was empty,
                        % which may be OK.
                        %error( 'Property names and values are not evenly paired.' );
                    end
                else
                    error( 'Property names must be strings.' );
                end
                
            end
            
            return;
            
        end
        
        function [ ] = validatePropertiesAndValuesArgument( propertiesAndValuesArgument )
            %% validatePropertiesAndValuesArgument confirms the
            % "PropertiesAndValues" argument exists and is a cell array and throws an
            % error otherwise.
            %--------------------------------------------------------------
            
            propertiesAndValuesArgumentExistence = ...
                (~isempty( propertiesAndValuesArgument )  );
            
            if( propertiesAndValuesArgumentExistence == true )
                
                propertiesAndValuesArgumentTypeIsCorrect = ...
                    iscell( propertiesAndValuesArgument );
                
                if( propertiesAndValuesArgumentTypeIsCorrect == true )
                    % Seems OK
                else
                    error( '"PropertiesAndValues" argument must be a cell array.' );
                end
            else
                % "PropertyAndValues" is empty, which may be OK.
                %error( '"PropertiesAndValues" is a required argument.' );
            end
            
            return;
            
        end
        
    end
    
end

