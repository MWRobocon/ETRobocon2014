classdef BluetoothApi<sphero.internal.Communication
    %BLUETOOTHAPI Summary of this class goes here
    %   Detailed explanation goes here
    
    
    properties(Constant, Access = ?sphero)
        Uint8Max = double(intmax('uint8'));
        SpheroDeviceNameBeg = 'Sphero';
        MaxSensorSampleRate = 400;
    end
    
    properties(Constant, Access = {?BluetoothApi, ?sphero})
        ResponseError = NaN;
        ResponseInitialValue = Inf;
        ResponseEmpty = [];
    end
    
    properties(SetObservable)%, Access = {?BluetoothApi, ?sphero})
        PowerNotification % To Do
        SensorData
        PreSleepWarning % To Do
        CollisionDetected % To Do
        GyroAxisLimitExceed % To Do
        ErrorSynchronous
        ErrorAsynchronous
    end
%     
%      events
%         PowerNotificationChange
%         SensorDataReceived
%         PreSleepWarningReceived
%         CollisionDetected
%         GyroAxisLimitExceeded
%     end
    
    
    properties %(Access = {?BluetoothApi, ?sphero})
        SequenceList%Structure containing the sequence number, action, response
        Rev = '1_50'; %temporarily hard coded. 
        %Should be based on revision of API, as returned by Sphero
        
        DeviceName
        Sequence = uint8(1);
        Handshake = 0;
        ApiInfo;
        Bt;
        Response;
        BytesToRead  =  Inf;
        Sensors;
        SamplesPerPacket;
        SensorDataPropertySet = 0; %Used in the readSensor method of 
        % sphero class, because the callback to SensorData listener cannot
        % be used for 'readSensor' method
    end
    
    methods(Access = private, Static = true)
         function cmd = cmdToByte(cmdIn)
         % cmd = cmdToByte(h, cmdIn)   Convert multiple byte data to array of uint8
            % CMD = cmdToByte(h, CMDIN) converts CMDIN to an array of uint8
            % data. It checks whether the machine is big endian and little
            % endian, and arranges the uint8 data based on that
            
             [~,~,endian] = computer;
               
             if strcmp(endian, 'L')
                   cmd = typecast(swapbytes(cmdIn), 'uint8');
             else
                   cmd = typecast(cmdIn, 'uint8');
             end
        end
        
        function cmd = cmdFromByte(bytedata, varargin)
         %CMDFROMBYTE    Convert 2 byte data to uint16 data 
            % CMDTOBYTE(H, BYTEDATA) converts the data represented by the 
            % BYTEDATA vector (containing Most Significant Bit and Least 
            % Significant Bit) to an uint16 variable. 
            % It checks whether the machine is big endian or little
            % endian, and arranges the data based on that
            % CMDTOBYTE(H, BYTEDATA, DATATYPE) converts the BYTEDATA to 
            % the desired DATATYPE
            if nargin>1
                type = varargin{1};
            else
                type = 'uint16';
            end
                
            [~,~,endian] = computer;
            
            if strcmp(endian, 'L')
                   cmd = swapbytes(typecast(bytedata, type));
            else
                   cmd = typecast(bytedata, type);
            end
        end
               
    end
    
    methods(Access = private)
        
        function devicename = findDevices(obj)
    
                devices = instrhwinfo('Bluetooth');
                checksphero = strncmp(devices.RemoteNames, obj.SpheroDeviceNameBeg, length(obj.SpheroDeviceNameBeg));
                
                spherodevices = devices.RemoteNames(checksphero);
            
                if isempty(spherodevices)
                    error('Sphero:Api:DeviceNotAvailable', 'No Sphero device available. Please make sure your Sphero device is switched on and is in vicinity');
                else
                    choose = 'Choose one of the available Sphero devices: \n '; 
                    for idx=1:length(spherodevices)
                        choose = [choose num2str(idx) '. ' spherodevices{idx} '\n']; %#ok<AGROW>
                    end

                    response = 'n';

                    while(~strcmp(response, 'y'))
                        chosen = input(sprintf(choose));
                        if chosen<=length(spherodevices)
                           recheck = ['Are you sure you would like to connect to ' spherodevices{chosen} ' [y/n] : '];
                            response = input(recheck, 's');
                        else
                            error('Sphero:Api:SelectValidDevice','Please select one of the available devices')
                        end
                    end

                    devicename = spherodevices{chosen};
                end
        end
        
        function chk = computeCheckSum(obj, cmd)
            chk = bitcmp(mod(sum(cmd(obj.ApiInfo.SpheroResponse.mrsp:end)), obj.Uint8Max+1), 'uint8');
        end
        
        function [did, cid, dlen] = obtainId(obj,action, data)
        %Get the Device ID, Command ID and Data Length of the action to 
        %be performed

            err = MException('Sphero:Api:InvalidParameter', 'Please enter a valid command');

            switch action
                case 'ping'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdPing; dlen = '01';
                case 'version'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdVersion; dlen = '01';
                case 'setbtname'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdSetBtName; dlen = dec2hex(length(data)+1);
                case 'getbtname'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdGetBtName; dlen = '01';
                case 'setautoreconnect'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdSetAutoReconnect; dlen = '03';
                case 'getautoreconnect'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdGetAutoReconnect; dlen = '01';
                case 'getpwrstate'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdGetPwrState; dlen = '01';
                case 'setpwrnotify'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdSetPwrNotify; dlen = '02';
                case 'sleep'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdSleep; dlen = '06';
                case 'getpowertrips'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.GetPowerTrips; dlen = '01';
                case 'setpowertrips'
                    did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.SetPowerTrips; dlen = '05';
                case 'setinactivetimer'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.SetInactiveTimer; dlen = '03';
                case 'gotobl'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.GotoBl; dlen = '01';
                case 'runl2diags'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdRunL2Diags; dlen = '01';
                case 'clearcounters'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdClearCounters; dlen = '01';
                case 'assigntime'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.CmdAssignTime; dlen = '05';
                case 'polltimes'
                     did = obj.ApiInfo.DidCore; cid = obj.ApiInfo.cmdPollTimes; dlen = '05';
