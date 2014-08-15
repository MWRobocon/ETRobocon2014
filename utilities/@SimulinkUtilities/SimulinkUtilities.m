classdef ( ...
        Hidden = false,          ... % = [false]|true
        InferiorClasses = {},    ... % = {}
        ConstructOnLoad = false, ... % = [false]|true
        Sealed = false           ... % = [false]|true
        ) ...
        SimulinkUtilities
    %% SimulinkUtilities: This is a collection of utilities that for working with Simulink.
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
    
    %% Private, constant properties:
    %======================================================================
    properties( ...
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
        
        BLOCK_LEFT_EDGE_POSITION_VECTOR_INDEX   = 1;
        BLOCK_RIGHT_EDGE_POSITION_VECTOR_INDEX  = 3;
        BLOCK_TOP_EDGE_POSITION_VECTOR_INDEX    = 2;
        BLOCK_BOTTOM_EDGE_POSITION_VECTOR_INDEX = 4;
        
    end
    
    %% Public, static methods:
    %  ====================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = public,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )
        
        function [ ] = assignBlockAnnotationToReflectDeviantParameters( targetBlockNameOrHandle )
            %% assignBlockAnnotationToReflectDeviantParameters: Assigns an annotation to the block that indicates all non-default parameters.
            %--------------------------------------------------------------
            
            [ deviantBlockParameterNamesCellStr, deviantBlockParameterQuantity ] = ...
                SimulinkUtilities.getDeviantBlockParameters( targetBlockNameOrHandle );
            
            newlineCharacter = sprintf( '\n' );
            
            originalBlockAnnotationString = ...
                get_param( targetBlockNameOrHandle, 'AttributesFormatString' );
            
            if( true == isempty( originalBlockAnnotationString ) )
                % No need to warn.
            else
                warningMessage = ...
                    [ ...
                    'The block annotation for "', ...
                    targetBlockNameOrHandle, ...
                    '" is being overwritten.' ...
                    ];
                warning( warningMessage );
            end
            
            newAnnotationTextString = '';
            
            for deviantBlockParameterIndex = 1 : deviantBlockParameterQuantity
                
                currentParameterName = ...
                    deviantBlockParameterNamesCellStr{ deviantBlockParameterIndex };
                
                newAnnotationTextString = ...
                    [ ...
                    newAnnotationTextString, ...
                    currentParameterName, ...
                    ': %<', ...
                    currentParameterName, ...
                    '>', ...
                    ]; %#ok<AGROW> We don't know how long the string will be.
                
                if( deviantBlockParameterIndex == deviantBlockParameterQuantity )
                    % This is the last entry, so there is no need to add a carriage
                    % return.
                else
                    newAnnotationTextString = ...
                        [ ...
                        newAnnotationTextString, ...
                        newlineCharacter, ...
                        ]; %#ok<AGROW> We don't know how long the string will be.
                end
                
                set_param( targetBlockNameOrHandle, 'AttributesFormatString', newAnnotationTextString );
            end
            
            return;
        end
        
        function [ siblinghood ] = blocksAreSiblings( systemANameOrHandle, systemBNameOrHandle )
            %% blockAreSiblings: returns true if the two specified systems share a common immediate parent.
            %
            %--------------------------------------------------------------
            systemAParent = get_param( systemANameOrHandle, 'Parent' );
            systemBParent = get_param( systemBNameOrHandle, 'Parent' );
            
            siblinghood = ...
                strcmp( systemAParent, systemBParent );
            return;
        end
        
        function [ relatedBlocks ] = findCorrespondingBlocks( systemNameOrHandle )
            %% findCorrespondingBlocks: returns the associated blocks for the selected block.
            % For Data Store-related blocks, this returns all associated Data
            % Store Read, Write, and Memory blocks. For Goto, From, and
            % GotoTagVisibility blocks, it reaturns all Goto, From, and
            % GotoTagVisibility blocks within the appropriate scope.
            %--------------------------------------------------------------
            
            relatedBlocks = {};
            
            selectedSystemType = ...
                get_param( systemNameOrHandle, 'BlockType' );
            
            switch( selectedSystemType )
                case { 'DataStoreMemory', 'DataStoreRead', 'DataStoreWrite' }
                    searchRootSystemNameOrHandle = ...
                        bdroot( systemNameOrHandle );
                    searchDepth = [];
                    targetBlockTypeCellArray = ...
                        { 'DataStoreMemory', 'DataStoreRead', 'DataStoreWrite' };
                    targetPropertyName = 'DataStoreName';
                    
                case 'Goto'
                    [ searchRootSystemNameOrHandle, searchDepth ] = ...
                        SimulinkUtilities.getGotoScopeAndSearchDepth( systemNameOrHandle );
                    targetBlockTypeCellArray = ...
                        { 'Goto', 'GotoTagVisibility', 'From' };
                    targetPropertyName = 'GotoTag';
                    
                case 'GotoTagVisibility'
                    searchRootSystemNameOrHandle = ...
                        get_param( systemNameOrHandle, 'Parent' );
                    searchDepth = [];
                    targetBlockTypeCellArray = ...
                        { 'Goto', 'GotoTagVisibility', 'From' };
                    
                    targetPropertyName = 'GotoTag';
                    
                case 'From'
                    [ searchRootSystemNameOrHandle, searchDepth ] = ...
                        SimulinkUtilities.getFromScopeAndSearchDepth( systemNameOrHandle );
                    targetBlockTypeCellArray = ...
                        { 'Goto', 'GotoTagVisibility', 'From' };
                    targetPropertyName = 'GotoTag';
                    
                otherwise
                    errorMessage = ...
                        [ ...
                        '"', ...
                        systemNameOrHandle, ...
                        '" has a block type of "', ...
                        '", but the only supported types are "Goto", "GotoTagVisibility", "From", "DataStoreMemory", "DataStoreRead", and "DataStoreWrite".' ...
                        ];
                    error( errorMessage );
            end
            
            targetPropertyValue = ...
                get_param( systemNameOrHandle, targetPropertyName );
            
            relatedBlockTypeQuantity = numel( targetBlockTypeCellArray );
            
            for blockTypeIndex = 1 : relatedBlockTypeQuantity
                
                currentBlockType = targetBlockTypeCellArray{ blockTypeIndex };
                
                if( isempty( searchDepth ) == true )
                    currentlyRelatedBlocks = ...
                        find_system( searchRootSystemNameOrHandle, ...
                        'LookUnderMasks',     'all', ...
                        'FollowLinks',        'on', ...
                        'BlockType',          currentBlockType, ...
                        targetPropertyName, targetPropertyValue );
                else
                    currentlyRelatedBlocks = ...
                        find_system( searchRootSystemNameOrHandle, ...
                        'SearchDepth', searchDepth, ...
                        'LookUnderMasks', 'all', ...
                        'FollowLinks',    'on', ...
                        'BlockType',      currentBlockType, ...
                        targetPropertyName,    targetPropertyValue );
                end
                relatedBlocks = ...
                    [ relatedBlocks; currentlyRelatedBlocks ]; %#ok<AGROW>
            end
            
            return;
        end
        
        function [ blockHeight ] = getBlockHeight( blockNameOrHandle )
            %% getBlockHeight: returns the width of the specified block.
            %
            %--------------------------------------------------------------
            
            blockPositionVector = ...
                get_param( blockNameOrHandle, 'Position' );
            
            blockHeight = ...
                blockPositionVector( SimulinkUtilities.BLOCK_BOTTOM_EDGE_POSITION_VECTOR_INDEX ) - ...
                blockPositionVector( SimulinkUtilities.BLOCK_TOP_EDGE_POSITION_VECTOR_INDEX );
            
            return;
        end
        
        function [ blockWidth ] = getBlockWidth( blockNameOrHandle )
            %% getBlockWidth: returns the width of the specified block.
            %
            %--------------------------------------------------------------
            blockPositionVector = ...
                get_param( blockNameOrHandle, 'Position' );
            
            blockWidth = ...
                blockPositionVector( SimulinkUtilities.BLOCK_RIGHT_EDGE_POSITION_VECTOR_INDEX ) - ...
                blockPositionVector( SimulinkUtilities.BLOCK_LEFT_EDGE_POSITION_VECTOR_INDEX );
            
            return;
        end

        function [ paternity ] = isAncestor( suspectedAncestorNameOrHandle, childInQuestionNameOrHandle )
            %% isAncestor: Returns true if the "suspectedAncestorNameOrHandle" is a parent system of "childInQuestionNameOrHandle", and false otherwise.
            %--------------------------------------------------------------
            
            suspectedAncestorFullPathString = ...
                [ ...
                get_param( suspectedAncestorNameOrHandle, 'Parent' ), ...
                '/', ...
                get_param( suspectedAncestorNameOrHandle, 'Name' ), ...
                ];
            
            systemHierarchyIterator = ...
                [ ...
                get_param( childInQuestionNameOrHandle, 'Parent' ), ...
                '/', ...
                get_param( childInQuestionNameOrHandle, 'Name' ), ...
                ];
            
            systemRoot = bdroot( childInQuestionNameOrHandle );
            
            paternity = ...
                strcmp( systemHierarchyIterator, suspectedAncestorFullPathString );
            
            hierarchyExhausted = ....
                strcmp( systemHierarchyIterator, systemRoot );
            
            while( ( hierarchyExhausted == false ) && ( paternity == false ) )
                
                paternity = ...
                    strcmp( systemHierarchyIterator, suspectedAncestorFullPathString );
                
                if( paternity == true )
                    break;
                else
                    systemHierarchyIterator = ...
                        get_param( systemHierarchyIterator, 'Parent' );
                    
                    hierarchyExhausted = ....
                        strcmp( systemHierarchyIterator, systemRoot );
                end
                
            end
            
            return;
        end
                
        function [ propertyAssignmentSuccess ] = setBlockHeight( blockNameOrHandle, proposedHeight )
            %% setBlockHeight: assigns a new width for the block.
            %
            %--------------------------------------------------------------
            
            assert( ( ( 0 < proposedHeight ) && ( proposedHeight == floor( proposedHeight ) ) ), ...
                'The proposed height must be a positive integer.' );
            
            blockPositionVector = ...
                get_param( blockNameOrHandle, 'Position' );
            
            blockPositionVector( SimulinkUtilities.BLOCK_BOTTOM_EDGE_POSITION_VECTOR_INDEX ) = ...
                blockPositionVector( SimulinkUtilities.BLOCK_TOP_EDGE_POSITION_VECTOR_INDEX ) + ...
                proposedHeight;
            
            set_param( blockNameOrHandle, 'Position', blockPositionVector );
            
            propertyAssignmentSuccess = true;
            return;
        end
        
        function [ propertyAssignmentSuccess ] = setBlockWidth( blockNameOrHandle, proposedWidth )
            %% setBlockWidth: assigns a new width for the block.
            %
            %--------------------------------------------------------------
            
            assert( ( ( 0 < proposedWidth ) && ( proposedWidth == floor( proposedWidth ) ) ), ...
                'The proposed height must be a positive integer.' );
            
            blockPositionVector = ...
                get_param( blockNameOrHandle, 'Position' );
            
            blockPositionVector( SimulinkUtilities.BLOCK_RIGHT_EDGE_POSITION_VECTOR_INDEX ) = ...
                blockPositionVector( SimulinkUtilities.BLOCK_LEFT_EDGE_POSITION_VECTOR_INDEX ) + ...
                proposedWidth;
            
            set_param( blockNameOrHandle, 'Position', blockPositionVector );
            
            propertyAssignmentSuccess = true;
            return;
        end
        
    end
    
    %% Private, static methods:
    %  ====================================================================
    methods( ...
            Abstract = false,     ... % = [false]|true
            Access   = private,    ... % = [public]|protected|private
            Hidden   = false,     ... % = [false]|true
            Static   = true,      ... % = [false]|true
            Sealed   = true       ... % = [false]|true
            )

        function [ defaultParameterSettingsMap ] = getDefaultBlockTypeParameterSettings( blockTypeString )
            %% getDefaultBlockTypeParameterSettings: Returns a containers.Map of the default parameters and their values for the specified  block type.
            %--------------------------------------------------------------
            
            % The contents of the library versions of the block shouldn't
            % change very often. Therefore, it makes sense to cache the
            % results of previous searches:
            persistent previousResultsCacheMap;
            
            if( true == isempty( previousResultsCacheMap ) )
                previousResultsCacheMap = containers.Map( );
            else
                % The variable has already been initialized.
            end
            
            if( true == previousResultsCacheMap.isKey( blockTypeString) )
                defaultParameterSettingsMap = ...
                    previousResultsCacheMap( blockTypeString );
            else
                % This particular type of block hasn't been searched for,
                % so proceed with the regular search:
                
                % If the Simulink library browser isn't open, we should
                % open it:
                loadedModelsCellStr = find_system('type', 'block_diagram');
                
                libraryBrowserWasOriginallyLoaded = ...
                    any( strcmp( 'simulink', loadedModelsCellStr ) );
                
                if( true == libraryBrowserWasOriginallyLoaded )
                    % Then we don't need to load it.
                else
                    load_system( 'simulink' );
                end
                
                matchingLibraryBlocksCellStr = ...
                    find_system( 'simulink', 'BlockType', blockTypeString );
                
                matchingLibraryBlockQuantity = numel( matchingLibraryBlocksCellStr );
                
                assert( ( 0 <  matchingLibraryBlockQuantity ), ...
                    [ '"', blockTypeString, '" is not a valid block type argument.'] );
                
                defaultParameterSettingsMap = containers.Map();
                
                % For now, we'll arbitrarily pick the first match, but
                % there is generally more than one match:
                libraryBlockInstance = matchingLibraryBlocksCellStr{ 1 };
                
                dialogParametersStructure = ...
                    get_param( libraryBlockInstance, 'DialogParameters' );
                
                blockParameterNamesCellStr = ...
                    fieldnames( dialogParametersStructure );
                
                blockParameterQuantity = ...
                    numel( blockParameterNamesCellStr );
                
                for blockParameterIndex = 1 : blockParameterQuantity
                    currentParameterName = ...
                        blockParameterNamesCellStr{ blockParameterIndex };
                    
                    currentParameterValue = ...
                        get_param( libraryBlockInstance, currentParameterName );
                    
                    defaultParameterSettingsMap( currentParameterName ) = ...
                        currentParameterValue;
                end
                
                % Leave the Simulink library open if it was already opened
                % when the search started:
                if( true == libraryBrowserWasOriginallyLoaded )
                    % The leave the library browser open.
                else
                    bdclose( 'simulink' );
                end
                
                previousResultsCacheMap( blockTypeString ) = ...
                    defaultParameterSettingsMap;
                
            end
            return;
            
        end
        
        function [ deviantBlockParameterNamesCellStr, deviantBlockParameterQuantity ] = getDeviantBlockParameters( targetBlockNameOrHandle )
            %% getDeviantBlockParameters: Returns the names of all parameters whose values differ from those in the Simulink library.
            %--------------------------------------------------------------                   
            
            deviantBlockParameterNamesCellStr  = { };
            deviantBlockParameterQuantity      = 0;
            
            targetBlockTypeString = get_param( targetBlockNameOrHandle, 'BlockType' );
            
            defaultParameterSettingsMap = ...
                SimulinkUtilities.getDefaultBlockTypeParameterSettings( targetBlockTypeString );
            
            blockParameterNamesCellStr = ...
                defaultParameterSettingsMap.keys( );
            
            blockParameterQuantity = numel( blockParameterNamesCellStr );
            
            for blockParameterIndex = 1 : blockParameterQuantity
                
                currentBlockParameterName = ...
                    blockParameterNamesCellStr{ blockParameterIndex };
                
                targetBlockParameterValue = ...
                    get_param( targetBlockNameOrHandle, currentBlockParameterName );
                
                if( true == ischar( targetBlockParameterValue ) )
                    
                    targetBlockParameterValueMatches = ...
                        strcmp( targetBlockParameterValue, defaultParameterSettingsMap( currentBlockParameterName ) );
                    
                    if( true == targetBlockParameterValueMatches )
                        % Skip it.
                    else
                        deviantBlockParameterNamesCellStr{ end + 1 } = ...
                            currentBlockParameterName; %#ok<AGROW> We can't predict how many parameters will or won't match.
                        
                        deviantBlockParameterQuantity = ...
                            deviantBlockParameterQuantity + 1;
                    end
                else
                    warningMessage = ...
                        [ ...
                        'Skipping  parameter "', ....
                        currentBlockParameterName, ...
                        '" because it is not a string.' ...
                        ];
                    warning( warningMessage );
                end
            end
            
            return;
        end        

        function [ scopeRootSystemNameOrHandle, searchDepth ] = getFromScopeAndSearchDepth( fromBlockNameOrHandle )
            %% get_from_scope_and_search_depth: Returns the system at the root of the From block's scope and the corresponding search depth for associated blocks (empty for unbounded depth).
            % If the From block lacks a corresponding Goto, or if the
            % corresponding Goto is scoped and lacks a corresponding
            % GotoTagVisibility block, the function returns the From
            % block's parent as the search root and a search depth of 1. 
            %--------------------------------------------------------------
            
            scopeRootSystemNameOrHandle = [];
            searchDepth = [];
            
            rootSystemNameOrHandle = ...
                bdroot( fromBlockNameOrHandle );
            
            gotoTag = get_param( fromBlockNameOrHandle, 'GotoTag' );
            
            potentiallyMatchingGotoBlocks = ...
                find_system( rootSystemNameOrHandle, ...
                'LookUnderMasks', 'all', ...
                'FollowLinks',    'on', ...
                'BlockType',      'Goto', ...
                'GotoTag',        gotoTag );
            
            potentiallyMatchingGotoBlockQuantity = ...
                numel( potentiallyMatchingGotoBlocks );
            
            for gotoBlockIndex = 1 : potentiallyMatchingGotoBlockQuantity
                currentGotoBlock = ...
                    potentiallyMatchingGotoBlocks{ gotoBlockIndex };
                
                currentGotoBlockVisibility = ...
                    get_param( currentGotoBlock, 'TagVisibility' );
                
                switch( currentGotoBlockVisibility )
                    case 'local'
                        gotoAndFromSiblinghood = ...
                            SimulinkUtilities.blocksAreSiblings( currentGotoBlock, fromBlockNameOrHandle );
                        if( gotoAndFromSiblinghood == true )
                            scopeRootSystemNameOrHandle = ...
                                get_param( currentGotoBlock, 'Parent' );
                            searchDepth = 1;
                            break;
                        else
                            % Keep searching.
                        end
                    case 'scoped'
                        correspondingGotoVisibilityBlock = ...
                            getGotoCorrespondingGotoVisibilityBlock( currentGotoBlock );
                        if( isempty( correspondingGotoVisibilityBlock ) == true )
                            warningMessage = ...
                                [ ...
                                '"', ...
                                currentGotoBlock, ...
                                '" could be a matching Goto block for "', ...
                                fromBlockNameOrHandle, ...
                                '". However it is scoped and does not have a corresponding "GotoTagVisibility" block.' ...
                                ];
                            warning( warningMessage ); %#ok<WNTAG> I like this style of warning...
                            % Keep searching.
                        else
                            correspondingGotoTagVisibilityScopeRoot = ...
                                get_param( correspondingGotoVisibilityBlock, 'Parent' );
                            
                            fromBlockIsInScope = ...
                                is_ancestor( correspondingGotoTagVisibilityScopeRoot, fromBlockNameOrHandle );
                            
                            if( fromBlockIsInScope == true )
                                scopeRootSystemNameOrHandle = ...
                                    correspondingGotoTagVisibilityScopeRoot;
                                searchDepth = [];
                                break;
                            else
                                % Keep searching.
                            end
                        end
                    case 'global'
                        scopeRootSystemNameOrHandle = ...
                            rootSystemNameOrHandle;
                        searchDepth = [];
                        break;
                    otherwise
                        errorMessage = ...
                            [ ...
                            '"', ...
                            currentGotoBlock, ...
                            '" has an invalid value ("', ...
                            currentGotoBlockVisibility, ...
                            '") for its "TagVisibility" property.' ...
                            ];
                        error( errorMessage );
                end
            end
            
            if( isempty( scopeRootSystemNameOrHandle ) == true )
                warningMessage = ...
                    [ ...
                    '"', ...
                    fromBlockNameOrHandle, ...
                    '" either lacks a corresponding "Goto" block to specify its scope, or the corresponding "Goto" is "scoped", but lacks a corresponding "GotoTagVisibility" block.' ...
                    ];
                warning( warningMessage ); %#ok<WNTAG> I like this style of warning...
                
                scopeRootSystemNameOrHandle = ...
                    get_param( fromBlockNameOrHandle, 'Parent' );
                searchDepth = 1;
            else
                % We found a match already.
            end
            return;
        end
        
        function [ correspondingGotoVisibilityBlock ] = getGotoCorrespondingGotoVisibilityBlock( gotoBlockNameOrHandle )
            %% get_goto_corresponding_goto_visibility_block: returns the GotoVisibility block that corresponds to the specified scoped Goto block.
            % It returns an empty value if there is no GotoVisibility
            % block.
            %--------------------------------------------------------------                   
            
            correspondingGotoVisibilityBlock = [];
            
            rootSystemNameOrHandle = ...
                bdroot( gotoBlockNameOrHandle );
            
            gotoTag = get_param( gotoBlockNameOrHandle, 'GotoTag' );
            
            potentiallyMatchingGotoVisibilityBlocks = ...
                find_system( rootSystemNameOrHandle, ...
                'LookUnderMasks', 'all', ...
                'FollowLinks',    'on', ...
                'BlockType',      'GotoTagVisibility', ...
                'GotoTag',        gotoTag );
            
            potentiallyMatchingGotoVisibilityBlockQuantity = ...
                numel( potentiallyMatchingGotoVisibilityBlocks );
            
            for potentiallyMatchingGotoVisibilityBlockIndex = 1 : potentiallyMatchingGotoVisibilityBlockQuantity
                
                currentGotoVisibilityBlock = ...
                    potentiallyMatchingGotoVisibilityBlocks{ potentiallyMatchingGotoVisibilityBlockIndex };
                
                currentGotoVisibilityBlockScopeRoot = ...
                    get_param( currentGotoVisibilityBlock, 'Parent' );
                
                currentGotoVisibilityBlockIsInScope = ...
                    is_ancestor( currentGotoVisibilityBlockScopeRoot, gotoBlockNameOrHandle );
                
                if( currentGotoVisibilityBlockIsInScope == true )
                    
                    correspondingGotoVisibilityBlock = ...
                        currentGotoVisibilityBlock;
                    
                    break;
                else
                    % Keep searching.
                end
            end
            
            if( isempty( correspondingGotoVisibilityBlock ) == true )
                warningMessage = ...
                    [ ...
                    '"', ...
                    gotoBlockNameOrHandle, ...
                    '" does not have a matching GotoTagVisibility block.' ...
                    ];
                warning( warningMessage ); %#ok<WNTAG> I still like this style of warning...
            else
                % Everything is fine.
            end
            
            return;
        end
           
        function [ scopeRootSystemNameOrHandle, searchDepth ] = getGotoScopeAndSearchDepth( gotoBlockNameOrHandle )
            %% get_goto_scope_and_search_depth: returns the root of the Goto tag's scope and the depth of that scope (which is empty for unbounded searches).
            % If the Goto is scoped, but lacks a corresponding
            % GotoTagVisibility, it returns empty values for both answers. 
            %--------------------------------------------------------------       
            
            gotoVisibility = get_param( gotoBlockNameOrHandle, 'TagVisibility' );
            switch( gotoVisibility )
                case 'global'
                    scopeRootSystemNameOrHandle = ...
                        bdroot( gotoBlockNameOrHandle );
                    searchDepth = [];
                case 'local'
                    scopeRootSystemNameOrHandle = ...
                        get_param( gotoBlockNameOrHandle, 'Parent' );
                    searchDepth = 1;
                case 'scoped'
                    correspondingGotoVisibilityBlock = ...
                        getGotoCorrespondingGotoVisibilityBlock( gotoBlockNameOrHandle );
                    searchDepth = [];
                    if( isempty( correspondingGotoVisibilityBlock ) == true )
                        warningMessage = ...
                            [ ...
                            '"', ...
                            gotoBlockNameOrHandle, ...
                            '" is a scoped Goto block, but does not have a GotoTagVisibility block.' ...
                            ];
                        warning( warningMessage ); %#ok<WNTAG> I still like this style of warning...
                        scopeRootSystemNameOrHandle = [];
                        searchDepth = [];
                    else
                        scopeRootSystemNameOrHandle = ...
                            get_param( correspondingGotoVisibilityBlock, 'Parent' );
                    end
                otherwise
                    errorMessage = ...
                        [ ...
                        gotoBlockNameOrHandle, ...
                        'has an invalid value ("', ...
                        gotoVisibility, ...
                        '")for "TagVisibility". The only valid values are "global", "local", and "scoped".', ...
                        ];
                    error( errorMessage );
            end
            
            return;
        end
       
    end
end