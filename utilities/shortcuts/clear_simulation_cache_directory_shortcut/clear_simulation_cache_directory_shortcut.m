function [ ] = clear_simulation_cache_directory_shortcut( )
%% [ ] = clear_simulation_cache_directory_shortcut( ): This is a wrapper for the "ETRoboconUtilities.clearSimulationCacheDirectory" command.
%
%--------------------------------------------------------------------------

ETRoboconUtilities.clearSimulationCacheDirectory( );
disp('Simulation cache directory cleared');
return;

end

