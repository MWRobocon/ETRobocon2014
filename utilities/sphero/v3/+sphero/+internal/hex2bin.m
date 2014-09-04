function [ bin ] = hex2bin(hex)
%HEX2BIN Summary of this function goes here
%   Detailed explanation goes here

for i=1:length(hex)
    switch hex
        case'f'
            bin((i*4)-3:i*4)=[1 1 1 1];
        case 'e'
            bin((i*4)-3:i*4)=[1 1 1 0];
        case 'd'
            bin((i*4)-3:i*4)=[1 1 0 1];
        case 'c'
            bin((i*4)-3:i*4)=[1 1 0 0];
        case 'b'
            bin((i*4)-3:i*4)=[1 0 1 1];
        case 'a'
            bin((i*4)-3:i*4)=[1 0 1 0];
        case '9'
            bin((i*4)-3:i*4)=[1 0 0 1];
        case '8'
            bin((i*4)-3:i*4)=[1 0 0 0];
        case '7'
            bin((i*4)-3:i*4)=[0 1 1 1];
        case '6'
            bin((i*4)-3:i*4)=[0 1 1 0];
        case '5'
            bin((i*4)-3:i*4)=[0 1 0 1];
        case '4'
            bin((i*4)-3:i*4)=[0 1 0 0];
        case '3'
            bin((i*4)-3:i*4)=[0 0 1 1];
        case '2'
            bin((i*4)-3:i*4)=[0 0 1 0];
        case '1'
            bin((i*4)-3:i*4)=[0 0 0 1];
        case '0'
            bin((i*4)-3:i*4)=[0 0 0 0];
        otherwise
            bin((i*4)-3:i*4) = [];
        end
end  
end