%                 case 'runl1diags'
%                 case 'btinfo'
%                     did = 'obj.ApiInfo.DidCore'; cid = '11'; dlen = '01';
                case 'setcal'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetCal; dlen = '03';
                case 'setstabiliz'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetStabiliz; dlen = '02';
                case 'setrotationrate'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetRotationRate; dlen = '02';
                case 'getchassisid'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdGetChassisId; dlen = '01';
                case 'selflevel'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSelfLevel; dlen = '05';
                case 'setdatastreaming'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetDataStreaming; dlen = '0e';
                case 'setcollisiondet'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetCollisionDet; dlen = '07';
                case 'locator'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdLocator; dlen = '08';
                 case 'setaccelero'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetAccelero; dlen = '02';
                case 'readlocator'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdReadLocator; dlen = '01';
                case 'setrgbled'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetRgbLed; dlen = '05';
                case 'setbackled'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetBackLed; dlen = '02';
                case 'getrgbled'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdGetRgbLed; dlen = '01';
                case 'roll'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdRoll; dlen = '05';
                case 'boost'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdBoost; dlen = '02';
                case 'setrawmotors'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetRawMotors; dlen = '05';
                case 'setmotionto'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetMotionTo; dlen = '03';
                case 'setdevicemode'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdSetDeviceMode; dlen = '02';
                case 'getdevicemode'
                    did = obj.ApiInfo.DidSphero; cid = obj.ApiInfo.CmdGetDeviceMode; dlen = '01';
                
                otherwise
                    throw(err);
            end
            
%             did  = uint8(hex2dec(did));
%             cid  = uint8(hex2dec(cid));
            dlen = uint8(hex2dec(dlen));
        end
        
        function validAction = validateAction(~,action)
            validActions = {'ping', 'version', 'controluarttx', 'setbtname',...
                'getbtname', 'setautoreconnect', 'getautoreconnect', ...
                'getpwrstate', 'setpwrnotify', 'sleep', 'getpowertrips', ...
                'setpowertrips', 'setinactivetimer', 'gotobl', ...
                'runl1diags', 'runl2diags', 'clearcounters', 'assigntime', ...
                'polltimes', ...
                'beginreflash', 'hereispage', 'leavebootloader', ...
                'ispageblank', 'eraseuserconfig', ...
                'setcal', 'setstabiliz', 'setrotationrate', ...
                'setcreationdate', 'reenabledemo', 'getchassisid', ...
                'setchassisid', 'selflevel', 'setdatastreaming', ...
                'setcollisiondet', 'locator', 'setaccelero', ...
                'readlocator', 'setrgbled', 'getrgbled', ...
                'setbackled', 'roll', 'boost', 'move', 'setrawmotors', ...
                'setmotionto', 'setoptionsflag', 'getoptionsflag', ...
                'settempoptionsflag', 'gettempoptionsflag', ...
                'getconfigblk', 'setssbparams', 'setdevicemode', ...
                'getssb', 'getdevicemode', 'setssb', 'ssbrefill', 'ssbbuy', ...
                'ssbuseconsumeable', 'ssbgrantcores', 'ssbaddxp', ...
                'ssblevelupattr', 'getpwseed', 'ssbenableasync', ...
                'runmacro', 'savetempmacro', 'savemacro', ...
                'initmacroexecutive', 'abortmacro', 'macrostatus', ...
                'setmacroparam', 'appendtempmacrochunk', ...
                'eraseorbbas', 'appendfrag', 'execorbbas', 'answerinput',...
                'committoflash'};
            
            validAction = validatestring(action, validActions);
                       
        end
        
        function data = formatCommandData(obj, action, varargin)
            
            switch action
                case 'controluarttx'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setbtname'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setpwrnotify'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                    
                case 'sleep'
                    origdata = cell2mat(varargin);
                    data(1:2) = obj.cmdToByte(uint16(origdata(1)));
                    data(3) = uint8(origdata(2));
                     data(4:5) = obj.cmdToByte(uint16(origdata(3)));
                case 'setpowertrips'
                    origdata = cell2mat(varargin);
                    data(1:2) = obj.cmdToByte(uint16(origdata(1)));
                    data(3:4) = obj.cmdToByte(uint16(origdata(2)));
                case 'setinactivetimer'
                    origdata = cell2mat(varargin);
                    data(1:2) = obj.cmdToByte(uint16(origdata(1)));
                case 'setrgbled'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'roll'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = obj.cmdToByte(uint16(origdata(2)));
                    data(4) = uint8(origdata(3));
                case 'setcal'
                    origdata = cell2mat(varargin);
                    data = obj.cmdToByte(uint16(origdata));
                case 'setstabiliz'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setrotationrate'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setaccelero'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setbackled'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                    
                case 'setdatastreaming'
