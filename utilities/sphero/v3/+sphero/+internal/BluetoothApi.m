<<<<<<< HEAD:utilities/sphero/v3/+sphero/+internal/BluetoothApi.m
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
        PowerNotification
        SensorData
        PreSleepWarning
        CollisionDetection
        GyroAxisLimitExceed
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
        SensorDataPropertySet = 0;
    end
    
    
    methods(Access = private)
        
        function devicename = findDevices(obj)
    
                devices = instrhwinfo('Bluetooth');
                checksphero = strncmp(devices.RemoteNames, obj.SpheroDeviceNameBeg, length(obj.SpheroDeviceNameBeg));
                
                spherodevices = devices.RemoteNames(checksphero);
            
                if isempty(spherodevices)
                    error('No Sphero device available. Please make sure your Sphero device is switched on and is in vicinity');
%                     throw(
                else
                    choose = 'Choose one of the available Sphero devices: \n '; 
                    for idx=1:length(spherodevices)
                        choose = [choose num2str(idx) '. ' spherodevices{idx} '\n'];
                    end

                    response = 'n';

                    while(~strcmp(response, 'y'))
                        chosen = input(sprintf(choose));
                        if chosen<=length(spherodevices)
                           recheck = ['Are you sure you would like to connect to ' spherodevices{chosen} ' [y/n] : '];
                            response = input(recheck, 's');
                        else
                            error('Please select one of the available devices')
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

            err = MException('commandInfo:InvalidParameter', 'Please enter a valid command');

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
                    throw(err)
            end
            
%             did  = uint8(hex2dec(did));
%             cid  = uint8(hex2dec(cid));
            dlen = uint8(hex2dec(dlen));
        end
        
        function validAction = validateAction(obj,action)
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
                case 'sleep'
                    origdata = cell2mat(varargin);
                    data(1:2) = cmdToByte(obj, uint16(origdata(1)));
                    data(3) = uint8(origdata(2));
                     data(4:5) = cmdToByte(obj, uint16(origdata(3)));
                case 'setpowertrips'
                    origdata = cell2mat(varargin);
                    data(1:2) = cmdToByte(obj, uint16(origdata(1)));
                    data(3:4) = cmdToByte(obj, uint16(origdata(2)));
                case 'setrgbled'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'roll'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = cmdToByte(obj, uint16(origdata(2)));
                    data(4) = uint8(origdata(3));
                case 'setcal'
                    origdata = cell2mat(varargin);
                    data = cmdToByte(obj, uint16(origdata));
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
                    data(1:2) = cmdToByte(obj, uint16(varargin{1}));
                    data(3:4) = cmdToByte(obj, uint16(varargin{2}));
                    data(5:8) = cmdToByte(obj, uint32(varargin{3}));
                    data(9) = cmdToByte(obj, uint8(varargin{4}));
                    data(10:13) = cmdToByte(obj, uint32(varargin{5}));
                case 'setcollisiondet'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'locator'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = cmdToByte(obj, int16(origdata(2)));
                    data(4:5) = cmdToByte(obj, int16(origdata(3)));
                    data(6:7) = cmdToByte(obj, int16(origdata(3)));
                case 'boost'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setrawmotors'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setmotionto'
                    origdata = cell2mat(varargin);
                    data(1:2) = cmdToByte(obj, uint16(origdata(1)));
                otherwise
                    data = [];
                    
                    
                
            end
        end
            
        
        function valid = checkValidityResponse(obj, sop1, sop2, msrp, code, dlen, data, chk, response)
           expectedChk = computeCheckSum(obj, response(1:end-1));
%            err = MException('checkValidityResponse:InvalidResponse',...
%                'Valid response not received');
                
           
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
            switch msrp
                case obj.ApiInfo.RspCodeOk
                    valid = 1;
                
%                 case obj.ApiInfo.RspCodeegen
%                 
%                 case obj.ApiInfo.RspCodeEchksum
%                 
%                 case obj.ApiInfo.RspCodeEfrag
%                 
%                 case obj.ApiInfo.RspCodeEbadCmd
%                 
%                 case obj.ApiInfo.RspCodeEunsupp
%                 
%                 case obj.ApiInfo.RspCodeEbadMsg
%                 
%                 case sobj.ApiInfo.RspCodeEparam
%                 
%                 case obj.ApiInfo.RspCodeEexec
%                 
%                 case obj.ApiInfo.RspCodeEbadDid
%                 
%                 case obj.ApiInfo.RspCodeMemBusy
%                 
%                 case obj.ApiInfo.RspCodeBadPassword
%                 
%                 case obj.ApiInfo.RspCodePowerNogood
%                 
%                 case obj.ApiInfo.RspCodePageIllegal
%                         
%                 case obj.ApiInfo.RspCodeFlashFail
%                 
%                 case obj.ApiInfo.RspCodeMaCorrupt
%                  
%                 case sobj.ApiInfo.RspCodeMsgTimeout
                    
                otherwise
                    error('Unrecognized Message Reponse received. Please check API definition');
                    valid=0;
            
                
            end
        end
        
        function cmd = cmdToByte(obj, cmdIn)
        %CMDTOBYTE    Convert multiple byte data to array of uint8
            % CMDTOBYTE(H, CMDIN) converts CMDIN to an array of uint8
            % data. It checks whether the machine is big endian and little
            % endian, and arranges the uint8 data based on that
            
             [~,~,endian] = computer;
               
             if strcmp(endian, 'L')
                   cmd = typecast(swapbytes(cmdIn), 'uint8');
             else
                   cmd = typecast(cmdIn, 'uint8');
             end
        end
        
        function cmd = cmdFromByte(obj, bytedata, varargin)
         %CMDFROMBYTE    Convert 2 byte data to uint16 data 
            % CMDTOBYTE(H, BYTEDATA) converts the data represented by the 
            % BYTEDATA vector (containing Most Significant Bit and Least 
            % Significant Bit) to an uint16 variable. 
            % It checks whether the machine is big endian or little
            % endian, and arranges the data based on that
            % CMDTOBYTE(H, BYTEDATA, DATATYPE) converts the BYTEDATA to 
            % the desired DATATYPE
            if nargin>3
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
        
        function [result, out] = decodeResponseData(obj, data, action)
%             err = MException('decodeResponseData:InvalidResponse',...
%                'Valid response not received');
            
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
                       voltage      = cmdFromByte(obj, data(3:4), 'uint16');
                       charges      = cmdFromByte(obj, data(5:6), 'uint16');
                       timeawake    =  cmdFromByte(obj, data(7:8), 'uint16');
                       
                       out = {recver powerstate voltage charges timeawake};
                       
                   end
               case 'getpowertrips'
                   if length(data)~=obj.ApiInfo.RspGetPowerTripsDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out(1) = cmdFromByte(obj, data(1:2), 'uint16');
                       out(2) = cmdFromByte(obj, data(3:4), 'uint16');
                   end
               case 'runl2diags'
                   if length(data)~=obj.ApiInfo.RspRunL2DiagsDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       
                       out{1} = cmdFromByte(obj, data(1:2), 'uint16');
                       out{2} = cmdFromByte(obj, data(4:7), 'uint32');
                       out{3} = cmdFromByte(obj, data(8:11), 'uint32');
                       out{4} = cmdFromByte(obj, data(12:15), 'uint32');
                       out{5} = cmdFromByte(obj, data(16:19), 'uint32');
                       out{6} = cmdFromByte(obj, data(20:23), 'uint32');
                       out{7} = cmdFromByte(obj, data(24:27), 'uint32');
                       out{8} = cmdFromByte(obj, data(28:31), 'uint32');
                       out{9} = cmdFromByte(obj, data(32:35), 'uint32');
                       out{10} = data(36);
%                        out{11} = cmdFromByte(obj, data(37:68), 'uint32');
                       out{12} = cmdFromByte(obj, data(71:72), 'uint16');
                       out{13} = cmdFromByte(obj, data(73:74), 'uint16');
                       out{14} = cmdFromByte(obj, data(75:78), 'uint32');
                       out{15} = cmdFromByte(obj, data(79:82), 'uint32');
                       out{16} = cmdFromByte(obj, data(83:84), 'uint16');
                       out{17} = cmdFromByte(obj, data(85:88), 'uint32');
                       
                   end
               case 'getrgbled'
                    if length(data)~= obj.ApiInfo.RspGetRgbLedDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out = data;
                       
                    end
                   
               case 'sensor'
%                    result = 0;
                   out = [];
                   sprintf(['Sensor data streaming \n' num2str(data)])
                   
                   
%                    sensordata = zeros(length(data)/2, 1);

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
                            sensordata.(obj.Sensors{j})(end+1) =  cmdFromByte(obj, data(i,2*j-1:2*j), 'int16');
                      end
                  end
                  
                  result=1;
                  obj.SensorData = sensordata;
                  obj.SensorDataPropertySet = 1;
%                        for i=1:length(sensordata)
%                             obj.SensorData.(obj.Sensors{i}) = sensordata(i);
%                        end


               case 'readlocator'
                   if length(data)~= obj.ApiInfo.RspReadLocatorDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       xpos = cmdFromByte(obj, data(1:2), 'int16');
                       ypos = cmdFromByte(obj, data(3:4), 'int16');
                       xvel = cmdFromByte(obj, data(5:6), 'int16');
                       yvel = cmdFromByte(obj, data(7:8), 'int16');
                       sog = cmdFromByte(obj, data(9:10), 'uint16');
                       
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
                   % Other cases for response
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
                        processResponse(obj, response);
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
                
%               throwAsCaller(exception)
                rethrow(exception)
            
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
                
                obj.Response%%% Remove after debugging
                
                assembleResponse(obj);
            end
        end
        
       
        
        function processResponse(obj, response)
            err = MException('checkValidityResponse:InvalidResponse',...
               'Received response is not valid');
           
           response
           
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
        
        
    end
    
    methods
        
        function obj = BluetoothApi
            hInfo = sphero.internal.ApiInfo(obj.Rev);
            obj.ApiInfo = hInfo.Constants;
            obj.ApiInfo.SpheroResponse = hInfo.SpheroResponse;
            
            obj.SequenceList.seq = [];
            obj.SequenceList.action = {};
            obj.SequenceList.response = {};
             
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
               error(['Data being sent through the Client Command Packet is ',...
                   'of incorrect size according to the Bluetooth API']);
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
            err = MException('readResponse:timeout', 'Response Timeout');
            
            if responseexpected
                idx = indexOfResponseSequence(obj, seq);
                
                 t = cputime;
                 
                try  
                    while ~iscell(obj.SequenceList.response{idx}) && any(isinf(obj.SequenceList.response{idx}(:)))
                        if cputime-t>responseTimeout
                            if ~isempty(idx)
                                %Remove the action from the SequenceList
                                obj.SequenceList.response{idx(1)} = [];
                                obj.SequenceList.action{idx(1)} = [];
                                obj.SequenceList.seq(idx(1)) = [];

                                % remove empty arrays in cell arrays
                                obj.SequenceList.action = obj.SequenceList.action(~cellfun(@isempty, obj.SequenceList.action));
                                obj.SequenceList.response = obj.SequenceList.response(~cellfun(@isempty, obj.SequenceList.response));
                            end

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
                    dlen = cmdFromByte(obj, [dlenmsb, dlenlsb]);
                    
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
%                     throw(err);
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
%                     throw(err)
%                 end
% 
%                 
%                 [result2, varagout] = decodeResponseData(obj, data, action);
%                 
%                 if ~result1 || ~result2
%                     throw(err)
%                 end
%                 
%             catch
%                 throw(err)
%             end
            
        end
       
        function delete(obj)
            disconnect(obj);
         end

        function [responseexpected, seq] = sendCmd(obj, action, varargin)
            
            %Check if connection open
            %Other checking
            
            [cmd, responseexpected, seq] = createCommand(obj, action, varargin{:});
            fwrite(obj.Bt, cmd);
            cmd %%%Remove after debugging
            
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
%                     error('Device:Invalild', ...
%                     'Unable to connect to device. Please check that the device name is correct and the device is discoverable');
%                 end
            
            catch
                err = MException('Device:Invalild', ...
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
    
=======
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
        PowerNotification
        SensorData
        PreSleepWarning
        CollisionDetection
        GyroAxisLimitExceed
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
        
        Sequence = uint8(1);
        Handshake = 0;
        ApiInfo;
        Bt;
        Response;
        BytesToRead  =  Inf;
        Sensors;
        SamplesPerPacket;
        SensorDataPropertySet = 0;
    end
    
    
    methods(Access = private)
        
        function devicename = findDevices(obj)
    
                devices = instrhwinfo('Bluetooth');
                checksphero = strncmp(devices.RemoteNames, obj.SpheroDeviceNameBeg, length(obj.SpheroDeviceNameBeg));
                
                spherodevices = devices.RemoteNames(checksphero);
            
                if isempty(spherodevices)
                    error('No Sphero device available. Please make sure your Sphero device is switched on and is in vicinity');
%                     throw(
                else
                    choose = 'Choose one of the available Sphero devices: \n '; 
                    for idx=1:length(spherodevices)
                        choose = [choose num2str(idx) '. ' spherodevices{idx} '\n'];
                    end

                    response = 'n';

                    while(~strcmp(response, 'y'))
                        chosen = input(sprintf(choose));
                        if chosen<=length(spherodevices)
                           recheck = ['Are you sure you would like to connect to ' spherodevices{chosen} ' [y/n] : '];
                            response = input(recheck, 's');
                        else
                            error('Please select one of the available devices')
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

            err = MException('commandInfo:InvalidParameter', 'Please enter a valid command');

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
                    
                otherwise
                    throw(err)
            end
            
%             did  = uint8(hex2dec(did));
%             cid  = uint8(hex2dec(cid));
            dlen = uint8(hex2dec(dlen));
        end
        
        function validAction = validateAction(obj,action)
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
                'getssb', 'setssb', 'ssbrefill', 'ssbbuy', ...
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
                case 'sleep'
                    origdata = cell2mat(varargin);
                    data(1:2) = cmdToByte(obj, uint16(origdata(1)));
                    data(3) = uint8(origdata(2));
                     data(4:5) = cmdToByte(obj, uint16(origdata(3)));
                case 'setrgbled'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'roll'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = cmdToByte(obj, uint16(origdata(2)));
                    data(4) = uint8(origdata(3));
                case 'setcal'
                    origdata = cell2mat(varargin);
                    data = cmdToByte(obj, uint16(origdata));
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
                    data(1:2) = cmdToByte(obj, uint16(varargin{1}));
                    data(3:4) = cmdToByte(obj, uint16(varargin{2}));
                    data(5:8) = cmdToByte(obj, uint32(varargin{3}));
                    data(9) = cmdToByte(obj, uint8(varargin{4}));
                    data(10:13) = cmdToByte(obj, uint32(varargin{5}));
                case 'setcollisiondet'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'locator'
                    origdata = cell2mat(varargin);
                    data(1) = uint8(origdata(1));
                    data(2:3) = cmdToByte(obj, int16(origdata(2)));
                    data(4:5) = cmdToByte(obj, int16(origdata(3)));
                    data(6:7) = cmdToByte(obj, int16(origdata(3)));
                case 'boost'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setrawmotors'
                    origdata = cell2mat(varargin);
                    data = uint8(origdata);
                case 'setmotionto'
                    origdata = cell2mat(varargin);
                    data(1:2) = cmdToByte(obj, uint16(origdata(1)));
                otherwise
                    data = [];
                    
                    
                
            end
        end
            
        
        function valid = checkValidityResponse(obj, sop1, sop2, msrp, code, dlen, data, chk, response)
           expectedChk = computeCheckSum(obj, response(1:end-1));
%            err = MException('checkValidityResponse:InvalidResponse',...
%                'Valid response not received');
                
           
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
            switch msrp
                case obj.ApiInfo.RspCodeOk
                    valid = 1;
                
%                 case obj.ApiInfo.RspCodeegen
%                 
%                 case obj.ApiInfo.RspCodeEchksum
%                 
%                 case obj.ApiInfo.RspCodeEfrag
%                 
%                 case obj.ApiInfo.RspCodeEbadCmd
%                 
%                 case obj.ApiInfo.RspCodeEunsupp
%                 
%                 case obj.ApiInfo.RspCodeEbadMsg
%                 
%                 case sobj.ApiInfo.RspCodeEparam
%                 
%                 case obj.ApiInfo.RspCodeEexec
%                 
%                 case obj.ApiInfo.RspCodeEbadDid
%                 
%                 case obj.ApiInfo.RspCodeMemBusy
%                 
%                 case obj.ApiInfo.RspCodeBadPassword
%                 
%                 case obj.ApiInfo.RspCodePowerNogood
%                 
%                 case obj.ApiInfo.RspCodePageIllegal
%                         
%                 case obj.ApiInfo.RspCodeFlashFail
%                 
%                 case obj.ApiInfo.RspCodeMaCorrupt
%                  
%                 case sobj.ApiInfo.RspCodeMsgTimeout
                    
                otherwise
                    error('Unrecognized Message Reponse received. Please check API definition');
                    valid=0;
            
                
            end
        end
        
        function cmd = cmdToByte(obj, cmdIn)
        %CMDTOBYTE    Convert multiple byte data to array of uint8
            % CMDTOBYTE(H, CMDIN) converts CMDIN to an array of uint8
            % data. It checks whether the machine is big endian and little
            % endian, and arranges the uint8 data based on that
            
             [~,~,endian] = computer;
               
             if strcmp(endian, 'L')
                   cmd = typecast(swapbytes(cmdIn), 'uint8');
             else
                   cmd = typecast(cmdIn, 'uint8');
             end
        end
        
        function cmd = cmdFromByte(obj, msb, lsb, varargin)
         %CMDFROMBYTE    Convert 2 byte data to uint16 data 
            % CMDTOBYTE(H, MSB, LSB) converts the data represented by the 
            %Most Significant Bit and Least Significant Bit to an uint16 variable. 
            % It checks whether the machine is big endian or little
            % endian, and arranges the data based on that
            if nargin>3
                type = varargin{1};
            else
                type = 'uint16';
            end
                
            [~,~,endian] = computer;
            
            if strcmp(endian, 'L')
                   cmd = swapbytes(typecast([msb lsb], type));
            else
                   cmd = typecast([msb lsb], type);
            end
        end
        
        function [result, out] = decodeResponseData(obj, data, action)
%             err = MException('decodeResponseData:InvalidResponse',...
%                'Valid response not received');
            
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
                       voltage      = cmdFromByte(obj, data(3), data(4), 'uint16');
                       charges      = cmdFromByte(obj, data(5), data(6), 'uint16');
                       timeawake    =  cmdFromByte(obj, data(7), data(8), 'uint16');
                       
                       out = {recver powerstate voltage charges timeawake};
                       
                   end
               case 'getrgbled'
                    if length(data)~= obj.ApiInfo.RspGetRgbLedDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       out = data;
                       
                    end
                   
               case 'sensor'
%                    result = 0;
                   out = [];
                   sprintf(['Sensor data streaming \n' num2str(data)])
                   
                   
%                    sensordata = zeros(length(data)/2, 1);

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
                            sensordata.(obj.Sensors{j})(end+1) =  cmdFromByte(obj, data(i,2*j-1), data(i,2*j), 'int16');
                      end
                  end
                  
                  result=1;
                  obj.SensorData = sensordata;
                  obj.SensorDataPropertySet = 1;
%                        for i=1:length(sensordata)
%                             obj.SensorData.(obj.Sensors{i}) = sensordata(i);
%                        end


               case 'readlocator'
                   if length(data)~= obj.ApiInfo.RspReadLocatorDlen-1
                       result = 0;
                       out = [];
                   else
                       result = 1;
                       xpos = cmdFromByte(obj, data(1), data(2), 'int16');
                       ypos = cmdFromByte(obj, data(3), data(4), 'int16');
                       xvel = cmdFromByte(obj, data(5), data(6), 'int16');
                       yvel = cmdFromByte(obj, data(7), data(8), 'int16');
                       sog = cmdFromByte(obj, data(9), data(10), 'uint16');
                       
                       out = {xpos ypos xvel yvel sog};
                       
                    end
                   
                   
                   % Other cases for response
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
           processing = 1;
                
                while processing
                    dlen = obj.Response(obj.ApiInfo.SpheroResponse.dlen);
                    responseEnd = obj.ApiInfo.SpheroResponse.dlen+dlen;
                    
                    readDataLength = length(obj.Response)-obj.ApiInfo.SpheroResponse.dlen;
                
                    obj.BytesToRead = dlen-readDataLength;
                
                    if obj.BytesToRead<=0
                        response = obj.Response(1:responseEnd);
                        processResponse(obj, response);
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
            
            if (lenRsp<numDlen && lenRsp+eventSrc.BytesAvailable>=numDlen) || ...
                (lenRsp>=numDlen && eventSrc.BytesAvailable>=obj.BytesToRead)
                
                bytesRead = eventSrc.BytesAvailable;
                
                obj.Response(end+1:end+bytesRead) = fread(eventSrc, bytesRead);
                
                assembleResponse(obj);
            end
        end
        
       
        
        function processResponse(obj, response)
            err = MException('checkValidityResponse:InvalidResponse',...
               'Valid response not received');
           
           response
           
            [valid, ack, data, code] = decodeResponse(obj, response);
            
            if ack==1
                idx = indexOfResponseSequence(obj, code);
            else
                idx = code;
            end
            
            
            action = decodeAction(obj, ack, idx);

            if (~valid || strcmp(action , 'notfound'))
                if ~isempty(idx)
                    obj.SequenceList.response{idx(1)} = obj.ResponseError;
                    return
                else
                    error('Received response is not valid')
                    
                
                end
            end

            [result2, out] = decodeResponseData(obj, data, action);
            
            if result2 && ack
                obj.SequenceList.response{idx(1)} = out;
            elseif ack
                obj.SequenceList.response{idx(1)} = obj.ResponseError;
            elseif ~result2 %When response is asynchronous & result is 0
                error('Received asynchronous response is invalid');
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
               error(['Data being sent through the Client Command Packet is ',...
                   'of incorrect size according to the Bluetooth API']);
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
            err = MException('readResponse:timeout', 'Response Timeout');
            
            if responseexpected
                idx = indexOfResponseSequence(obj, seq);
                
                 t = cputime;
                 
                while (isinf(obj.SequenceList.response{idx}))%&&~iscell(obj.SequenceList.response{idx})
                    if cputime-t>responseTimeout
                        throwAsCaller(err);
                    end
                    
                    idx = indexOfResponseSequence(obj, seq);
                end
                
                if idx(1)<=length(obj.SequenceList.seq)
                    response = obj.SequenceList.response{idx(1)};

                    obj.SequenceList.response{idx(1)} = [];
                    obj.SequenceList.action{idx(1)} = [];
                    obj.SequenceList.seq(idx(1)) = [];
                    
                    % remove empty arrays in cell arrays
                    obj.SequenceList.action = obj.SequenceList.action(~cellfun(@isempty, obj.SequenceList.action));
                    obj.SequenceList.response = obj.SequenceList.response(~cellfun(@isempty, obj.SequenceList.response));
                    
                else
                    response = obj.ResponseError;
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
                    dlen = cmdFromByte(obj, dlenmsb, dlenlsb);
                    
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
%                     throw(err);
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
%                     throw(err)
%                 end
% 
%                 
%                 [result2, varagout] = decodeResponseData(obj, data, action);
%                 
%                 if ~result1 || ~result2
%                     throw(err)
%                 end
%                 
%             catch
%                 throw(err)
%             end
            
        end
       
        function delete(obj)
            disconnect(obj);
         end

        function [responseexpected, seq] = sendCmd(obj, action, varargin)
            
            %Check if connection open
            %Other checking
            
            [cmd, responseexpected, seq] = createCommand(obj, action, varargin{:});
            fwrite(obj.Bt, cmd);
            cmd
            
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
                
%                 result = ping(obj);
%                 if ~result
%                     error('Device:Invalild', ...
%                     'Unable to connect to device. Please check that the device name is correct and the device is discoverable');
%                 end
            
            catch
                err = MException('Device:Invalild', ...
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
    
>>>>>>> origin/Hydra:models/sphero/+sphero/+internal/BluetoothApi.m
end