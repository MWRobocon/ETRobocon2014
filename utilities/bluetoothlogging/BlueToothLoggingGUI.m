function BlueToothLoggingGUI(modelname)
if (nargin < 1), modelname=bdroot; end;


FS = 14;

handles.ModelName = modelname;

handles.LoggedSignals       = {};
handles.BlueToothSignals    = {};
handles.LoggedSignalHandles = [];
handles.BTSignalHandles     = [];
handles.run_number          = [];
handles.PERIOD              = 0.01;
handles.WhilePause          = 0.0002;

fh = figure('Visible','on','Name','BlueToothControl');
%    'Position',[2360,200,750,750],...
set(fh,'MenuBar','none')
pos_orig = get(fh,'Position');
Width = 750; Height = 500;
set(fh,'Position',[pos_orig(1), pos_orig(2)+pos_orig(4)-Height, Width, Height]);
%set(fh,'Position',[2360,300, Width, Height]);
set(fh,'units','normalized');

listwidth = 0.25;
emptywidth = 0.025;
buttonwidth = 0.15;

handles.textaxis = axes('parent',fh,...
    'units','normalized',...
    'position',[0 0 1 1],...
    'visible','off'); 

handles.listboxLeft = uicontrol('Style','listbox',... 
    'units','normalized',... 
    'position',[emptywidth .1 listwidth .8],... 
    'Max',2,...
    'string',handles.LoggedSignals);

handles.listboxRight = uicontrol('Style','listbox',... 
    'units','normalized',... 
    'Max',2,...
    'position',[(listwidth+buttonwidth+3*emptywidth) .1 listwidth .8]); 

handles.RefreshSignalsButton = uicontrol('Style','pushbutton',... 
    'units','normalized',... 
    'position',[(listwidth+2*emptywidth) .8 buttonwidth .1],... 
    'string','Refresh Signals',... 
    'callback',@RefreshSignals); 

handles.ToBlueToothButton = uicontrol('Style','pushbutton',... 
    'units','normalized',... 
    'position',[(listwidth+2*emptywidth) .6 buttonwidth .1],... 
    'string','--->',... 
    'callback',@(s,e) TransferToBlueTooth(s,e)); 

handles.RemoveBlueToothButton = uicontrol('Style','pushbutton',... 
    'units','normalized',... 
    'position',[(listwidth+2*emptywidth) .4 buttonwidth .1],... 
    'string','<---',... 
    'callback',@(s,e) RemoveBlueTooth(s,e)); 

handles.CommEdit = uicontrol(fh,'Style','edit',...
    'String','13',...
    'FontSize',FS,...
    'units','normalized',...
    'Position',[(2*listwidth+buttonwidth+4*emptywidth) .6 0.225 .1]);

handles.CommText = text(.8,.725,'COM:',...
    'unit','normalized',...
    'HorizontalAlignment','center',...
    'FontSize',FS);

handles.BuildButton = uicontrol('Style','pushbutton',... 
    'units','normalized',... 
    'position',[(2*listwidth+buttonwidth+4*emptywidth) .4 0.225 .1],... 
    'string','Build/Download',...
    'callback', @BuildandDownload); 

handles.StartButton = uicontrol('Style','pushbutton',... 
    'units','normalized',... 
    'position',[(2*listwidth+buttonwidth+4*emptywidth) .25 0.225 .1],... 
    'string','Start Acquisition',...
    'callback', @StartStop); 


setappdata(fh,'handles',handles) 
end

%%%%%%%
function TransferToBlueTooth(hObject,~)
fh = get(hObject,'Parent');
handles = getappdata(fh,'handles');

LoggedSignals      = handles.LoggedSignals;
listboxLeft        = handles.listboxLeft;
listboxRight       = handles.listboxRight;
BlueToothSignals   = handles.BlueToothSignals;
LoggedSignalHandle = handles.LoggedSignalHandles;
BTSignalHandles    = handles.BTSignalHandles;

value_array        = get(listboxLeft,'Value');


for index = 1:length(value_array)
    value = value_array(index);
    signalname   = LoggedSignals{value};
    signalhandle = LoggedSignalHandle(value);

    % check to see if the signal is already logged
    alreadythere = strcmp(BlueToothSignals,signalname);
    
    nCurrent = length(BTSignalHandles);
    if (nCurrent==15)
        warning('Blue Tooth limited to 15 signals')
        return
    end
    
    if sum(alreadythere)==0
        % we need to add this signal
        BlueToothSignals{end+1} = signalname;
        BTSignalHandles(end+1)  = signalhandle;
        set(listboxRight,'String',BlueToothSignals);
    else
        % signal is already there
        % don't do anything
    end
    
end


% save the handles
handles.BlueToothSignals = BlueToothSignals;
handles.BTSignalHandles  = BTSignalHandles; 
setappdata(fh,'handles',handles) ;
end

