classdef ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        FileSystemUtilities
    %% FileSystemUtilities: This is a set of tools to be useful for file operations.
    % This is a toolbox of useful functions, not a proper "class" per se.
    % Consequently, all methods are static, because instantiation shouldn't
    % be necessary, and sealed, because inheritance shouldn't be necessary.
    %
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: 9 $
    % $Date: 2013-01-13 11:01:58 -0500 (Sun, 13 Jan 2013) $
    % $Author: mbiesiad $
    %
    %============== End of Version Control Auto-Text ======================
    
    %% Constant, public properties:
    %======================================================================
    properties ( ...
            AbortSet      = false,     ... % = [false]|true
            Abstract      = false,     ... % = [false]|true
            Constant      = true,      ... % = [false]|true
            Dependent     = false,     ... % = [false]|true
            GetAccess     = public,    ... % = [public]|protected|private
            GetObservable = false,     ... % = [false]|true
            Hidden        = false,     ... % = [false]|true
            SetObservable = false,     ... % = [false]|true
            Transient     = false      ... % = [false]|true
            )
        
        FILE_SEPARATOR_REGEX = '(\\|/)';
        
        MATLAB_FILE_REGEX = '(.*\.(m|M)$)';
        PCODE_FILE_REGEX  = '(.*\.(p|P)$)';
        MAT_FILE_REGEX    = '(.*\.(m|M)(a|A)(t|T)$)';
        
        SLPRJ_DIRECTORY_REGEX = ...
            [ ...
            '(.*', ...
            FileSystemUtilities.FILE_SEPARATOR_REGEX, ...
            '((s|S)(l|L)(p|P)(r|R)(j|J))', ...
            '($|', FileSystemUtilities.FILE_SEPARATOR_REGEX, ')', ...
            '.*)' ...
            ];
        
        SLPRJ_DIRECTORY_EXCLUSION_REGEX = ...
            [ '^((?!(', FileSystemUtilities.SLPRJ_DIRECTORY_REGEX, ')).)*$' ];
        
        
        % TODO: Populate these with the right regular expressions:
        ERT_GENERATED_CODE_DIRECTORY_REGEX = ...
            [ ];
        
        GRT_GENERATED_CODE_DIRECTORY_REGEX = ...
            [ ];
        
        GENERATED_CODE_DIRECTORY_REGEX = ...
            [ ];
        
        GENERATED_CODE_DIRECTORY_EXCLUSION_REGEX = ...
            [ '^((?!(', FileSystemUtilities.GENERATED_CODE_DIRECTORY_REGEX, ')).)*$' ];
        
        
        MDL_FILE_REGEX    = '(.*\.(m|M)(d|D)(l|L)$)';
        MDLP_FILE_REGEX   = '(.*\.(m|M)(d|D)(l|L)(p|P)$)';
        SLX_FILE_REGEX    = '(.*\.(s|S)(l|L)(x|X)$)';
        SLXP_FILE_REGEX   = '(.*\.(s|S)(l|L)(x|X)(p|P)$)';
        MODEL_FILE_REGEX  = ...
            [ ...
            FileSystemUtilities.MDL_FILE_REGEX,  '|', ...
            FileSystemUtilities.MDLP_FILE_REGEX, '|', ...
            FileSystemUtilities.SLX_FILE_REGEX,  '|', ...
            FileSystemUtilities.SLXP_FILE_REGEX, '|' ...
            ];
    end
    
    %% Public, static, sealed methods:
    %======================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )

        function [ filteredPaths ] = filteredGenPath( varargin )
            %% filteredGenPath: returns the results of "genpath", but filtered to exclude specific directory names, or directory name patterns.
            %
            % Variable arguments:
            %
            % * 'RootDirectory' (Required): The path in which to start the
            %       search.
            %
            % * 'ExactDirectoriesToExclude' (Optional): A cell array of
            %       exact directory name strings that should be excluded
            %       from the search. Default = {}
            %
            % * 'RegularExpressionDirectoriesToExclude' (Optional): A cell
            %       array of regular expression strings. If directory names
            %       match any of these regular expressions, they will be
            %       excluded. Default = {}
            %
            % * 'ReturnCellArray' (Optional): A Boolean flag that indicates
            %       whether the function should return a single
            %       ";"-delimited string, or a cell array of strings.
            %       Default = false
            %
            %--------------------------------------------------------------
            
            requiredVararginProperties = ...
                { ...
                'RootDirectory' ...
                };
            
            defaultVararginPropertiesAndValues = ...
                { ...
                'ExactDirectoriesToExclude', {}, ...
                'RegularExpressionDirectoriesToExclude', {}, ...
                'ReturnCellArray', false ...
                };
            
            vararginPropertyValuesMap = ...
                MATLABUtilities.mapPropertyValuePairs( 'PropertiesAndValues', varargin, ...
                'RequiredProperties', requiredVararginProperties, ...
                'DefaultPropertiesAndValues', defaultVararginPropertiesAndValues );
            
            
            exactDirectoriesToExcludeArgument = ...
                vararginPropertyValuesMap( 'ExactDirectoriesToExclude' );
            
            regularExpressionDirectoriesToExcludeArgument = ...
                vararginPropertyValuesMap( 'RegularExpressionDirectoriesToExclude' );
            
            
            %% Get unfiltered directory list
            unfilteredPathsDelimitedString = ...
                genpath( vararginPropertyValuesMap( 'RootDirectory' ) );
            
            unfilteredPathsCellStr = ...
                textscan( unfilteredPathsDelimitedString, '%s',    ...
                'delimiter',                       pathsep, ...
                'multipleDelimsAsOne',             1 );
            
            unfilteredPathsCellStr = unfilteredPathsCellStr{1};
            
            unfilteredPathQuantity = length( unfilteredPathsCellStr );
            
            pathIndicesToInclude = ones( unfilteredPathQuantity, 1 );
            
            %% Filter directory list for exact names to exclude
            
            
            exactMatchExcludedDirectoryQuantity = ...
                length( exactDirectoriesToExcludeArgument );
            
            
            for excludedDirectoryIndex = 1 : exactMatchExcludedDirectoryQuantity
                currentDirectoryToExclude = ...
                    exactDirectoriesToExcludeArgument{ excludedDirectoryIndex };
                
                pathIndicesToInclude = pathIndicesToInclude & ...
                    cellfun( @isempty, strfind( unfilteredPathsCellStr, currentDirectoryToExclude ) );
                
            end
            
            % Todo: Replace this to use "filter_out_regexp_matches"
            %% Filter directory list for regular expression names to exclude.
            regularExpressionMatchExcludedDirectoryQuantity = ...
                length( regularExpressionDirectoriesToExcludeArgument );
            
            for excludedDirectoryIndex = 1 : regularExpressionMatchExcludedDirectoryQuantity
                currentDirectoryRegularExpressionToExclude = ...
                    regularExpressionDirectoriesToExcludeArgument{ excludedDirectoryIndex };
                
                pathIndicesToInclude = pathIndicesToInclude & ...
                    cellfun( @isempty, regexp( unfilteredPathsCellStr, currentDirectoryRegularExpressionToExclude ) );
                
            end
            
            %% Format list into a delimited string
            filteredPathsCellStr = ...
                unfilteredPathsCellStr( logical(pathIndicesToInclude) );
            
            
            if( vararginPropertyValuesMap( 'ReturnCellArray' ) == true )
                filteredPaths = filteredPathsCellStr;
            else
                if( isempty( filteredPathsCellStr ) == true )
                    % There are no paths to return.
                    filteredPaths = [];
                else
                    
                    delimitedFilteredPathsCellStr = ...
                        strcat( filteredPathsCellStr, pathsep );
                    filteredPaths = ...
                        [ delimitedFilteredPathsCellStr{:} ];
                end
            end
            
            
            
            return;
        end

        function [ matchingFileFullNamesCellStr, matchingDirectoriesCellStr, matchingFileQuantity, matchingDirectoryQuantity ] = findDirectoryContents( varargin )
            %% findDirectoryContents: returns separate cell arrays of sub-files and sub-directories.
            % Variable arguments can specify a different starting directory
            % and/or a regular expression to use for filtering the results.
            %
            % Variable arguments:
            %
            % 'RootDirectory' [ = pwd ]: the directory in which to start
            %     the search.
            %
            % 'MatchPatternRegularExpression' [ = '.*' ]: The regular
            %     expression used to filter names (applied to the whole
            %     path).
            %
            %--------------------------------------------------------------
            
            %% Parse the variable arguments:
            requiredProperties = ...
                { ...
                };
            
            defaultPropertiesAndValues = ...
                { ...
                'RootDirectory',                 pwd, ...
                'MatchPatternRegularExpression', '.*' ...
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
            
            %% Get the full directory listing:
            [ directoryFullNamesCellStr, fileFullNamesCellStr ] = ...
                FileSystemUtilities.findRecursiveDirectoryContents( propertyValuesMap( 'RootDirectory' ) );
            
            %% Filter the listing:
            % Unfortunately, we can't "filter as we go" during the search.
            % Directories can't be pruned mid-search because we don't know
            % what's in them, and the specified regular expression might
            % actually filter across a multi-directory + file name pattern.
            % So, we have to filter *after* we get the full directory
            % listing.
            [ matchingFileFullNamesCellStr, matchingFileQuantity ] = ...
                FileSystemUtilities.filterCellstrBasedOnRegularExpression( fileFullNamesCellStr, propertyValuesMap( 'MatchPatternRegularExpression' ) );
            
            [ matchingDirectoriesCellStr, matchingDirectoryQuantity ] = ...
                FileSystemUtilities.filterCellstrBasedOnRegularExpression( directoryFullNamesCellStr, propertyValuesMap( 'MatchPatternRegularExpression' ) );
            
            return;
        end
                
        function [ relativePathString ] = convertAbsolutePathToRelativePath( originDirectoryAbsolutePathString, destinationDirectoryAbsolutePathString )
            %% convertAbsolutePathToRelativePath: This calculates the relative path between two specified absoulte paths.
            %
            % Known issues:
            %
            % * This probably doesn't work with paths that were generated
            % on one operating system but are being converted on another.
            %
            %--------------------------------------------------------------
            relativePathString = '';
            
            originDirectoryPathCellStr = ...
                regexp( originDirectoryAbsolutePathString, filesep, 'split' );
            
            destinationDirectoryPathCellStr = ...
                regexp( destinationDirectoryAbsolutePathString, filesep, 'split' );
            
            %% Confirm that a relative path between the directories
            % is possible:
            if( true == ispc( ) )
                
                originDriveLetter = ...
                    originDirectoryPathCellStr{ 1 };
                
                destinationDriveLetter = ...
                    destinationDirectoryPathCellStr{ 1 };
                
                assert( ( true == strcmp( originDriveLetter, destinationDriveLetter ) ), ...
                    'The origin and destination directories are not on the same drive, so there is no relative path between them. ' );
            else
                % Linux always starts with the file system root, so there
                % is always a relative path.
            end
            
            
            %% Skip over any overlapping path root segments:
            originDirectoryPathDepth = ...
                numel( originDirectoryPathCellStr );
            
            destinationDirectoryPathDepth = ...
                numel( destinationDirectoryPathCellStr );
            
            maximumPotentiallyOverlappingPathDepth = ...
                min( originDirectoryPathDepth, destinationDirectoryPathDepth );
            
            overlappingPathDepth = 0;
            
            for overlappingPathElementIndex = 1 : maximumPotentiallyOverlappingPathDepth
                currentOriginDirectory = ...
                    originDirectoryPathCellStr{ overlappingPathElementIndex };
                
                currentDestinationDirectory = ...
                    destinationDirectoryPathCellStr{ overlappingPathElementIndex };
                
                if( true == strcmp( currentOriginDirectory, currentDestinationDirectory ) )
                    
                    overlappingPathDepth = overlappingPathDepth + 1;
                    
                else
                    % We have found the maximum depth of the overlap.
                    break;
                end
                
            end
            
            %% Add ".." repeatedly to get out of the origin directory until
            % reaching the overlap section.
            for pathsToBackOutIndex = overlappingPathDepth : originDirectoryPathDepth
                relativePathString = ...
                    fullfile( relativePathString, '..' );
            end
            
            %% Add the remaining segment of the destination directory
            % past the overlapping section:
            
            % There's probably a smoother way to do this with expanding the
            % cell array:
            for pathsToContinue = overlappingPathDepth : destinationDirectoryPathDepth
                currentDestinationDirectory = ...
                    destinationDirectoryPathCellStr{ pathsToContinue };
                
                relativePathString = ...
                    fullfile( relativePathString, currentDestinationDirectory );
            end
            
            return;
        end
                
        function [ destinationDirectoryAbsolutePathString ] = convertRelativePathToAbsolutePath( startingDirectoryAbsolutePathString, destinationDirectoryRelativePathString )
            %% convertRelativePathToAbsolutePath: converts the specified relative path to an absolute path.
            %--------------------------------------------------------------
            originalDirectory = pwd;
            cd( startingDirectoryAbsolutePathString );
            cd( destinationDirectoryRelativePathString );
            destinationDirectoryAbsolutePathString = pwd;
            cd( originalDirectory );
            return;
        end
        
    end
    
    %% Private, static, sealed methods:
    %======================================================================
    methods ( ...
            Abstract = false,     ... % = [false]|true
            Access   = private,   ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )

        function [ filteredCellStr, matchQuantity ] = filterCellstrBasedOnRegularExpression( originalCelltr, regularExpression )
            %% filterCellstrBasedOnRegularExpression: returns a cell array of only those elements that match the regular expression.
            %--------------------------------------------------------------
            
            filteredCellStr = { };
            matchQuantity = 0;
            
            originalElementQuantity = numel( originalCelltr );
            
            for elementIndex = 1 : originalElementQuantity
                
                currentElementName = ...
                    originalCelltr{ elementIndex };
                
                matchesRegularExpression = ...
                    regexp( currentElementName, regularExpression, 'once' );
                
                if( true == matchesRegularExpression )
                    
                    filteredCellStr{ end + 1 } = ...
                        currentElementName; %#ok<AGROW> We can't predict the number of matches.
                    
                    matchQuantity = matchQuantity + 1;
                    
                else
                    % Don't add it.
                end
                
            end
            return;
        end
                
        function [ directoryFullNamesCellStr, filesFullNamesCellStr, directoryQuantity, fileQuantity ] = findIndividualDirectoryContents( rootDirectory )
            %% findIndividualDirectoryContents: Returns the files, folders
            % and their quantities of a single directory.
            %--------------------------------------------------------------
            
            % The "dir" command's results include "." and "..",
            % which will need to be skipped later on:
            currentDirectoryListingStructureArray = ...
                dir( rootDirectory );
            
            nameExtractionFunctionHandle = ...
                @(currentDirectoryListing) currentDirectoryListing.name;
            
            currentDirectoryListingShortNames = ...
                arrayfun( nameExtractionFunctionHandle, ...
                currentDirectoryListingStructureArray, ...
                'UniformOutput', false );
            
            directoryFlagExtractionFunctionHandle = ...
                @(currentDirectoryListing) currentDirectoryListing.isdir;
            
            directoryFlagsCellArray = ...
                arrayfun( directoryFlagExtractionFunctionHandle, ...
                currentDirectoryListingStructureArray, ...
                'UniformOutput', false );
            
            directoryIndicationLogicalIndices = ...
                [ directoryFlagsCellArray{ : } ];
            
            allDirectoryShortNamesCellStr = ...
                currentDirectoryListingShortNames( directoryIndicationLogicalIndices );
            
            totalDirectoryQuantity = ...
                sum( uint8( directoryIndicationLogicalIndices ) );
            
            % The "." and ".." are not always the first directories in the
            % list, so they must be actively sought and removed:
            if( 2 < totalDirectoryQuantity )
                currentDirectoryLogicalIndex = ...
                    strcmp( '.', allDirectoryShortNamesCellStr );
                
                parentDirectoryLogicalIndex = ...
                    strcmp( '..', allDirectoryShortNamesCellStr );
                
                actualSubDirectoryLogicalIndices = ...
                    (~( currentDirectoryLogicalIndex | parentDirectoryLogicalIndex) );
                
                directoryShortNamesCellStr = ...
                    allDirectoryShortNamesCellStr( actualSubDirectoryLogicalIndices );
                
                directoryFullNamesCellStr = ...
                    fullfile( rootDirectory, directoryShortNamesCellStr );
                
                directoryQuantity = totalDirectoryQuantity - 2;
                
            else
                % The only entries are "." and "..", which should be
                % skipped.
                directoryFullNamesCellStr = { };
                directoryQuantity = 0;
            end
            
            file_indication_logical_indices = ...
                (~directoryIndicationLogicalIndices);
            
            file_short_names_cellstr = ...
                currentDirectoryListingShortNames( file_indication_logical_indices );
            filesFullNamesCellStr = ...
                fullfile( rootDirectory, file_short_names_cellstr );
            
            fileQuantity = sum( uint8( file_indication_logical_indices ) );
            
            
            return;
        end
        
        function [ subDirectoryFullNamesCellStr, subDirectoryFileFullNamesCellStr, subDirectoryQuantity, subDirectoryFileQuantity ] = findRecursiveDirectoryContents( rootDirectory )
            %% findRecursiveDirectoryContents: returns a cell arrays of
            % the filesand directories below the specified root directory,
            % as well as the number of directories and files.
            %--------------------------------------------------------------
            
            %% Get the current directory contents:
            [ ...
                immediateSubDirectoryFullNamesCellStr, ...
                immediateSubDirectoryFileFullNamesCellStr, ...
                immediateSubDirectoryQuantity, ...
                immediateSubDirectoryFileQuantity ...
                ] = ...
                FileSystemUtilities.findIndividualDirectoryContents( rootDirectory );
            
            %% Use those contents as the starting point for the results:
            subDirectoryFullNamesCellStr = ...
                immediateSubDirectoryFullNamesCellStr;
            
            subDirectoryFileFullNamesCellStr = ...
                immediateSubDirectoryFileFullNamesCellStr;
            
            subDirectoryQuantity = ...
                immediateSubDirectoryQuantity;
            
            subDirectoryFileQuantity = ...
                immediateSubDirectoryFileQuantity;
            
            %% Recurse through the directories, concatenating the results
            % as we find them:
            for immediateSubDirectoryIndex = 1 : immediateSubDirectoryQuantity
                
                currentImmediateSubDirectory = ...
                    immediateSubDirectoryFullNamesCellStr{ immediateSubDirectoryIndex };
                [ ...
                    subSubDirectoryFullNamesCellStr, ...
                    subSubDirectoryFilesFullNamesCellStr, ...
                    subSubDirectoryQuantity, ...
                    subSubDirectoryFileQuantity ...
                    ] = ...
                    FileSystemUtilities.findRecursiveDirectoryContents( currentImmediateSubDirectory );
                
                subDirectoryFullNamesCellStr = ...
                    [ ...
                    subDirectoryFullNamesCellStr; ...
                    subSubDirectoryFullNamesCellStr ...
                    ]; %#ok<AGROW> We can't anticipate how many there will be.
                
                subDirectoryFileFullNamesCellStr = ...
                    [ ...
                    subDirectoryFileFullNamesCellStr; ...
                    subSubDirectoryFilesFullNamesCellStr ...
                    ]; %#ok<AGROW> We can't anticipate how many there will be.
                
                subDirectoryQuantity = ...
                    subDirectoryQuantity + subSubDirectoryQuantity;
                
                subDirectoryFileQuantity = ...
                    subDirectoryFileQuantity + subSubDirectoryFileQuantity;
                
            end
            
            return;
        end
        
                
    end
    
end