%                     origdata = cell2mat(varargin);
                    data(1:2) = obj.cmdToByte(uint16(varargin{1}));
                    data(3:4) = obj.cmdToByte(uint16(varargin{2}));
                    data(5:8) = obj.cmdToByte(uint32(varargin{3}));
                    data(9) = obj.cmdToByte(uint8(varargin{4}));
                    data(10:13) = obj.cmdToByte(uint32(varargin{5}));
                case 'setcollisiondet'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'locator'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = obj.cmdToByte(int16(origdata(2)));
                    data(4:5) = obj.cmdToByte(int16(origdata(3)));
                    data(6:7) = obj.cmdToByte(int16(origdata(3)));
                case 'boost'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setrawmotors'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setmotionto'
                    origdata = cell2mat(varargin);
                    data(1:2) = obj.cmdToByte(uint16(origdata(1)));
                otherwise
                    data = [];
                    
                    
                
            end
        end
            
        
        function valid = checkValidityResponse(obj, sop1, sop2, msrp, code, dlen, data, chk, response)
           expectedChk = computeCheckSum(obj, response(1:end-1));
%            err = MException('Sphero:Api:InvalidResponse',...
%                'Received response is not valid');
                
           
           if sop1~=obj.ApiInfo.expectedSop1||...
                   (sop2~=obj.ApiInfo.sop2Acknowledgement && sop2~=obj.ApiInfo.sop2Asynchronous)||...
                   dlen~=length(data)+1||chk~=expectedChk
                valid=0;
           elseif sop2 == obj.ApiInfo.sop2Asynchronous
               if code>length(obj.ApiInfo.RspAsync)
                   valid = 0;
               else
                   valid=1;
               end
           else
               valid = checkMsrp(obj, msrp);
           end
            
        end
        
        function valid = checkMsrp(obj, msrp)
            valid = 0;
            switch msrp
                case obj.ApiInfo.RspCodeOk
                    valid = 1;
                
                case obj.ApiInfo.RspCodeEgen
                    err = MException('Sphero:Api:InvalidCommand:GeneralError',...
                        'Unrecognized Message Reponse received. Please check API definition');
                case obj.ApiInfo.RspCodeEchksum
                    err = MException('Sphero:Api:InvalidCommand:ChecksumFailure',...
                        'Command with incorrect checksum value sent. Please check API definition');
                case obj.ApiInfo.RspCodeEfrag
                    err = MException('Sphero:Api:InvalidCommand:CommandFragment',...
                        'Complete command not received. Please check API definition');
                case obj.ApiInfo.RspCodeEbadCmd
                    err = MException('Sphero:Api:InvalidCommand:CommandID',...
                        'Unknown command ID received. Please check API definition');
                case obj.ApiInfo.RspCodeEunsupp
                    err = MException('Sphero:Api:InvalidCommand:CommandUnsupported',...
                        'Command currently unsupported. Please check API definition for current revision');
                case obj.ApiInfo.RspCodeEbadMsg
                    err = MException('Sphero:Api:InvalidCommand:BadMessage',...
                        'Incorrect message format received. Please check API definition');
                case obj.ApiInfo.RspCodeEparam
                    err = MException('Sphero:Api:InvalidCommand:InvalidParameterValues',...
                        'Invalid Parameter Values. Please check API definition');
                case obj.ApiInfo.RspCodeEexec
                    err = MException('Sphero:Api:InvalidCommand:FailedExecution',...
                        'Failed to execute command. Please retry');
                case obj.ApiInfo.RspCodeEbadDid
                     err = MException('Sphero:Api:InvalidCommand:UnknownDeviceID',...
                        'Invalid Device ID. Please check API definition');
                case obj.ApiInfo.RspCodeMemBusy
                     err = MException('Sphero:Api:InvalidCommand:MemBusy',...
                        'RAM is busy. Please retry');
                case obj.ApiInfo.RspCodeBadPassword
                     err = MException('Sphero:Api:InvalidCommand:IncorrectPassword',...
                        'Incorrect Password supplied');
                case obj.ApiInfo.RspCodePowerNogood
                     err = MException('Sphero:Api:InvalidCommand:LowVoltage',...
                        'Voltage too low for reflash operation. Recharge Sphero and try again.');
                case obj.ApiInfo.RspCodePageIllegal
                      err = MException('Sphero:Api:InvalidCommand:IllegalPageNumber',...
                        'Illegal page number provided.');
                case obj.ApiInfo.RspCodeFlashFail
                      err = MException('Sphero:Api:InvalidCommand:FlashFail',...
                        'Page did not reprogram correctly.');
                case obj.ApiInfo.RspCodeMaCorrupt
                     err = MException('Sphero:Api:InvalidCommand:MainApplicationCorrupt',...
                        'Main Application corrupted');
                case obj.ApiInfo.RspCodeMsgTimeout
                      err = MException('Sphero:Api:InvalidCommand:MessageTimeout',...
                        'Message timed out. Please try again.');
                    
                otherwise
