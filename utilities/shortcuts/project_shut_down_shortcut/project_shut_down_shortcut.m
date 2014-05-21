function [ ] = project_shut_down_shortcut( )
%% project_shut_down_shortcut:  This is a wrapper function around "ETRoboconUtilities.projectShutDown( )" since class methods (even "static" ones) can't be Simulink Project shortcuts.
%
%==========================================================================

ETRoboconUtilities.projectShutDown( );

return;
end