%%%%%
function RemoveBlueTooth(hObject,~)
fh = get(hObject,'Parent');
handles = getappdata(fh,'handles');

listboxRight     = handles.listboxRight;
BlueToothSignals = handles.BlueToothSignals;
BTSignalHandles  = handles.BTSignalHandles;

value_array = get(listboxRight,'Value');

BlueToothSignals(value_array) = [];
BTSignalHandles(value_array)  = [];

set(listboxRight,'Value',1)
set(listboxRight,'String',BlueToothSignals);

% save the handles
handles.BlueToothSignals = BlueToothSignals;
handles.BTSignalHandles  = BTSignalHandles; 
setappdata(fh,'handles',handles) ;
end

function RefreshSignals(hObject,~)
fh = get(hObject,'Parent');
handles = getappdata(fh,'handles');
listboxLeft      = handles.listboxLeft;
sys = handles.ModelName;
% Find all signal lines in the system
lines = find_system(sys,'FindAll','on','Type','line');

% Narrow down to all lines whose 'DataLogging == 1'
lines_logging = lines(find(cell2mat(get(lines,'DataLogging'))));

lines_logging_name = get(lines_logging,'Name');
empty_signal_indices = find(strcmp(lines_logging_name,''));
lines_logging_name(empty_signal_indices) = cellstr(strcat(repmat('Noname',length(empty_signal_indices),1),num2str((1:length(empty_signal_indices))')));

% store lines in handles
handles.LoggedSignals = lines_logging_name;
handles.LoggedSignalHandles = lines_logging;
set(listboxLeft,'String',handles.LoggedSignals);

setappdata(fh,'handles',handles) ;
end

function BuildandDownload(hObject,~)
fh = get(hObject,'Parent');
handles = getappdata(fh,'handles');
BTSignalHandles = handles.BTSignalHandles;
sys             = handles.ModelName;

% % get compiled port dimensions at beginning of each line
% eval([sys '([],[],[],''compile'')'])
% line_dimensions  = cell(1,length(BTSignalHandles));
% data_type_single = zeros(1,length(BTSignalHandles));
% for i = 1:length(BTSignalHandles)
%     line_dimensions{i}  = get(get(BTSignalHandles(i),'SrcPortHandle'),'CompiledPortDimensions');
%     data_type_single(i) = strcmp('single',get(get(BTSignalHandles(i),'SrcPortHandle'),'CompiledPortDataType'));
%     if ~isequal(line_dimensions{i},[1 1])
%         eval([sys '([],[],[],''term'')'])
%         error('Can only handle scalar signals at this point')
%     end
% end
% eval([sys '([],[],[],''term'')'])


% add a data store memory block
h1 = add_block('Simulink/Signal Routing/Data Store Memory',[sys '/DSM'],...
               'Dimensions',['[' num2str(length(BTSignalHandles)) ']'],...
               'InitialValue',['[' num2str(zeros(1,length(BTSignalHandles))) ']'],...
               'ShowName','off');

% add a data store write block onto each signal line
lines_added = [];
dsw_handles = zeros(1,length(BTSignalHandles));
dtc_handles = zeros(1,length(BTSignalHandles));
for i = 1:length(BTSignalHandles)
    
    dsw_handles(i) = add_block('Simulink/Signal Routing/Data Store Write',[get_param(BTSignalHandles(i),'Parent') '/DSW1'],...
                               'MakeNameUnique','on',...
                               'DataStoreElements',['A(' num2str(i) ')'],...
                               'ShowName','off');
    
    position = get(get(BTSignalHandles(i),'SrcPortHandle'),'Position');
    dsw_porthandles = get_param(dsw_handles(i),'PortHandles');
    
%     if data_type_single(i)
%         % position block
%         set_param(dsw_handles(i),'Position',[position(1)+20 position(2)-30 position(1)+40 position(2)-10]);
%         
%         % line is already single. no need for data type conversion
%         lines_added(end+1) = add_line(get_param(BTSignalHandles(i),'Parent'),get_param(BTSignalHandles(i),'SrcPortHandle'),dsw_porthandles.Inport,'autorouting','on');
%         
%     else
        % add data type conversion block
        dtc_handles(i) = add_block('Simulink/Signal Attributes/Data Type Conversion',[get_param(BTSignalHandles(i),'Parent') '/DTC1'],...
                               'MakeNameUnique','on',...
                               'OutDataTypeStr','single',...
                               'ShowName','off');
        
        % position blocks
        set_param(dtc_handles(i),'Position',[position(1)+20 position(2)-30 position(1)+60 position(2)-10]);
        set_param(dsw_handles(i),'Position',[position(1)+80 position(2)-30 position(1)+100 position(2)-10]);
        
        % add lines from source to dtc and dtc to dsw
        dtc_porthandles = get(dtc_handles(i),'PortHandles');
        lines_added(end+1) = add_line(get_param(BTSignalHandles(i),'Parent'),get_param(BTSignalHandles(i),'SrcPortHandle'),dtc_porthandles.Inport,'autorouting','on');
        lines_added(end+1) = add_line(get_param(BTSignalHandles(i),'Parent'),dtc_porthandles.Outport,dsw_porthandles.Inport,'autorouting','on');
%         
%     end

end

% add a data store read block, a lego nxt bluetooth block and connect them
h2 = add_block('Simulink/Signal Routing/Data Store Read',[sys '/DSR'],...
               'ShowName','off','SampleTime',num2str(handles.PERIOD));
h2_porthandles = get(h2,'PortHandles');

h3 = add_block('legonxtlib/Send via Bluetooth(R) Connection',[sys '/SEND'],...
               'ShowName','off');
h3_porthandles = get(h3,'PortHandles');
lines_added(end+1) = add_line(sys,h2_porthandles.Outport,h3_porthandles.Inport,'autorouting','on');


blocks_added = [h1 h2 h3 dsw_handles dtc_handles];

rtwbuild(sys)



% store lines/blocks added in handles
handles.ModelLinesAdded  = lines_added;
handles.ModelBlocksAdded = blocks_added;
save AddedBlocksLines.mat lines_added blocks_added;


setappdata(fh,'handles',handles) ;

end


function StartStop(hObject,~)
fh = get(hObject,'Parent');
handles = getappdata(fh,'handles');

StartButton = handles.StartButton;

buttonstring = get(StartButton,'String');
startflag = strcmp(buttonstring,'Start Acquisition');
handles.StartFlag = startflag;
setappdata(fh,'handles',handles) ;

if (startflag)
    %set to stop
    set(StartButton,'String','Stop Acquisition');
    disp('tried to set to stop')
    pause(1)
    startWhileLoop(fh)
else
    %set to start
    set(StartButton,'String','Start Acquisition');
end


end

function startWhileLoop(fh)
handles = getappdata(fh,'handles');

BTSignalHandles    = handles.BTSignalHandles;
BlueToothSignals   = handles.BlueToothSignals;
run_number         = handles.run_number;
PERIOD             = handles.PERIOD;

nSignals = length(BTSignalHandles);

% need signal names structure lines_logging_name
% need array of added block and line handles blocks_added and lines_added
% needs an internal variable run_number initialized to [] when GUI starts
% will need a variable to keep track of start/stop toggle capability
% variable below will need to come from edit boxes
commnumber_str = get(handles.CommEdit,'String');

if (length(commnumber_str)==4)
    port = upper(commnumber_str);
elseif (length(commnumber_str)==1)
    port = ['COM', commnumber_str];
elseif (length(commnumber_str)==2)
    port = ['COM', commnumber_str];
else
    warning('COM edit should be COMx or x')
    return
end




PACKET_SIZE = 3 + 4*nSignals;  % adjust to the amount of data sent

try
    s = w32serial(port, 'BaudRate', 9600)
    fopen(s);
catch
    fclose(s);
    disp(['Failed to connect with: ' port]);
end

j = 1;
data = zeros(nSignals,1);

disp('starting acquisition')
while handles.StartFlag
    % read the packet
    packet = fread(s, PACKET_SIZE, 'uint8');

    if length(packet) == PACKET_SIZE
        k = 4;
        for i = 1:nSignals
            data(i,j) = typecast(uint8(packet(k:k+3)),'single');
            k = k+4;
        end
    end
    
    j = j+1;
    pause(handles.WhilePause)
    handles = getappdata(fh,'handles');

end
fclose(s);
disp('Acquisition completed');

% run_number must be initialized to [] at gui initialization
if isempty(run_number)
    run_number = 1;
else
    run_number = run_number + 1;
end

% store data in handles
handles.run_number = run_number;
setappdata(fh,'handles',handles) ;


% remove the lines we added to the model
LinesAdded  = handles.ModelLinesAdded;
BlocksAdded = handles.ModelBlocksAdded;
delete(BlocksAdded)
delete_line(LinesAdded)

handles.ModelLinesAdded  = [];
handles.ModelBlocksAdded = [];

%% filter data
% for i = 1:nSignals
%     d = data(i,:);
% 
%     d(abs(d)>1e4)=nan;
%     data(i,:) = d;
% end


% add data to SDI and view it
runID = Simulink.sdi.createRun(['Run ' num2str(run_number)]);
t = PERIOD * (0:(size(data,2)-1));
for i = 1:size(data,1)
    timeseries_i = timeseries(data(i,:),t,'Name',BlueToothSignals{i});
    signalIDs = Simulink.sdi.addToRun(runID,'vars',timeseries_i);
end

Simulink.sdi.view


setappdata(fh,'handles',handles) ;
end

