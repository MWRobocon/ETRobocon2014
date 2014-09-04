function obj = w32serial(portname, varargin)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% �{�t�@�C���i�v���O�����j�𗘗p�������Ƃɂ�钼�ڂ��邢��
%% �ԐړI�ȑ��Q�Ɋւ��āA�T�C�o�l�b�g�V�X�e���͂���������
%% �ӔC�𕉂����˂܂��B
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% w32serial �N���X�R���X�g���N�^

if ~ispc
  error('This command is for the PC(Windows) version only.')
end

if nargin == 0
    error('You must provide a port name as the first input.(For example, "COM1")')
elseif ~isa(portname,'char')
  error('The first input argument must be a port name.(For example, "COM1")');
end



obj.PortName = portname;
%Global defaults
obj.BaudRate = 9600;
obj.Parity = 'NOPARITY';
obj.DataBits = 8;
obj.StopBits = 1;
obj.FileID = -1;
obj.InputBufferSize = 512;
obj.CurrentState = 'Closed';

obj = class(obj,'w32serial');
% Take care of any parameters set at the command line
obj = set(obj,varargin{:});
%aviobj.FileHandle = avi('open',filename);
% elseif nargin == 1 & isa(obj,'w32serial')
%     data = a;
% elseif nargin == 2 & ischar(label) & isnumeric(a)
%     data.x = a(2, :);
%     data.y = a(1, :);
%     data.label = label;
%     data = class(data,'sigbdata');
% else
%     error('Paremeter error!!!')
% end
