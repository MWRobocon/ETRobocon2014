currfolder = cd;

if ~strcmp(currfolder(end-7:end), 'examples')
    cd examples
end

files = ls('sphero*');
for i=1:size(files, 1)
    publish(files(i, :), 'evalCode', false, 'catchError', false, 'showCode', true);
end