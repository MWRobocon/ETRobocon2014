classdef tRawNXTDataProcessor < matlab.unittest.TestCase
    methods(Test)
        function processesOneByteDataInOneShot(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [data,dataLen] = p.process(uint8([2 0 11 73]),uint8(4));
            testCase.assertEqual(dataLen,uint8(1),'Unexpected returned dataLen when processing [2 0 11 73] in one-shot');
            testCase.verifyEqual(data(1:dataLen),uint8(73),'Unexpected returned data when when processing [2 0 11 73] in one-shot');
        end
        
        function processesThreeByteDataInOneShot(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [data,dataLen] = p.process(uint8([4 0 11 99 88 77]),uint8(6));
            testCase.assertEqual(dataLen,uint8(3),'Unexpected returned dataLen when processing [2 0 11 73] in one-shot');
            testCase.verifyEqual(data(1:dataLen),uint8([99 88 77]),'Unexpected returned data when when processing [2 0 11 73] in one-shot');
        end
        
        function processesThreeByteDataInTwoSteps(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [~,dataLen] = p.process(uint8([4 0 11 99]),uint8(4));
            testCase.assertEqual(dataLen,uint8(0),'Unexpected returned dataLen when processing packet subset [4 0 11 99]');
            
            [data,dataLen] = p.process(uint8([88 77]),uint8(2));
            testCase.assertEqual(dataLen,uint8(3),'Unexpected returned dataLen when processing [4 0 11 99 88 77] in two steps');
            testCase.verifyEqual(data(1:dataLen),uint8([99 88 77]),'Unexpected returned data when processing [4 0 11 99 88 77] in two steps');
        end
        
        function handlesMailboxOnlyPacketInOneShot(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [~,dataLen] = p.process(uint8([1 0 6]),uint8(3));
            testCase.verifyEqual(dataLen,uint8(0),'Unexpected returned dataLen when processing mailbox only packet [1 0 6] in one-shot');
            testCase.verifyEqual(p.state,comms.RawNXTDataProcessorState.PACKET_SIZE_BYTE,...
                                 'Data processor is in unexpected state after processing mailbox only packet [1 0 6] in one-shot');
        end
        
        function handlesTwoPacketsInOneShot(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [data,dataLen] = p.process(uint8([3 0 11 13 14 2 0 11 46]),uint8(9));
            testCase.assertEqual(dataLen,uint8(3),'Unexpected returned dataLen when processing two-packets [3 0 11 13 14 2 0 11 46] in one-shot');
            testCase.verifyEqual(data(1:dataLen),uint8([13 14 46]),'Unexpected returned data when processing two-packets [3 0 11 13 14 2 0 11 46] in one-shot');
        end
        
        function usesActualLengthInput(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [~,dataLen] = p.process(uint8([3 0 11 13 14]),uint8(4));
            testCase.assertEqual(dataLen,uint8(0),'Unexpected returned dataLen when processing 4 actualBytes of [3 0 11 13 14] in one-shot');
            
            [data,dataLen] = p.process(uint8(63),uint8(1));
            testCase.assertEqual(dataLen,uint8(2),'Unexpected returned dataLen after fully processing [3 0 11 13 63] in two steps');
            testCase.verifyEqual(data(1:dataLen),uint8([13 63]),'Unexpected returned data after fully processing [3 0 11 13 63] in two steps');
        end
        
        function partiallyOverrunsBuffer(testCase)
            p = comms.RawNXTDataProcessor(uint8(2));
            [data,dataLen] = p.process(uint8([4 0 17 32 75 19]),uint8(6));
            testCase.assertEqual(dataLen,uint8(2),'Unexpected returned dataLen for overrun [4 0 17 32 75 19] in two element buffer');
            testCase.verifyEqual(data,uint8([32 75]),'Unexpected returned data for overrun [4 0 17 32 75 19] in two element buffer');
            testCase.verifyTrue(p.numOverruns > 0,'Data processor object does not indicate overrun for overrun [4 0 17 32 75 19] in two element buffer');
        end
        
        function fullyOverrunsBuffer(testCase)
            p = comms.RawNXTDataProcessor(uint8(1));
            [data,dataLen] = p.process(uint8([2 0 17 3 2 0 19 4]),uint8(8));
            testCase.assertEqual(dataLen,uint8(1),'Unexpected returned dataLen for overrun [2 0 17 3 2 0 19 4] in one element buffer');
            testCase.verifyEqual(data,uint8(3),'Unexpected returned data for overrun [2 0 17 3 2 0 19 4] in one element buffer');
            testCase.verifyTrue(p.numOverruns > 0,'Data processor object does not indicate overrun for overrun [2 0 17 3 2 0 19 4] in one element buffer');
            
            [data,dataLen] = p.process(uint8([2 0 11 73]),uint8(4));
            testCase.assertEqual(dataLen,uint8(1),'Unexpected returned dataLen when processing [2 0 11 73] after full overrun');
            testCase.verifyEqual(data(1:dataLen),uint8(73),'Unexpected returned data when when processing [2 0 11 73] after full overrun');
        end
        
        function handlesMissingSynchroByte(testCase)
            p = comms.RawNXTDataProcessor(uint8(10));
            [data,dataLen] = p.process(uint8([2 4 0 11 99 88 77]),uint8(7));
            testCase.assertEqual(dataLen,uint8(3),'Unexpected returned dataLen when processing missing synchro byte [2 4 0 11 99 88 77] in one-shot');
            testCase.verifyEqual(data(1:dataLen),uint8([99 88 77]),'Unexpected returned data when processing missing synchro byte [2 4 0 11 99 88 77] in one-shot');
        end
    end
end