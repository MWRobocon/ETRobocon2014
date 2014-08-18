% Class processing raw NXT bluetooth packets into actual transmitted data.
% Takes care of stripping out header 

classdef RawNXTDataProcessor < handle
    properties(SetAccess = private, GetAccess = public)
        state = comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE;
        dataBuffer;
        currentDataSize = uint8(0);
        currentDataBytesReceived = uint8(0);
        numOverruns = 0;
    end
    
    methods
        function this = RawNXTDataProcessor(aBufferLength)
            this.dataBuffer = zeros([1,aBufferLength],'uint8');
        end
        
        function [data,dataLen] = process(this,byteArray,actualLength)
            data = this.dataBuffer;
            dataLen = uint8(0);
            
            assert(actualLength <= uint8(numel(byteArray)));
            for k = 1:actualLength
                switch(this.state)
                    case comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE
                        this.processPacketSizeByte(byteArray(k));
                    case comms.RawNXTDataProcessorState.SYNCHRO_BYTE
                        this.processSynchroByte(byteArray(k));
                    case comms.RawNXTDataProcessorState.MAILBOX_BYTE
                        this.processMailboxByte(byteArray(k));
                    case comms.RawNXTDataProcessorState.PACKET_BYTES
                        this.currentDataBytesReceived = this.currentDataBytesReceived + 1;
                        
                        if(this.currentDataBytesReceived <= uint8(numel(this.dataBuffer)))
                            this.dataBuffer(this.currentDataBytesReceived) = byteArray(k);
                        else
                            this.numOverruns = this.numOverruns + 1;
                        end
                        
                        if(this.currentDataBytesReceived >= this.currentDataSize)
                            startIdx = dataLen + 1;
                            
                            if(startIdx <= uint8(numel(data)))
                                endIdx = dataLen + this.currentDataSize;
                                if(endIdx > uint8(numel(data)))
                                    this.numOverruns = this.numOverruns + 1;
                                    endIdx = uint8(numel(data));
                                end
                                bufferLen = 1 + (endIdx - startIdx);
                                dataLen = dataLen + bufferLen;
                                
                                data(startIdx:1:endIdx) = this.dataBuffer(1:bufferLen);
                            else
                                this.numOverruns = this.numOverruns + 1;
                            end
                            this.state = comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE;
                        end
                end
            end
        end
        
        function reset(this)
            this.state = comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE;
        end
    end
    
    methods(Access = private)
        function processPacketSizeByte(this,aByte)
            this.currentDataBytesReceived = uint8(0);
            this.currentDataSize = aByte - 1; % We will strip off the mailbox
            this.state = comms.RawNXTDataProcessorState.SYNCHRO_BYTE;
        end
        
        function processSynchroByte(this,aByte)
            if(aByte ~= uint8(0))
                % If we didn't get the synchroByte assume we got the packetSizeByte
                this.state = comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE;
                this.processPacketSizeByte(aByte);
            else
                this.state = comms.RawNXTDataProcessorState.MAILBOX_BYTE;
            end
        end
        
        function processMailboxByte(this,~)
            if(this.currentDataSize == 0)
                this.state = comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE;
            else
                this.state = comms.RawNXTDataProcessorState.PACKET_BYTES;
            end
        end
    end
end