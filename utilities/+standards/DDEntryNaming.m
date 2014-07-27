% DDContent
% Check the naming of data dictionary entries

classdef DDEntryNaming < standards.Standard
    properties(Access = private)
        ddCell = {};
        reportStruct;
    end
    
    methods
        function this = DDEntryNaming(aRepositoryRoot)
            this = this@standards.Standard(aRepositoryRoot);
        end
        
        function r = checkStandard(this)
            this.findAllDD();
            
            for k = 1:numel(this.ddCell)
                this.checkDDEntryNaming(this.ddCell{k});
            end
            
            r = this.reportStruct;
        end
    end
    
    methods(Access = private)
        function findAllDD(this)
            this.findAllDDImpl(this.repositoryRoot);
            this.reportStruct.foundDDCell = this.ddCell;
        end
        
        function findAllDDImpl(this,aDirName)
            dirStruct = dir(aDirName);
            
            for k = 1:numel(dirStruct)
                d = dirStruct(k);
                if(d.isdir)
                    if(~any(strcmp(d.name,{'.','..'})))
                        this.findAllDDImpl(fullfile(aDirName,d.name));
                    end
                else
                    [~,~,ext] = fileparts(d.name);
                    if(strcmp(ext,'.sldd'))
                        this.ddCell{end+1,1} = fullfile(aDirName,d.name);
                    end
                end
            end
        end 
        
        function checkDDEntryNaming(this,ddFilePath)
            fprintf('Checking Entry Naming of %s\n',ddFilePath);
            
            ci.ddFilePath = ddFilePath;
            ci.camelCaseValid = {};
            ci.camelCaseViolation = {};
            ci.mixedCaseValid = {};
            ci.mixedCaseViolation = {};
            ci.allCapsValid = {};
            ci.allCapsViolation = {};
            
            dd = Simulink.data.dictionary.open(ddFilePath);
            closeDD = onCleanup(@() close(dd));
            
            s = dd.getSection('Design Data');
            entryNameCell = this.getDDEntryNames(s);
            ci.entryNameCell = entryNameCell;
            
            for k = 1:numel(entryNameCell)
                e = s.getEntry(entryNameCell{k});
                r = this.checkEntry(e);
                ci.(r){end+1} = e.Name;
            end
            
            delete(closeDD);
            this.addCheckInfoToReport(ci);
            fprintf('\n');
        end
        
        function entryNameCell = getDDEntryNames(~,sectionObj)
            tempMatPath = [tempname '.mat'];
            sectionObj.exportToFile(tempMatPath);
            l = load(tempMatPath);
            entryNameCell = fieldnames(l);
        end
            
        
        function result = checkEntry(this,entryObj)
            if(this.isEntryCamelCase(entryObj))
                result = this.doCamelCaseCheck(entryObj);
            elseif(this.isEntryMixedCase(entryObj))
                result = this.doMixedCaseCheck(entryObj);
            elseif(this.isEntryAllCaps(entryObj))
                result = this.doAllCapsCheck(entryObj);
            else
                result = this.reportUnhandledEntry(entryObj);
            end
        end
        
        function tf = isEntryCamelCase(~,entryObj)
            val = entryObj.Value;
            
            tf = isnumeric(val) || ...
                 isa(val,'Simulink.Signal') || ...
                 isa(val,'Simulink.Parameter') || ...
                 isstruct(val);
        end
        
        function r = doCamelCaseCheck(~,entryObj)
            % Don't allow
            % - First character be uppercase
            % - Character proceeding "_" be uppercase
            invalid = '(^[A-Z])|(_[A-Z])';
            matches = regexp(entryObj.Name,invalid,'once');
            
            if(~isempty(matches))
                fprintf('camelCase Violation: %s (%s)\n',entryObj.Name,class(entryObj.Value));
                r = 'camelCaseViolation';
            else
                r = 'camelCaseValid';
            end
        end
        
        function tf = isEntryMixedCase(~,entryObj)
            val = entryObj.Value;
            tf = isa(val,'Simulink.Bus') || ...
                 isa(val,'Simulink.Variant');
        end
        
        function r = doMixedCaseCheck(~,entryObj)
            % Don't allow
            % - First character be lowercase
            % - Character proceeding "_" be lowercase
            invalid = '(^[a-z])|(_[a-z])';
            matches = regexp(entryObj.Name,invalid,'once');
            
            if(~isempty(matches))
                fprintf('MixedCase Violation: %s (%s)\n',entryObj.Name,class(entryObj.Value));
                r = 'mixedCaseViolation';
            else
                r = 'mixedCaseValid';
            end
        end
        
        function tf = isEntryAllCaps(~,entryObj)
            tf = false;
        end
        
        function r = doAllCapsCheck(~,entryObj)
            % Don't allow
            % - lowercase characters
            invalid = '[a-z]';
            matches = regexp(entryObj.Name,invalid,'once');
            
            if(~isempty(matches))
                fprintf('ALL_CAPS Violation: %s (%s)\n',entryObj.Name,class(entryObj.Value));
                r = 'allCapsViolation';
            else
                r = 'allCapsValid';
            end
        end
        
        function r = reportUnhandledEntry(~,entryObj)
            fprintf('Unhandled: %s (%s)\n',entryObj.Name,class(entryObj.Value));
            r = 'unhandledEntry';
        end
                
        function addCheckInfoToReport(this,aCheckInfo)
            if(isfield(this.reportStruct,'checkInfo'))
                this.reportStruct.checkInfo(end+1) = aCheckInfo;
            else
                this.reportStruct.checkInfo = aCheckInfo;
            end
        end
    end
end