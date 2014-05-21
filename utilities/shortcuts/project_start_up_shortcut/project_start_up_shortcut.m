function [ ] = project_start_up_shortcut( )
%% project_start_up_shortcut: This is a wrapper function around "ETRoboconUtilities.projectStartUp( )" since class methods (even "static" ones) can't be Simulink Project shortcuts.
%
%==========================================================================

thisFilesFullName = mfilename( 'fullpath' );
thisFilesAbsolutePath = fileparts( thisFilesFullName );

etRoboconUtilitiesDirectoryRelativePath = ...
    fullfile( thisFilesAbsolutePath, '..', '..' );

cd( etRoboconUtilitiesDirectoryRelativePath );

ETRoboconUtilities.projectStartUp( );



return;
end
