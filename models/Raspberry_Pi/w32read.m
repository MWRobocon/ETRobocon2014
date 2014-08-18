classdef w32read < matlab.System & matlab.system.mixin.Propagates
% MATLAB System Object for read w32serial communication
%
% NOTE: You should always write once before reading.

    
    properties (Hidden)
       SerialObj; 
    end

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
          numIn = 0;
       end
   
       function numOut = getNumOutputsImpl(~)
          numOut = 1;
       end
              
       function setupImpl(obj)
            obj.COMObj = evalin('base',obj.COMObj);
       end
      
       function msg = stepImpl(obj)         
           % The message is framed as follows:
           %    [ LENGTH 0 MAILBOX DATA ]
           % Hence, +3 for the first 3 elements.
           message_length = obj.DataSize*obj.DataLength + 3;
           try
                message = fread(obj.COMObj,message_length);
           catch
                message = zeros(message_length,1);
                message(3) = obj.Mailbox;
           end
           
           if message(3) ~= obj.Mailbox
               error('Wrong Mailbox.')
           end

           % Temporary cast to uint8
           msg = uint8(message(4:end));
  
       end

       
       function s1 = getOutputSizeImpl(obj)
           s1 = obj.DataSize*obj.DataLength;
       end 
       
       
        function d1 = getOutputDataTypeImpl(obj)
            d1 = obj.DataType;
        end

        function c1 = isOutputComplexImpl(~)
            c1 = false;
        end

        function c1 = isOutputFixedSizeImpl(~)
            c1 = true;
        end
    end

end

