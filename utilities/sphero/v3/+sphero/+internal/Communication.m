classdef (Abstract) Communication<handle
    %SPHEROCOMMUNICATION Summary of this class goes here
    %   Detailed explanation goes here
    
%    properties
%       ApiInfo 
%    end
   
    methods 
%         [did, cid, dlen] = obtainId(action)
        
%         cmd = createCommand(action, varargin)
        [cmd, respond, seq] = createCommand(obj, action, varargin);
         [valid, ack, data, code] = decodeResponse(obj, response);
%         varagout = decodeResponse(response)
%         
    end
    methods (Access = private)
%         checkValidityResponse(varargin)
    end
    
end

