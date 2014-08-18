function [ ] = clear_code_generation_directory_shortcut( )
%% [ ] = clear_code_generation_directory_shortcut( ): This is a wrapper for the "ETRoboconUtilities.clearCodeGenerationDirectory" command.
%
%--------------------------------------------------------------------------

ETRoboconUtilities.clearCodeGenerationDirectory( );
disp('Code generation directory cleared');
return;

end