%                     valid=0;
                    err = MException('Sphero:Api:InvalidCommand:GeneralError','Unrecognized Message Reponse received. Please check API definition');
                 
            end
            
            if exist('err', 'var')
                obj.ErrorSynchronous = err;
            end
        end
        
       
        
        function [result, out] = decodeResponseData(obj, data, action)
%             err = MException('Sphero:Api:InvalidResponse',...
%                'Received response is not valid');
            
           switch action
                case 'version'
                    if length(data)~= obj.ApiInfo.RspVersionDlen-1
                        result = 0;
                        out = [];
                    else
                        result = 1;
                        
                        recv = data(1); mdl = data(2); hw = data(3); 
                        msaver = data(4); msarev = data(5); 
                        bl = packedNibble2Dec(data(6));
                        bas = packedNibble2Dec(data(7));
                        macro = packedNibble2Dec(data(8));
                        apimaj = data(9); apimin = data(10);
                        
                        version.RecordVersion = recv;
                        version.ModelNumber = mdl;
                        version.HardwareVersion = hw;
                        version.MainSpheroApplicationVersion = msaver;
                        version.MainSpheroApplicationRev = msarev;
                        version.BootloaderVersion = bl;
                        version.OrbBasicVersion = bas;
                        version.MacroExecutiverVersion = macro;
                        version.ApiMajorRev = apimaj;
                        version.ApiMinorRev = apimin;
                        
                        out = version;
%                         if nargout==0
%                             disp(version);
%                       SensorDataPropertySet  else
%                             varargout{1} = version;
%                         end
                    end
               case 'getbtname'
                   if length(data)~= obj.ApiInfo.RspGetBtNameDlen-1
%                         error(err)
                         result = 0;
                        out = [];
                   else
                       result = 1;
                       
                      name = char(data(1:16));
                      address = char(data(17:28));
                      colors = char(data(30:32));
                      
                      out = strvcat(name, address, colors);
%                       varagout{1} = address;
%                       varagout{2} = colors;
                   end
               case 'getautoreconnect' % Not being used in hwinfo now
                   if length(data)~= obj.ApiInfo.RspGetAutoReconnectDlen-1
%                         error(err)
                       result = 0;
                        out = [];
                   else
                       result = 1;
                       out = data;
%                       out           = data(1);
%                       varagout{1}   = data(2);
                   end
               case 'getpwrstate'
                   if length(data)~=obj.ApiInfo.RspGetPwrStateDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       
                       recver       = data(1);
                       powerstate   = data(2);
                       voltage      = obj.cmdFromByte(data(3:4), 'uint16');
                       charges      = obj.cmdFromByte(data(5:6), 'uint16');
                       timeawake    =  obj.cmdFromByte(data(7:8), 'uint16');
                       
                       out = {recver powerstate voltage charges timeawake};
                       
                   end
               case 'getpowertrips'
                   if length(data)~=obj.ApiInfo.RspGetPowerTripsDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out(1) = obj.cmdFromByte(data(1:2), 'uint16');
                       out(2) = obj.cmdFromByte(data(3:4), 'uint16');
                   end
               case 'runl2diags'
                   if length(data)~=obj.ApiInfo.RspRunL2DiagsDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;

                                              
                       out{1} = obj.cmdFromByte(data(1:2), 'uint16');
                       out{2} = obj.cmdFromByte(data(4:7), 'uint32');
                       out{3} = obj.cmdFromByte(data(8:11), 'uint32');
                       out{4} = obj.cmdFromByte(data(12:15), 'uint32');
                       out{5} = obj.cmdFromByte(data(16:19), 'uint32');
                       out{6} = obj.cmdFromByte(data(20:23), 'uint32');
                       out{7} = obj.cmdFromByte(data(24:27), 'uint32');
                       out{8} = obj.cmdFromByte(data(28:31), 'uint32');
                       out{9} = obj.cmdFromByte(data(32:35), 'uint32');
