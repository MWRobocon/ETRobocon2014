classdef w32write < matlab.System
% MATLAB System Object for writing w32serial communication

    properties (Nontunable)
        % COMObj w32serial Object Name
        COMObj = 's';
        % DataType Data Type
        DataType = 'uint8';
    end
    
    properties (PositiveInteger)
       % DataSize Data Type Size (Bytes)
       DataSize = 1;
       % DataLength Message Size
       DataLength = 1;
       Mailbox = 1;    
    end

    methods (Access=protected)
       
       function numIn = getNumInputsImpl(~)
          numIn = 1;
       end
   
       function numOut = getNumOutputsImpl(~)
          numOut = 0;
       end
        
        
       function setupImpl(obj,~)
            obj.COMObj = evalin('base',obj.COMObj);
       end
      
       function stepImpl(obj,data)      
           message_size = obj.DataSize*obj.DataLength + 1;
           message = [message_size 0 obj.Mailbox data'];
           fwrite(obj.COMObj,message,obj.DataType,length(message));
       end
       
    end
end

