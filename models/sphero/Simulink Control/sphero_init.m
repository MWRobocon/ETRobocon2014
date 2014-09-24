function sphero_init(sphOrangeName, sphBlueName)

comms.SpheroStore.forceReset();

%% Connect Orange sphero
sphOrange.Status = 'closed';
count = 0;

while count<5&&~strcmp(sphOrange.Status, 'open')
    try 
        sphOrange = sphero(sphOrangeName);
   
    catch exception
        if strncmp('Sphero', exception.identifier, 6)
            warning(['Orange sphero    ' exception.message]);
            sphOrange.Status = 'closed';
        end
        count = count+1;
    end
end
    
%% Connect Blue Sphero
sphBlue.Status = 'closed';

count = 0;
while count<5&&~strcmp(sphBlue.Status, 'open')
    try 
        sphBlue = sphero(sphBlueName);
   
    catch exception
        if strncmp('Sphero', exception.identifier, 6)
            warning(['Blue sphero    ' exception.message]);
            sphBlue.Status = 'closed';
        end
        count = count+1;
    end
end

%% Add the objects to the SpheroStore

comms.SpheroStore.registerRobot(RobotID.SPHERO_ORANGE, sphOrange);
comms.SpheroStore.registerRobot(RobotID.SPHERO_BLUE, sphBlue);