%                        out{10} = data(36);
%                        out{11} = obj.cmdFromByte(data(37:68), 'uint32');
                       out{12} = obj.cmdFromByte(data(71:72), 'uint16');
                       out{13} = obj.cmdFromByte(data(73:74), 'uint16');
                       out{14} = obj.cmdFromByte(data(75:78), 'uint32');
                       out{15} = obj.cmdFromByte(data(79:82), 'uint32');
                       out{16} = obj.cmdFromByte(data(83:84), 'uint16');
                       out{17} = obj.cmdFromByte(data(85:88), 'uint32');
                       
                   end
               case 'getrgbled'
                    if length(data)~= obj.ApiInfo.RspGetRgbLedDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out = data;
                       
                    end
                   
             
               case 'readlocator'
                   if length(data)~= obj.ApiInfo.RspReadLocatorDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       xpos = obj.cmdFromByte(data(1:2), 'int16');
                       ypos = obj.cmdFromByte(data(3:4), 'int16');
                       xvel = obj.cmdFromByte(data(5:6), 'int16');
                       yvel = obj.cmdFromByte(data(7:8), 'int16');
                       sog = obj.cmdFromByte(data(9:10), 'uint16');
                       
                       out = {xpos ypos xvel yvel sog};
                       
                   end
                   
                   
               case 'getdevicemode'
                  if length(data)~= obj.ApiInfo.RspGetDeviceModeDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out = data;
                  end
                  
               case 'power'
                   out = [];
                   if length(data)~=obj.ApiInfo.RspPowerDlen-1
                       result = 0;
                   else
                       result = 1;
                       switch data
                            case 1
                                obj.PowerNotification = 'Charging';
                            case 2
                                obj.PowerNotification = 'Battery OK';
                            case 3
                                obj.PowerNotification = 'Battery Low';
                            case 4
                                obj.PowerNotification = 'Battery Critical';
                           otherwise
                                result = 0;
                        end
                       
                   end
               case 'presleep'
                   out= [];
                   if length(data)~=obj.ApiInfo.RspPreSleepDlen-1
                       result = 0;
                   else
                       obj.PreSleepWarning = 1;
                       result = 1;
                   end
                   
               case 'collision'
                   out= [];
                   if length(data)~=obj.ApiInfo.RspCollisionDlen-1
                       result = 0;
                   else
                       x = obj.cmdFromByte(data(1:2), 'int16'); %#ok<NASGU>
                       y = obj.cmdFromByte(data(3:4), 'int16'); %#ok<NASGU>
                       z = obj.cmdFromByte(data(5:6), 'int16'); %#ok<NASGU>
                       axis = uint8(data(7));
                       xMag = obj.cmdFromByte(data(8:9), 'int16'); %#ok<NASGU>
                       yMag = obj.cmdFromByte(data(10:11), 'int16'); %#ok<NASGU>
                       speed = uint8(data(12)); %#ok<NASGU>
                       timestamp = obj.cmdFromByte(data(13:16), 'uint32'); %#ok<NASGU>
                       
                       if bitget(axis, 1)
                           obj.CollisionDetected = 'x';
                       elseif bitget(axis, 2)
                           obj.CollisionDetected = 'y';
                       end
                       
                       result = 1;
                   end
                   
               case 'gyroaxislimit'
                   out = [];
                   if length(data)~=obj.ApiInfo.RspGyroAxisLimitDlen-1
                       result = 0;
                   else
                       result = 1;
                       obj.GyroAxisLimitExceed = 1;
                   end
                case 'sensor'

                   out = [];
                   sprintf(['Sensor data streaming \n' num2str(data)])%%% Remove after debugging
                   
                % Check if the number of elements in the received response
                % are equal to the samples per packet per sensor * number of sensors
                  if length(data)== obj.SamplesPerPacket * length(obj.Sensors)*2;
                      data = reshape(data, length(obj.Sensors)*2, obj.SamplesPerPacket)';  
                  else
                      result=0;
                      return
                  end
                  
                  % Initialilze the 'sensordata' variable, which is a
                  % structure containing the present data received from the
                  % sensors.
                  for i=1:length(obj.Sensors)
                      sensordata.(obj.Sensors{i}) = [];
                  end
                  
                  for i=1:size(data,1)
                      for j=1:size(data,2)/2
                            sensordata.(obj.Sensors{j})(end+1) =  obj.cmdFromByte(data(i,2*j-1:2*j), 'int16');
                      end
                  end
                  
                  result=1;
                  obj.SensorData = sensordata;
                  obj.SensorDataPropertySet = 1;
%                        for i=1:length(sensordata)
%                             obj.SensorData.(obj.Sensors{i}) = sensordata(i);
%                        end
                %% Following cases have not been complately considered yet. 
                % Just putting placeholders so that doesn't error out
               case 'level1diag'
                   result = 1;
                   out = [];
               case 'configblk'
                   result = 1;
                   out = [];
               case 'macro'
                   result = 1;
                   out = [];
               case 'orbbasicprint'
                   result = 1;
                   out = [];
               case 'orbbasicerrorascii'
                   result = 1;
                   out = [];
               case 'orbbasicerrorbinary'
                   result = 1;
                   out = [];
               case 'selflevel'
                  result = 1;
                   out = []; 
               case 'ssb'
                  result = 1;
                   out = []; 
               case 'levelup'
                  result = 1;
                   out = []; 
               case 'shielddamage'
                   result = 1;
                   out = [];
               case 'xpupdate'
                  result = 1;
                   out = []; 
               case 'boostupdate'
                   result = 1;
                   out = [];

                %% All Other cases for response
                otherwise
                     if length(data)~= obj.ApiInfo.RspSimpleDlen-1
%                         error(err)
                          result = 0;
                          out = obj.ResponseError;
                     else
                         result = 1;
                         out = [];
                     end
            end
        end
      
        function action = decodeAction(obj, ack, idx)
           switch ack
               case 1
%                    idx = arrayfun(@(x) find(x.seq==code), obj.SequenceList);
                   
                   if ~isempty(idx)
                       action = obj.SequenceList.action{idx(1)};
                   else
                       action = 'notfound';
                   end
                   
               case 0
                   if idx>0 && idx<=length(obj.ApiInfo.RspAsync)
                       action = obj.ApiInfo.RspAsync{idx};
                   else
                       action = 'notfound';
                   end
               otherwise
                   action = 'notfound';
           end
        end
        
