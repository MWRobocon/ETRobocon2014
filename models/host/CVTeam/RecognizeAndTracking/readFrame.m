 function frame = readFrame(obj)
%         frame = getsnapshot(obj.videoObj);
        frame = obj.videoObj.step;
end