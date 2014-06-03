classdef ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        ETRoboconUtilities
    %% ETRoboconUtilities: This is a set of tools to be useful for the ET Robocon project
    %%============= Start of Version Control Auto-Text ====================
    %
    % $Revision: $
    % $Date:  $
    % $Author: $
    %
    %============== End of Version Control Auto-Text ======================
    
    %% Constant properties:
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
        
        CD_SYSTEM_FUNCTION_DEBUG_ENABLED = false;
        
        CODE_GENERATION_DIRECTORY_ABSOLUTE_PATH = ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'code_generation_directory' );
        
        DOCUMENTATION_ROOT = ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'documentation' );
        
        ET_ROBOCON_REPOSITORY_ROOT_URL = ...
            'http://svn.mathworks.com/asg/asg_repository/trunk/projects/et_robocon';
        
        IMAGE_DIRECTORY_ROOT = ...
            fullfile( ETRoboconUtilities.DOCUMENTATION_ROOT, 'images' );
        
        %------------------------------------------------------------------
        % These paths (but not their subdirectories) will be added to the
        % path. They should be semi-colon separated in order to be
        % concatenated properly in later parts of the code.
        %------------------------------------------------------------------
        LEAF_NODE_PATHS_TO_ADD_CELLSTR = ...
            { ...
            ETRoboconUtilities.WORK_AREA_ABSOLUTE_PATH; ...
            ETRoboconUtilities.SIMULATION_CACHE_DIRECTORY_ABSOLUTE_PATH; ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'data_dictionaries' ) ...
            };
        
        ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING = ...
            'original_simulation_cache_directory';
        
        ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING = ...
            'original_code_generation_directory';
        
        %------------------------------------------------------------------
        % These directories and their sub-directories will be added to the
        % path. They should be semi-colon separated in order to be
        % concatenated properly in later parts of the code.
        %------------------------------------------------------------------
        PATH_ROOTS_TO_ADD_RECURSIVELY_CELLSTR = ...
            { ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'models' ); ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'data_types' ); ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'utilities' ); ...
            fullfile( ETRoboconUtilities.getProjectDocumentationRoot( ) ) ...
            };
        
        PREFERENCES_GROUP_NAME_STRING = 'et_robocon_preferences';
        
        SIMULATION_CACHE_DIRECTORY_ABSOLUTE_PATH = ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'simulation_cache_directory' );
        
        SUBVERSION_DIRECTORY_REGEX = ...
            [ ...
            '(.*', ...
            FileSystemUtilities.FILE_SEPARATOR_REGEX, ...
            '\.(s|S)(v|V)(n|N)', ...
            '($|',FileSystemUtilities.FILE_SEPARATOR_REGEX, ')', ...
            '.*)', ...
            ];
        
        SUBVERSION_DIRECTORY_EXCLUSION_REGEX = ...
            [ '^((?!(', ETRoboconUtilities.SUBVERSION_DIRECTORY_REGEX , ')).)*$' ];
        
        % Keyword:
        %---------
        SVN_KEYWORDS_PROPERTY_STRING  = 'svn:keywords';
        SVN_IGNORE_PROPERTY_STRING    = 'svn:ignore';
        SVN_MIME_TYPE_PROPERTY_STRING = 'svn:mime-type';
        
        SVN_PROPSET_COMMAND_STRING = 'svn propset';
        SVN_PROPGET_COMMAND_STRING = 'svn propget';
        
        %svn propset svn:mime-type application/octet-stream <filename>
        % Special keywords:
        %------------------
        
        % "svn:keywords" pre-defined property values:
        %------------------------------------------------------------------
        SVN_AUTHOR_KEYWORD_STRING   = 'Author';
        SVN_DATE_KEYWORD_STRING     = 'Date';
        SVN_HEAD_URL_KEYWORD_STRING = 'HeadURL';
        SVN_HEADER_KEYWORD_STRING   = 'Header';
        SVN_ID_KEYWORD_STRING       = 'Id';
        SVN_REVISION_KEYWORD_STRING = 'Revision';
        
        % "svn:mime-type" pre-defined property values:
        %------------------------------------------------------------------
        SVN_BINARY_FILE_MIME_TYPE_STRING = 'application/octet-stream';
        
        SVN_INFO_COMMAND_STRING    = 'svn info'
        
        %% This folder is only accessible from Windows for now.
        TORTOISE_SVN_INSTALLATION_EXECUTABLE_ABSOLUTE_PATH = ...
            '\\MATHWORKS\SalesService\technical_support\asg\svn\configuration_management_tools\tortoise';
        
        WORK_AREA_ABSOLUTE_PATH = ...
            fullfile( ETRoboconUtilities.getCheckoutRoot( ), 'work_area' );
    end
    
    %% Public, static methods:
    %======================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = false      ... % = [false]|true
            )
        
        function [ preExistingProperties ] = getFileSubversionKeywords( fileFullName )
            %% [ preExistingProperties ] = fetFileSubversionKeywords( fileFullName ):
            %
            %==============================================================
            
            [ filePath, fileShortName, fileExtension ] = ...
                fileparts( fileFullName );
            
            commandStringToExecute = ...
                [ ...
                ETRoboconUtilities.SVN_PROPGET_COMMAND_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_KEYWORDS_PROPERTY_STRING, ...
                ' ', ...
                [ fileShortName, fileExtension ] ...
                ];
            
            [ ~, preExistingProperties ] = ...
                ETRoboconUtilities.cdSystem( filePath, commandStringToExecute );
            
            return;
        end
        
        
        function [ ] = setFileSubversionKeywords( fileFullName )
            %% [ ] = setFileSubversionKeywords( fileFullName ):
            %
            %==============================================================
            
            [ filePath, fileShortName, fileExtension ] = ...
                fileparts( fileFullName );
            
            commandStringToExecute = ...
                [ ...
                ETRoboconUtilities.SVN_PROPSET_COMMAND_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_KEYWORDS_PROPERTY_STRING, ...
                ' "', ...
                ETRoboconUtilities.SVN_AUTHOR_KEYWORD_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_DATE_KEYWORD_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_HEAD_URL_KEYWORD_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_HEADER_KEYWORD_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_ID_KEYWORD_STRING, ...
                ' ', ...
                ETRoboconUtilities.SVN_REVISION_KEYWORD_STRING, ...
                '" ', ...
                [ fileShortName, fileExtension ] ...
                ];
            
            [ ~, preExistingProperties ] = ...
                ETRoboconUtilities.cdSystem( filePath, commandStringToExecute );
            
            disp( preExistingProperties );
            return;
        end
        
        function [ projectFilesFullNamesCellStr, projectDirectoriesAbsolutePathsCellStr ] = getProjectFilesAndDirectories( )
            %% getProjectFilesAndDirectories: Returns cell arrays of strings for all of the files and directories in the ETRobocon project.
            %
            %==============================================================
            
            [ matchingFileFullNamesCellStr, matchingDirectoriesCellStr ] = ...
                FileSystemUtilities.findDirectoryContents( 'RootDirectory', ETRoboconUtilities.getCheckoutRoot( ), 'MatchPatternRegularExpression', ETRoboconUtilities.SUBVERSION_DIRECTORY_EXCLUSION_REGEX );
            
            projectFileIndices = ...
                cellfun( @ETRoboconUtilities.isPartOfProject, matchingFileFullNamesCellStr );
            
            projectFilesFullNamesCellStr = ...
                matchingFileFullNamesCellStr( projectFileIndices );
            
            projectDirectoryIndices = ...
                cellfun( @ETRoboconUtilities.isPartOfProject, matchingDirectoriesCellStr );
            
            
            projectDirectoriesAbsolutePathsCellStr = ...
                matchingDirectoriesCellStr( projectDirectoryIndices );
            
            return;
        end
        
        function [ ] = clearCodeGenerationDirectory( )
            %% [ ] = clearCodeGenerationDirectory( ) cleans out the generated code directory.
            %
            %--------------------------------------------------------------
            folderContents = ...
                dir( ETRoboconUtilities.getProjectCodeGenerationDirectoryAbsolutePath( ) );
            
            contentQuantity = numel( folderContents );
            
            clear mex;
            
            for folderContentIndex = 1 : contentQuantity
                currentContentStructure = folderContents( folderContentIndex );
                
                currentContentFullName = ...
                    fullfile( ETRoboconUtilities.getProjectCodeGenerationDirectoryAbsolutePath( ), currentContentStructure.name );
                
                if( true == currentContentStructure.isdir )
                    switch( currentContentStructure.name )
                        
                        case { '.', '..', '.svn' }
                            % "." and ".." are always output by "dir" and
                            % represent the current directory and its parent,
                            % respectively. There is also always a ".svn"
                            % folder because *the code-generation folder
                            % itself* is under revision control even if its
                            % contents are not.
                        otherwise
                            % In some parallel universe, "s" means "recurSive".
                            rmdir( currentContentFullName, 's' );
                    end
                else
                    delete( currentContentFullName );
                end
            end
            
            return;
        end
        
        function [ ] = clearSimulationCacheDirectory( )
            %% [ ] = clearSimulationCacheDirectory( ) clears the "slprj" content from the simulation cache directory and the generated ".mex" files.
            %
            %--------------------------------------------------------------
            
            targetDirectory = ...
                fullfile( ETRoboconUtilities.getProjectSimulationCacheDirectoryAbsolutePath( ), 'slprj' );
            
            if( 0 < exist( targetDirectory, 'dir' ) )
                
                % In some parallel universe, "s" means "recurSive".
                rmdir( targetDirectory, 's' );
            else
                % There is nothign to delete.
            end
            
            mexFileStructureList = ...
                dir( fullfile( ETRoboconUtilities.getProjectSimulationCacheDirectoryAbsolutePath( ), [ '*.', mexext ] ) );
            
            mexFileQuantity = numel( mexFileStructureList );
            if( 0 < mexFileQuantity )
                clear mex;
                
                for mexFileIndex = 1 : mexFileQuantity
                    
                    currentMexFileStructure = mexFileStructureList( mexFileIndex );
                    
                    currentMexFileFullName = ...
                        fullfile( ETRoboconUtilities.getProjectSimulationCacheDirectoryAbsolutePath( ), currentMexFileStructure.name );
                    
                    delete( currentMexFileFullName );
                end
                
            else
                % There are no ".mex" files to delete.
            end
            
            return;
        end
        
        function [ ] = generateDocumentation( )
            %% [ ] = generateDocumentation( ): generates all of the automatically-generated documentation.
            %
            %--------------------------------------------------------------
            
            ETRoboconUtilities.generateRepositoryInstructions( );
            
            % More documentation sections to follow...
            
            return;
        end
        
        function [ etRoboconCheckoutRootAbsolutePath ] = getCheckoutRoot( )
            %% [ etRoboconCheckoutRootAbsolutePath ] = getCheckoutRoot( ): Returns the absolute path of the root of the checkout.
            %
            %--------------------------------------------------------------
            
            thisFilesFullName = mfilename( 'fullpath' );
            
            thisFilesAbsolutePath = fileparts( thisFilesFullName );
            
            etRoboconCheckoutRootRelativePath = ...
                fullfile( '..', '..' );
            
            etRoboconCheckoutRootAbsolutePath = ...
                FileSystemUtilities.convertRelativePathToAbsolutePath( thisFilesAbsolutePath, etRoboconCheckoutRootRelativePath );
            
            return;
        end
        
        function [ imageDirectoryRootAbsolutePath ] = getImageDirectoryRoot( )
            %% [ imageDirectoryRootAbsolutePath ] = getImageDirectoryRoot( ): returns the root path of the directory containing images used for documentation.
            %
            %--------------------------------------------------------------
            
            imageDirectoryRootAbsolutePath = ...
                ETRoboconUtilities.IMAGE_DIRECTORY_ROOT;
            
            return;
        end
        
        function [ codeGenerationDirectoryAbsolutePath ] = getProjectCodeGenerationDirectoryAbsolutePath( )
            %% [ codeGenerationDirectoryAbsolutePath ] = getProjectCodeGenerationDirectoryAbsolutePath( ): Returns the absolute path of the code-generation directory to use for this project.
            %
            %--------------------------------------------------------------
            
            codeGenerationDirectoryAbsolutePath = ...
                ETRoboconUtilities.CODE_GENERATION_DIRECTORY_ABSOLUTE_PATH;
            
            return;
        end
        
        function [ documentationRootDirectoryAbsolutePath ] = getProjectDocumentationRoot( )
            %% [ documentationRootDirectoryAbsolutePath ] = getProjectDocumentationRoot( ): Returns the root of the documentation directory.
            %
            %--------------------------------------------------------------
            documentationRootDirectoryAbsolutePath = ...
                ETRoboconUtilities.DOCUMENTATION_ROOT;
            
            return;
        end
        
        function [ simulationCacheDirectoryAbsolutePath ] = getProjectSimulationCacheDirectoryAbsolutePath( )
            %% [ simulationCacheDirectoryAbsolutePath ] = getProjectSimulationCacheDirectoryAbsolutePath( ): Returns the absolute path of the simulation cache directory to use for this project.
            %--------------------------------------------------------------
            
            simulationCacheDirectoryAbsolutePath = ...
                ETRoboconUtilities.SIMULATION_CACHE_DIRECTORY_ABSOLUTE_PATH;
            
            return;
        end
        
        function [ workAreaAbsolutePath ] = getWorkAreaAbsolutePath( )
            %% [ workAreaAbsolutePath ] = getWorkAreaAbsolutePath( ): Returns the absolute path to the work area directory
            %
            %==============================================================
            
            workAreaAbsolutePath = ...
                ETRoboconUtilities.WORK_AREA_ABSOLUTE_PATH;
            
            return;
        end
        
        function [ repositoryURL ] = getRepositoryURL( )
            %% [ repositoryURL ] = getRepositoryURL( ): Returns the URL for the repository.
            %
            %--------------------------------------------------------------
            
            repositoryURL = ...
                ETRoboconUtilities.ET_ROBOCON_REPOSITORY_ROOT_URL;
            
            return;
        end
        
        function [ installationExecutableAbsolutePath ] = getTortoiseSVNInstallationExecutablePath( )
            %% [ installationExecutableAbsolutePath ] = getTortoiseSVNInstallationExecutablepath( ): Returns the absolute path of the Tortoise/SVN installation executable.
            %
            %--------------------------------------------------------------
            
            installationExecutableAbsolutePath = ...
                ETRoboconUtilities.TORTOISE_SVN_INSTALLATION_EXECUTABLE_ABSOLUTE_PATH;
            
            return;
        end
        
        
        function [ ] = displayImageForPublishing( imageFileName )
            %% [ ] = displayImageForPublishing( imageFile ): Displays the specified file and maximizes the figure window, which improves resolution when publishing files.
            %
            %--------------------------------------------------------------
            
            if( 0 < exist( imageFileName, 'file' ) )
                imageFigureHandle = figure;
                
                imageScreenshot = ...
                    imread( imageFileName );
                
                imagesc( imageScreenshot);
                pause( 0.01 );
                
                % This involves an unpublished API that I got from a guy
                % who knows things. Do not give this to customers.
                warning( 'off', 'MATLAB:HandleGraphics:ObsoletedProperty:JavaFrame' );
                imageJavaFrame = get( imageFigureHandle, 'javaframe' );
                
                set( imageJavaFrame, 'maximized', 1 );
                warning( 'on', 'MATLAB:HandleGraphics:ObsoletedProperty:JavaFrame' );
                
                axis off;
                axis image;
                hold off;
                
                %% TODO: We need to find a way to close the figures, but doing so early prevents them from appearing in the outpuf file.
                %pause( 0.01 );
                %close( imageFigureHandle );
            else
                errorMessage = ...
                    [ ...
                    'The specified image file, "', ...
                    imageFileName, ...
                    '" does not exist.' ...
                    ];
                error( errorMessage );
            end
            
            
            return;
        end
        
        function [ isUnderVersionControl ] = isPartOfProject( fileOrDirectoryWithAbsolutePath )
            %% isPartOfProject: Returns "true" if the specified file or directory is part of the ET Robocon project, "false" if it is not, and errors for non-existant files or directories.
            %
            %==============================================================
            
            isDirectory = ...
                ( 0 < exist( fileOrDirectoryWithAbsolutePath, 'dir' ) );
            
            % At the OS level, the "svn info" command succeeds or fails
            % depending on whether the file or folder is under revision
            % control, and this function bases its results on that command.
            
            % "exist( ..., 'file' )" seems to return "true" for "@" folders
            % of classes as well, so we'll check directories first.
            
            if( true == isDirectory )
                [ parentDirectory, directoryShortName ] = ...
                    fileparts( fileOrDirectoryWithAbsolutePath );
                
                systemCallCommandString = ...
                    [ ...
                    ETRoboconUtilities.SVN_INFO_COMMAND_STRING, ...
                    ' ', ...
                    directoryShortName ...
                    ];
            else
                isFile = ...
                    ( 0 < exist( fileOrDirectoryWithAbsolutePath, 'file' ) );
                
                if( true == isFile )
                    [ ...
                        parentDirectory, ...
                        fileNameString, ...
                        fileExtensionString ...
                        ] = ...
                        fileparts( fileOrDirectoryWithAbsolutePath );
                    
                    systemCallCommandString = ...
                        [ ...
                        ETRoboconUtilities.SVN_INFO_COMMAND_STRING, ...
                        ' ', ...
                        fileNameString, ...
                        fileExtensionString ...
                        ];
                    
                else
                    errorMessage = ...
                        [ ...
                        '"', ...
                        fileOrDirectoryWithAbsolutePath, ...
                        '" is neither a directory nor a file.' ...
                        ];
                    error( errorMessage );
                end
            end
            
            systemCallResult = ...
                ETRoboconUtilities.cdSystem( parentDirectory, systemCallCommandString );
            
            % In the operating system context, "0" indicates success.
            if( 0 == systemCallResult )
                isUnderVersionControl = true;
            else
                isUnderVersionControl = false;
            end
            
            return;
        end
        
        function [ ] = projectStartUp( )
            %% [ ] = projectStartUp( ): Sets up the ET Robocon environment.
            % Set-currently includes the following tasks:
            %
            % * Confirms that the correct version of MATLAB is being used
            % * Enables the data dictionary feature
            % * Assigning the generated code directory
            % * Assigning the simulation cache folder
            % * Setting up the path
            % * Refreshing customizations
            % * Creating data in the base workspace
            % * Sets the current directory to be the "work_area" folder
            %--------------------------------------------------------------
            
            ETRoboconUtilities.addProjectPaths( );
            
            ETRoboconUtilities.confirmMATLABVersion( );
            
            ETRoboconUtilities.confirmROTHInstallation( );
                     
            ETRoboconUtilities.setCodeGenerationDirectory( );
            
            ETRoboconUtilities.setSimulationCacheDirectory( );
            
            sl_refresh_customizations( );
            
            workAreaAbsolutePath = ...
                ETRoboconUtilities.getWorkAreaAbsolutePath( );
            
            cd( workAreaAbsolutePath );
            
            return;
        end
        
        function [ ] = projectShutDown( )
            %% [ ] = projectShutDown( ): Removes the paths that were added during the start-up script.
            %
            %
            %--------------------------------------------------------------
            ETRoboconUtilities.restoreCodeGenerationDirectory( );
            
            ETRoboconUtilities.restoreSimulationCacheDirectory( );
            
            ETRoboconUtilities.removeProjectPaths( );
            
            return;
        end
        
        function [ ] = refreshProjectPaths( )
            %% [ ] = refreshProjectPaths( ): Undoes, and then redoes the path set up for the project.
            %
            %--------------------------------------------------------------
            warning( 'This does not work right, yet. Clearing out the paths takes away functions needed by "addProjectPaths".' );
            ETRoboconUtilities.removeProjectPaths( );
            ETRoboconUtilities.addProjectPaths( );
            
            return;
        end
        
        function [ ] = removeProjectPreferences( )
            %% [ ] = removeProjectPreferences( ): removes any prefdir entries made by the ET Robocon project.
            %
            %--------------------------------------------------------------
            
            preferenceNamesCellStr = ...
                { ...
                ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING, ...
                ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING ...
                };
            
            preferenceQuantity = numel( preferenceNamesCellStr );
            
            for preferenceIndex = 1 : preferenceQuantity
                
                currentPreference = ...
                    preferenceNamesCellStr{ preferenceIndex };
                
                if( true == ispref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, currentPreference ) )
                    rmpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, currentPreference );
                else
                    warningMessage = ...
                        [ ...
                        'The "', ...
                        ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ...
                        '" group''s "', ...
                        currentPreference, ...
                        '" preference has not been set.' ...
                        ];
                    warning( warningMessage );
                end
            end
            
            return;
        end
        
        
    end
    
    %% Private, static, sealed methods:
    %======================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = private,   ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        
        function [ ] = addProjectPaths( )
            %% [ ] = addProjectPaths( ): Adds paths for the project.
            %
            %--------------------------------------------------------------
            pathsToAddCellStr = ...
                ETRoboconUtilities.getETRoboconProjectPathCellStr( );
            
            cellfun( @addpath, pathsToAddCellStr );
            return;
        end
        
        function [ commandStatus, commandOutputString ] = cdSystem( commandExecutionDirectory, commandStringToExecute, varargin )
            %% cdSystem: changes to the specified directory, executes the "system" command, and then returns to the original directory.
            % Variable arguments: To replicate the original "system"
            % command, users can optionally pass the string '-echo' to the
            % "system" command for output to be displayed.
            %
            %==============================================================
            assert( ( 0 < exist( commandExecutionDirectory, 'dir' ) ), ...
                [ 'The specified directory, "', commandExecutionDirectory, '" does not exist.' ] );
            
            originalDirectory = pwd;
            
            if( true == ETRoboconUtilities.CD_SYSTEM_FUNCTION_DEBUG_ENABLED )
                disp( '"cdSystem" debug mode output:' );
                
                disp( 'Command execution directory:' );
                disp( commandExecutionDirectory );
                
                disp( 'Command string to execute:' );
                disp( commandStringToExecute );
                
                commandStatus = 0;
                commandOutputString = '';
            else
                cd( commandExecutionDirectory );
                
                try
                    switch( nargin )
                        case 2
                            [ commandStatus, commandOutputString ] = ...
                                system( commandStringToExecute );
                        case 3
                            
                            if( true == strcmp( '-echo', varargin{ 1 } ) )
                                [ commandStatus, commandOutputString ] = ...
                                    system( commandStringToExecute, '-echo' );
                            else
                                error( '''-echo'' is the only valid optional argument.' );
                            end
                        otherwise
                            error( 'Invalid argument quantity.' );
                    end
                    
                catch systemCommandException
                    % This will get re-thrown after we switch back to the
                    % original directory.
                end
                
                cd( originalDirectory );
                
                if( 0 < exist( 'systemCommandException', 'var' ) )
                    rethrow( systemCommandException );
                else
                    % There were no exceptions thrown in the first place.
                end
            end
            return;
        end
        
        function [ ] = confirmMATLABVersion( )
            %% [ ] = confirmMATLABVersion( ): confirms that only a valid version of MATLAB is being used.
            %
            %==============================================================
            
            versionString = version( '-release' );
            switch( versionString )
                case { '2014b' }
                    % Everything is cool.
                otherwise
                    % Strengthen to "error" eventually.
                    warning( 'The current version is NOT supported. Use R2014b' );
            end
            return;
        end
        
        function [ ] = confirmROTHInstallation( )
            %% [ ] = confirmROTHInstallation( ): confirms that users have the "run on target hardware" packages installed.
            %
            %--------------------------------------------------------------
            if( true == ispc() )
                
                % This section might not be 100% correct. We haven't been
                % able to test how this works when there is more than one
                % target support package installed.
                hardwareInstallerObject = ...
                    hwconnectinstaller.PackageInstaller;
                
                installedPackages = ...
                    hardwareInstallerObject.getInstalledPackages( );
                
                if( true == isempty( installedPackages ) )
                    warning( 'The Lego Mindstoms "Run On Target Hardware" packages are not installed. Please open Simulink and install them by selecting "Tools"->"Run on Target Hardware"->"Install/Update support package".' );
                else
                    listOfAllInstalledPackages = {installedPackages.FullName}';
                    
                    legoMindstormsPackageIsInstalled = ...
                        any(strmatch('Simulink Support Package for LEGO MINDSTORMS NXT Hardware', listOfAllInstalledPackages, 'exact' ));
                    
                    
                    if( true == legoMindstormsPackageIsInstalled )
                        % Everything is fine.
                    else
                        warning( 'The Lego Mindstoms "Run On Target Hardware" packages are not installed. Please open Simulink and install them by selecting "Tools"->"Run on Target Hardware"->"Install/Update support package".' );
                    end
                    
                end
            else
                warning( 'The "Run On Target Hardware" packages are only available on Windows.' );
            end
            return;
        end
        
        
        function [ ] = generateRepositoryInstructions( )
            %% [ ] = generateRepositoryInstructions( ): Generates the HTML documentation for the repository instructions both as a PDF for distribution before people check out the repository, and as HTML for hyperlinking from inside the repository.
            %
            %--------------------------------------------------------------
            
            repositoryInstructionsSourceFile = ...
                fullfile( ETRoboconUtilities.getProjectDocumentationRoot( ), 'repository_instructions', 'source_files', 'repository_instructions.m' );
            
            repositoryInstructionsOutputDirectory = ...
                fullfile( ETRoboconUtilities.getProjectDocumentationRoot( ), 'repository_instructions' );
            
            publish( repositoryInstructionsSourceFile, ...
                'format', 'pdf', ...
                'showCode', false, ...
                'outputDir', repositoryInstructionsOutputDirectory ...
                );
            
            publish( repositoryInstructionsSourceFile, ...
                'format', 'html', ...
                'showCode', false, ...
                'outputDir', repositoryInstructionsOutputDirectory ...
                );
            
            return;
        end
        
        function [ pathsToAddCellStr ] = getETRoboconProjectPathCellStr( )
            %% [ pathsToAddCellStr ] = getETRoboconPaths( ): Returns a cell array of strings of all of the paths to be added for the project.
            %
            %--------------------------------------------------------------
            pathsToAddCellStr = ...
                ETRoboconUtilities.LEAF_NODE_PATHS_TO_ADD_CELLSTR;
            
            recursivePathRootQuantity = ...
                numel( ETRoboconUtilities.PATH_ROOTS_TO_ADD_RECURSIVELY_CELLSTR );
            
            for recursivePathRootIndex = 1 : recursivePathRootQuantity
                currentPathRoot = ...
                    ETRoboconUtilities.PATH_ROOTS_TO_ADD_RECURSIVELY_CELLSTR{ recursivePathRootIndex };
                
                currentPathRootRecursiveListingCellStr = ...
                    FileSystemUtilities.filteredGenPath( ...
                    'RootDirectory', currentPathRoot, ...
                    'ExactDirectoriesToExclude', { 'html' }, ...
                    'RegularExpressionDirectoriesToExclude', { ETRoboconUtilities.SUBVERSION_DIRECTORY_REGEX, FileSystemUtilities.SLPRJ_DIRECTORY_REGEX }, ...
                    'ReturnCellArray', true );
                
                pathsToAddCellStr = ...
                    [ ...
                    pathsToAddCellStr; ...
                    currentPathRootRecursiveListingCellStr ...
                    ]; %#ok<AGROW> We can't anticipate the number of paths to be added, so we can't pre-allocated it.
            end
            return;
        end
        
        function [ ] = removeProjectPaths( )
            %% [ ] = removeProjectPaths( ): Removes paths added by the project.
            %
            %--------------------------------------------------------------
            
            % It may be necessary to disable the warnings associated with
            % removing directories that were never on the path to begin
            % with. It is possible that a new directory could be created
            % within the recursively searched paths after its parent has
            % been added to the path.
            % 
            % Such a directory would be detected as one having been added,
            % despite the fact that it wasn't.
            %
            pathsToRemoveCellStr = ...
                ETRoboconUtilities.getETRoboconProjectPathCellStr( );
            
            cellfun( @rmpath, pathsToRemoveCellStr );
            return;
        end
        
        function [ ] = restoreCodeGenerationDirectory( )
            %% [ ] = restoreCodeGenerationDirectory( ): restores the code-generation directory to that which was stored in the preferences.
            %
            %--------------------------------------------------------------
            assert( true == ispref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING ), ...
                'There is no code-generation directory stored in the user preferences.' );
            
            originalCodeGenerationDirectory = ...
                getpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING );
            
            Simulink.fileGenControl( 'set', 'CodeGenFolder', originalCodeGenerationDirectory );
            return;
        end
        
        function [ ] = restoreSimulationCacheDirectory( )
            %% [ ] = restoreSimulationCacheDirectory( ): restores the simulation cache directory to that which was stored in the preferences.
            %
            %--------------------------------------------------------------
            assert( true == ispref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING ), ...
                'There is no code-generation directory stored in the user preferences.' );
            
            originalSimulationCacheDirectory = ...
                getpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING );
            
            Simulink.fileGenControl( 'set', 'CodeGenFolder', originalSimulationCacheDirectory );
            
            return;
        end
        
        function [ ] = setCodeGenerationDirectory( )
            %% [ ] = setCodeGenerationDirectory( ): sets the user's code-generation directory to the project-specific directory and stores the original directory in the user's preferences.
            %
            %--------------------------------------------------------------
            codeGenerationDirectoryAbsolutePath = ...
                ETRoboconUtilities.getProjectCodeGenerationDirectoryAbsolutePath( );
            
            assert( ( 0 < exist( codeGenerationDirectoryAbsolutePath, 'dir' ) ), ...
                [ '"', codeGenerationDirectoryAbsolutePath, '" does not exist and cannot be set as the code-generation folder.' ] );
            
            originalCodeGenerationDirectory = ...
                Simulink.fileGenControl( 'get', 'CodeGenFolder' );
            
            if( true == ispref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING ) )
                setpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING, originalCodeGenerationDirectory );
            else
                addpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_CODE_GENERATION_DIRECTORY_PREFERENCE_STRING, originalCodeGenerationDirectory );
            end
            
            Simulink.fileGenControl( 'set', 'CodeGenFolder', codeGenerationDirectoryAbsolutePath );
            
            return;
        end
        
        function [ ] = setSimulationCacheDirectory( )
            %% [ ] = setSimulationCacheDirectory( ): sets the user's simulation cache directory to the project-specific directory and stores the original directory in the user's preferences.
            %
            %--------------------------------------------------------------
            
            simulationCacheDirectoryAbsolutePath = ...
                ETRoboconUtilities.getProjectSimulationCacheDirectoryAbsolutePath( );
            
            assert( ( 0 < exist( simulationCacheDirectoryAbsolutePath, 'dir' ) ), ...
                [ '"', simulationCacheDirectoryAbsolutePath, '" does not exist and cannot be set as the simulation cache folder.' ] );
            
            originalSimulationCacheDirectory = ...
                Simulink.fileGenControl( 'get', 'CacheFolder' );
            
            if( true == ispref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING ) )
                setpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING, originalSimulationCacheDirectory );
            else
                addpref( ETRoboconUtilities.PREFERENCES_GROUP_NAME_STRING, ETRoboconUtilities.ORIGINAL_SIMULATION_CACHE_DIRECTORY_PREFERENCE_STRING, originalSimulationCacheDirectory );
            end
            
            Simulink.fileGenControl('set', 'CacheFolder', simulationCacheDirectoryAbsolutePath );
            return;
        end
        
    end
    
    
end