%         function action = decodeAsyncAction(idcode)
% %             if idcode>length(obj.ApiInfo.RspAsync)
% %                 result = 0;
% %                 action = '';
% %             else
% %                 result=1;
%                 action = obj.ApiInfo.RspAsync{idcode};
% %             end
%         end
        
        function dec = packedNibble2Dec(~, hex)
            dec = hex2dec(hex(1));
            
            nibble2 = hex2dec(hex(2));
            if nibble2<10
                dec = dec+nibble2/10;
            else
                dec = dec+nibble2/100;
            end
            
        end
        
        function  saveSeq(obj, respond, seq, action)
        %Save the sequence number in the SequenceList
            if respond
                idx = indexOfResponseAction(obj, action);
                
                if isempty(idx)
                    obj.SequenceList.seq(end+1) = seq;
                    obj.SequenceList.action{end+1} = action;
                    obj.SequenceList.response{end+1} = obj.ResponseInitialValue;
                else
                    obj.SequenceList.seq(idx) = seq;
                    obj.SequenceList.response{idx} = obj.ResponseInitialValue;
                end
            end
        end
        
            
        function assembleResponse(obj)
            %If error occurs on assembling asynchronous response, then 
            % throw the error. If error occurs during synchronous response,
            % set the response to NaN (ResponseError)
            
           processing = 1;
                
           try
                while processing
                    dlen = obj.Response(obj.ApiInfo.SpheroResponse.dlen);
                    responseEnd = obj.ApiInfo.SpheroResponse.dlen+dlen;
                    
                    readDataLength = length(obj.Response)-obj.ApiInfo.SpheroResponse.dlen;
                
                    obj.BytesToRead = dlen-readDataLength;
                
                    if obj.BytesToRead<=0
                        response = obj.Response(1:responseEnd);
                        ack = processResponse(obj, response);
                        obj.Response(1:responseEnd) = [];
                        
%                         obj.BytesToRead
                        if length(obj.Response)<obj.ApiInfo.SpheroResponse.dlen
                            processing = 0;
                           obj.BytesToRead =  Inf;
                        end
                    else
                        processing = 0;
                    end
                end
          catch exception
              flushinput(obj.Bt); 
              obj.Response(1:responseEnd) = [];
              
              %%%%%%%%% Test if this works in reestablishing the
              %%%%%%%%% BytesAvailbale function
              obj.Bt.BytesAvailableFcnCount = 1;
              obj.Bt.BytesAvailableFcnMode = 'byte';
              obj.Bt.BytesAvailableFcn = @obj.readBytes;
              %%%%%%%%%%%%  
              
              obj.disconnect();
                
              if exist('ack', 'var') && ack
                  obj.ErrorSynchronous = exception; %NOTE: Test this out
              else
                  obj.ErrorAsynchronous = exception;
              end
%               throwAsCaller(exception)
%                 rethrow(exception)
            
          end
                
        end
        function readBytes(obj, eventSrc, eventData)
            %
            % If on reading the additional number of bytes, the length of
            % the Reponse is more than the number of bytes till 'dlen'
            % byte, then assemble the Response
            % Or if the length of response at present is more than the num
            % of bytes till 'dlen', then check if the additional number of
            % bytes that can be read will be more than the number of bytes
            % that should be read to complete the message
            
            lenRsp = length(obj.Response);
            numDlen = obj.ApiInfo.SpheroResponse.dlen;
            
            avail = eventSrc.BytesAvailable %%% Remove after debugging
            
            if (lenRsp<numDlen && lenRsp+eventSrc.BytesAvailable>=numDlen) || ...
                (lenRsp>=numDlen && eventSrc.BytesAvailable>=obj.BytesToRead)
                
                bytesRead = eventSrc.BytesAvailable;
                
                obj.Response(end+1:end+bytesRead) = fread(eventSrc, bytesRead);
                
                %%%%%%%%
                obj.Response%%% Remove after debugging
%                 error('test');
                %%%%%%%
                
                assembleResponse(obj);
            end
        end
        
       
        
        function ack = processResponse(obj, response)
            err = MException('Sphero:Api:InvalidResponse',...
               'Received response is not valid');
           
          
%            try 
                [valid, ack, data, code] = decodeResponse(obj, response);

                if ack==1
                    idx = indexOfResponseSequence(obj, code);
                else
                    idx = code;
                end


                action = decodeAction(obj, ack, idx);

                if (~valid || strcmp(action , 'notfound'))
                    if ack && ~isempty(idx)
                        obj.SequenceList.response{idx(1)} = obj.ResponseError;
                        return
                    else
                        throw(err);
    %                     obj.Response(1:responseEnd) = [];
    %                     error('Received response is not valid')


                    end
                end

                [result2, out] = decodeResponseData(obj, data, action);

                if result2 && ack
                    obj.SequenceList.response{idx(1)} = out;
                elseif ack
                    obj.SequenceList.response{idx(1)} = obj.ResponseError;
                elseif ~result2 %When response is asynchronous & result is 0
                    throw(err)
    %                 obj.Response(1:responseEnd) = [];
    %                 error('Received asynchronous response is invalid');
                end
                
