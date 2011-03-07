unit CTSMain;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT �������
* ��Ԫ���ƣ�����Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע���õ�Ԫʵ���˵��� cvstrac.exe �ķ�����
* ����ƽ̨��PWindows Server 2003 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTSMain.pas,v 1.3 2005/09/16 02:16:14 zjy Exp $
* ���¼�¼��2003.11.15
*               �޸� cvstrac ���з�ʽ��ֻ����һ��ʵ��
*           2003.11.09
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, SvcMgr, Dialogs,
  CTConsts, CTUtils, ExtCtrls, CnCommon;

type
  TCVSTracService = class(TService)
    tmrBackup: TTimer;
    procedure ServiceStart(Sender: TService; var Started: Boolean);
    procedure ServiceStop(Sender: TService; var Stopped: Boolean);
    procedure ServiceCreate(Sender: TObject);
    procedure tmrBackupTimer(Sender: TObject);
  private
    { Private declarations }
    HProcess: THandle;
  public
    { Public declarations }
    function GetServiceController: TServiceController; override;
  end;

var
  CVSTracService: TCVSTracService;

implementation

{$R *.DFM}

uses
  IniFiles;

{$IFDEF DEBUG}
var
  LogFile: TFileStream;
{$ENDIF}

procedure Log(const Msg: string);
{$IFDEF DEBUG}
var
  Buff: string;
{$ENDIF}
begin
{$IFDEF DEBUG}
  Buff := Msg + #13#10;
  LogFile.Write(PChar(Buff)^, Length(Buff));
{$ENDIF}
end;

procedure ServiceController(CtrlCode: DWord); stdcall;
begin
  CVSTracService.Controller(CtrlCode);
end;

function DoExec(const FileName: string; WorkDir: string = ''): THandle;
var
  StartupInfo: TStartupInfo;
  ProcessInfo: TProcessInformation;
begin
  if WorkDir = '' then
    WorkDir := ExtractFilePath(ParamStr(0));
  FillChar(StartupInfo, SizeOf(StartupInfo), #0);
  StartupInfo.cb := SizeOf(StartupInfo);

  StartupInfo.dwFlags := STARTF_USESHOWWINDOW;
  StartupInfo.wShowWindow := SW_HIDE;
  if CreateProcess(nil, PChar(FileName), nil, nil, False, CREATE_NEW_CONSOLE or
    NORMAL_PRIORITY_CLASS, nil, PChar(WorkDir), StartupInfo, ProcessInfo) then
    Result := ProcessInfo.hProcess
  else
    Result := 0;
end;

function LongNameToShortName(const FileName: string): string;
var
  Buf: PChar;
  BufSize: Integer;
begin
  BufSize := GetShortPathName(PChar(FileName), nil, 0) + 1;
  GetMem(Buf, BufSize);
  try
    GetShortPathName(PChar(FileName), Buf, BufSize);
    Result := Buf;
  finally
    FreeMem(Buf);
  end;
end;

procedure TCVSTracService.ServiceCreate(Sender: TObject);
const
  csPath = 'PATH';
var
  AppDir: string;
  Path: string;
  R: Cardinal;
begin
  // �� Path ·���м��뵱ǰĿ¼��֧�� cvstrac ����ʱ�����ⲿ����
  AppDir := LongNameToShortName(ExtractFileDir(ParamStr(0)));
  R := GetEnvironmentVariable(PChar(csPath), nil, 0);
  SetLength(Path, R);
  GetEnvironmentVariable(PChar(csPath), PChar(Path), R);
  SetEnvironmentVariable(csPath, PChar(AppDir + ';' + Path));
  tmrBackupTimer(nil);
end;

function TCVSTracService.GetServiceController: TServiceController;
begin
  Result := ServiceController;
end;

procedure TCVSTracService.ServiceStart(Sender: TService;
  var Started: Boolean);
var
  FmtStr: string;
  FileName: string;
  Settings: TSettingsInfo;
  ExitCode: Cardinal;
begin
  Started := False;

{$IFDEF DEBUG}
  Log('FmtStr: ' + FmtStr);
{$ENDIF}
  Settings := LoadSettingsFromIni;
  FmtStr := '"' + ExtractFilePath(ParamStr(0)) + Settings.ExeName + '" server %d "%s"';
  FileName := Format(FmtStr, [Settings.Port, Settings.DBPath]);
{$IFDEF DEBUG}
  Log(Format('Port: %d, Home: %s', [Settings.Port, Settings.DBPath]));
  Log('FileName: ' + FileName);
{$ENDIF}
  HProcess := DoExec(FileName, ExtractFilePath(ParamStr(0)));
  if HProcess = 0 then
  begin
  {$IFDEF DEBUG}
    Log('CreateProcess Error: ' + FileName);
  {$ENDIF}
    LogMessage('CreateProcess Error: ' + FileName);
  end;

  if HProcess <> 0 then
  begin
    // ��ʱ 1 ��ȴ� CVSTrac �����ȶ������������Զ��رգ�
    Sleep(1000);
    GetExitCodeProcess(HProcess, ExitCode);
    if ExitCode = STILL_ACTIVE then
      Started := True
    else
    begin
    {$IFDEF DEBUG}
      Log('Start CVSTrac Error: ' + FileName);
    {$ENDIF}
      LogMessage('Start CVSTrac Error: ' + FileName);
    end;
  end;
end;

procedure TCVSTracService.ServiceStop(Sender: TService;
  var Stopped: Boolean);
begin
  if not TerminateProcess(HProcess, 0) then
  begin
  {$IFDEF DEBUG}
    Log('TerminateProcess Error.');
  {$ENDIF}
    LogMessage('TerminateProcess Error.');
  end;

  Stopped := True;
end;

procedure TCVSTracService.tmrBackupTimer(Sender: TObject);
begin
  BackupDataBase(False);
end;

initialization
{$IFDEF DEBUG}
  LogFile := TFileStream.Create(ChangeFileExt(ParamStr(0), '.log'), fmCreate);
  Log('Application Start: ' + DateTimeToStr(Now));
{$ENDIF}

finalization
{$IFDEF DEBUG}
  Log('Application End: ' + DateTimeToStr(Now));
  LogFile.Free;
{$ENDIF}

end.