%            catch exception
%                obj.Response(1:responseEnd) = [];
%                rethrow(exception)
%             
%            end
%         
        end
        function throwAsyncError(obj, src, eventdata)
            if ~isempty(obj.ErrorAsynchronous)
%                 err = MException(obj.ErrorAsynchronous.identifier, obj.ErrorAsynchronous.message);
                
                warning(['Error occured when reading Asynchronous message: ' obj.ErrorAsynchronous.message]);
                lastwarn(''); %Added so that instrcb.m does not display the warning again
                obj.ErrorAsynchronous = [];
            end
        end
        
    end
    
    methods
        
        function obj = BluetoothApi
            hInfo = sphero.internal.ApiInfo(obj.Rev);
            obj.ApiInfo = hInfo.Constants;
            obj.ApiInfo.SpheroResponse = hInfo.SpheroResponse;
            
            obj.SequenceList.seq = [];
            obj.SequenceList.action = {};
            obj.SequenceList.response = {};
            
            addlistener(obj, 'ErrorAsynchronous',  'PostSet',  @obj.throwAsyncError);
             
        end
        
%         function sensornames = get.Sensors(obj)
%             sensornames = obj.sph.SensorPolling.sensors;
%         end
        
        function [cmd, respond, seq] = createCommand(obj, action, varargin)
            % Arguments:
            % 1. Api object
            % 2. Action to be performed
%             % 3. Data
            % 3. Sequence number ([] if sequence number is to be
            % automatically selected)
            % 4. Whether sphero should respond to messge
            % 5. Reset the inactivity timeout
            % 6 onwards: Data that has to be sent to device for the action
            
            action = validateAction(obj, action);
                        
            if nargin>2
               seq = varargin{1};
            else
                seq = [];
            end
            
            if nargin>3 && ~isempty(varargin{2})
               respond = varargin{2}; 
            elseif obj.Handshake
               respond = 1;
            else
                respond = 0;
            end
            
            if nargin>4 && ~isempty(varargin{3})
                reset = varargin{3};
            else
                reset = 1;
            end
            
            if nargin>5
                data = formatCommandData(obj, action, varargin{4:end});
            else
                data = [];
            end
            

            % Create the command to be sent
            
            % SOP1 - FFh
            % SOP2 - bit1 is reset timeout, and bit0 is whether send a
            % reply to the command or not
            
            sop1 = obj.ApiInfo.expectedSop1;
            sop2 = bin2dec(['111111' dec2bin(reset) dec2bin(respond)]);
              
            
            [did, cid, dlen] = obtainId(obj,action, data);
            data = uint8(data);
            
            if isempty(seq)
                seq = obj.Sequence;
                obj.Sequence=obj.Sequence+1;
            end
            
            if dlen ~= numel(data)+1;
               throwAsCaller(MException('Sphero:Api:IncorrectCommand', ...
                   ['Data being sent through the Client Command Packet is ',...
                   'of incorrect size according to the Bluetooth API']));
            end
            
%             cmd(ApiInfo.ClientCommand.sop1) = sop1;
%             cmd(ApiInfo.ClientCommand.sop2) = sop2;
%             cmd(ApiInfo.ClientCommand.did)  = did;
%             cmd(ApiInfo.ClientCommand.cid)  = cid;
%             cmd(ApiInfo.ClientCommand.seq)  = seq;
%             cmd(ApiInfo.ClientCommand.dlen) = dlen;
%             cmd(ApiInfo.ClientCommand.data:ApiInfo.ClientCommand.data+ApiInfo.ClientCommand.dlen-1) = data;
%             
%             
%             
              cmd = [sop1 sop2 did cid seq dlen data];
          
              chk = obj.computeCheckSum(cmd);
            
              cmd = [cmd chk];
              
              %Save the sequence number in the SequenceList
              saveSeq(obj, respond, seq, action);
              
        end
        
        
        
        function response = readResponse(obj, responseexpected, seq, responseTimeout)
            % Read the response from the SequenceList structure
            % If timeout occurs, then give error
            % If timeout doesnt occur, but the received response is
            % invalid, then return NaN(ResponseError)
            err = MException('Sphero:Api:timeout', 'Response Timeout');
%             pause(0.5)
            
            if responseexpected
                idx = indexOfResponseSequence(obj, seq);
                
                 t = cputime;
                 
                try  
                    while ~iscell(obj.SequenceList.response{idx}) && any(isinf(obj.SequenceList.response{idx}(:)))
                        if ~isempty(obj.ErrorSynchronous)
                            throw(obj.ErrorSynchronous);
                        elseif cputime-t>responseTimeout
                            
                            throw(err);
                        end

                        idx = indexOfResponseSequence(obj, seq);
                    end
                
                    if idx(1)<=length(obj.SequenceList.seq)
                        response = obj.SequenceList.response{idx(1)};
                        %Remove the action from the SequenceList

                        obj.SequenceList.response{idx(1)} = [];
                        obj.SequenceList.action{idx(1)} = [];
                        obj.SequenceList.seq(idx(1)) = [];

                        % remove empty arrays in cell arrays
                        obj.SequenceList.action = obj.SequenceList.action(~cellfun(@isempty, obj.SequenceList.action));
                        obj.SequenceList.response = obj.SequenceList.response(~cellfun(@isempty, obj.SequenceList.response));

                    else
                        response = obj.ResponseError;
                    end
                    
                catch exception
%                     throwAsCaller(exception);
                       idx = indexOfResponseSequence(obj, seq);
                        if ~isempty(idx)
                            %Remove the action from the SequenceList
                            obj.SequenceList.response{idx(1)} = [];
                            obj.SequenceList.action{idx(1)} = [];
                            obj.SequenceList.seq(idx(1)) = [];

                            % remove empty arrays in cell arrays
                            obj.SequenceList.action = obj.SequenceList.action(~cellfun(@isempty, obj.SequenceList.action));
                            obj.SequenceList.response = obj.SequenceList.response(~cellfun(@isempty, obj.SequenceList.response));
                        end

                    obj.ErrorSynchronous = [];
                     rethrow(exception);
                end
                    
            else
                response = obj.ResponseEmpty;
            end
        end
        
        %% Decode Response
        function [valid, ack, data, code] = decodeResponse(obj, response)
               
           response = uint8(response);
           
%             try
                sop1 = response(obj.ApiInfo.SpheroResponse.sop1);
                sop2 = response(obj.ApiInfo.SpheroResponse.sop2);
                if sop2==obj.ApiInfo.sop2Acknowledgement
                    mrsp = response(obj.ApiInfo.SpheroResponse.mrsp);
                    code  = response(obj.ApiInfo.SpheroResponse.seq);
                    dlen = response(obj.ApiInfo.SpheroResponse.dlen);
                    
%                     idcode = 0;
%                     msg = 'ack';
                    ack = 1;
                    

                elseif sop2==obj.ApiInfo.sop2Asynchronous
                    code  = response(obj.ApiInfo.SpheroResponse.idcode);
                    dlenmsb = response(obj.ApiInfo.SpheroResponse.dlenmsb);
                    dlenlsb = response(obj.ApiInfo.SpheroResponse.dlenlsb);
                    dlen = obj.cmdFromByte([dlenmsb, dlenlsb]);
                    
                    mrsp = 0;
%                     seq = 0;
%                     msg = 'asy';
                    ack = 0;
                    
                    
            
                else
                    valid = 0;
                    data = [];
                    ack = 0;
                    code = 0;
                    return
%                     error(err);
                end
                
                data = response(obj.ApiInfo.SpheroResponse.data:end-1);
                chk  = response(end);

                valid = checkValidityResponse(obj, sop1, sop2, mrsp, code, dlen, data, chk, response);

% %                 action = decodeAckAction(seq);
% %                 action = decodeAsyncAction(idcode);
%                 
%                 action = decodeAction(obj, ack, code);
%                 
%                 if ~valid || strcmp(action , 'notfound')
%                     error(err)
%                 end
% 
%                 
%                 [result2, varagout] = decodeResponseData(obj, data, action);
%                 
%                 if ~result1 || ~result2
%                     error(err)
%                 end
%                 
%             catch
%                 error(err)
%             end
            
        end
       
        function delete(obj)
            disconnect(obj);
         end

        function [responseexpected, seq] = sendCmd(obj, action, varargin)
            
            %Other checking
            
            if strcmp(obj.Bt.status, 'open')
                [cmd, responseexpected, seq] = createCommand(obj, action, varargin{:});
                fwrite(obj.Bt, cmd);
            else
                err = MException('Sphero:NotConnected', 'Connection with sphero is not active. Please recheck the connection');
                throwAsCaller(err) ;
            end
           
        end
        
         function idx = indexOfResponseSequence(obj, seq)
            idx = find(obj.SequenceList.seq==seq); %Index of the sequence 
            %number which was achnowledged in the response
         end
        
         function idx = indexOfResponseAction(obj, action)
             idx = find(cellfun(@(x) strcmp(x, action), obj.SequenceList.action));
         end
        
        function connect(obj, varargin)
            
            channel = 1;
            
            if (nargin>1 && ~isempty(varargin{1}))
                if iscell(varargin{1})
                    devicename = varargin{1}{1};
                else
                    devicename = varargin{1};
                end

                          
            elseif ~isempty(obj.DeviceName)
                devicename = obj.DeviceName;
            else
               devicename = obj.findDevices;
                
            end

            try
                obj.Bt = Bluetooth(devicename, channel);
                %Open the bluetooth channel
               
                flushinput(obj.Bt);
                flushoutput(obj.Bt); 
                
                obj.Bt.BytesAvailableFcnCount = 1;
                obj.Bt.BytesAvailableFcnMode = 'byte';
                obj.Bt.BytesAvailableFcn = @obj.readBytes;
                
                fopen(obj.Bt);
                flushinput(obj.Bt);
                flushoutput(obj.Bt); 
                
                obj.DeviceName = devicename;
%                 result = ping(obj);
%                 if ~result
%                     error('Sphero:Api:InvalildDevice', ...
%                     'Unable to connect to device. Please check that the device name is correct and the device is discoverable');
%                 end
            
            catch
                err = MException('Sphero:Api:InvalildDevice', ...
                    'Unable to connect to device. Please check that the device name is correct and the device is discoverable');
                throw(err);
            end
        end
        
        function disconnect(obj)
            if strcmp(obj.Bt.Status, 'open')
                fclose(obj.Bt);
            end
        end
        
        
    end
    
end