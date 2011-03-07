unit CTNPlugin;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��ʼ�֪ͨ�����Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTNPlugin.pas,v 1.2 2007/02/09 12:08:45 zjy Exp $
* ���¼�¼��2005.03.31
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, SysUtils, Classes, IniFiles, CTPluginIntf, CTPlugin, CTNConsts,
  CnCommon, CnConsts, CnLangMgr, CTMultiLangPlugin;

type
  TNetSendPlugin = class(TMultiLangPlugin)
  protected
    procedure GetPluginInfo(var PluginInfo: TPluginInfo); override;
    function Execute(HostIniFile, DBIniFile: TCustomIniFile; TicketInfo:
      TTicketInfo): Boolean; override;
    procedure LangChanged(LangID: Integer); override;
  published
    function ConfigDatabase(Owner: HWND; IniFile: TCustomIniFile;
      const DBName, DBFileName: string): Boolean; override;
  end;

implementation

uses CTNDatabaseFrm, CTNSettings, CTPluginUtils, CTMultiLang;

{ TNetSendPlugin }

function TNetSendPlugin.ConfigDatabase(Owner: HWND; IniFile: TCustomIniFile;
  const DBName, DBFileName: string): Boolean;
var
  Settings: TNetSendDBSettings;
begin
  Settings := TNetSendDBSettings.Create;
  try
    Settings.LoadFromIni(IniFile);
    if ShowDBOptionForm(Settings) then
    begin
      Settings.SaveToIni(IniFile);
      Result := True;
    end
    else
      Result := False;
  finally
    Settings.Free;
  end;
end;

function TNetSendPlugin.Execute(HostIniFile, DBIniFile: TCustomIniFile;
  TicketInfo: TTicketInfo): Boolean;
var
  DBSettings: TNetSendDBSettings;
  Text: string;
  i: Integer;

  function DoSend(const AUser: string): Boolean;
  var
    CmdLine, S: string;
    Code: Cardinal;
  begin
    CmdLine := Format('net send %s %s', [AUser, Text]);
    Result := WinExecWithPipe(CmdLine, '', S, Code);
    if Result then
      Log(Format('Send to "%s". ExitCode: %d. Output:'#13#10'%s',
        [AUser, Code, S]))
    else
      Log(Format('Send to "%s" fail', [AUser]));
  end;
begin
  Result := False;
  DBSettings := nil;
  try
    try
      DBSettings := TNetSendDBSettings.Create;
      DBSettings.LoadFromIni(DBIniFile);

      Text := GetTicketInfoShortText(TicketInfo, Self);
      Log('Context: ' + Text);

      if DBSettings.AllUsers then
        DoSend('*');
      if DBSettings.LoginUsers then
        DoSend('/USERS');

      for i := 0 to DBSettings.Users.Count - 1 do
        if Trim(DBSettings.Users[i]) <> '' then
          DoSend(Trim(DBSettings.Users[i]));

      Result := True;
    except
      on E: Exception do
      begin
        Log('Exception: ' + E.Message);
      end;
    end;
  finally
    if Assigned(DBSettings) then DBSettings.Free;
  end;
end;

procedure TNetSendPlugin.GetPluginInfo(var PluginInfo: TPluginInfo);
begin
  PluginInfo.dwSize := SizeOf(TPluginInfo);
  PluginInfo.Name := PChar(SNetSendName);
  PluginInfo.Comment := PChar(SNetSendComment);
  PluginInfo.Version := MakeVersion(1, 0, 0, 0);
  PluginInfo.Author := PChar(SCnPack_Zjy);
  PluginInfo.WebSite := PChar(SCnPackUrl);
  PluginInfo.Email := PChar(SCnPackEmail);
end;

procedure TNetSendPlugin.LangChanged(LangID: Integer);
begin
  inherited;

  TranslateStr(SNetSendName, 'SNetSendName');
  TranslateStr(SNetSendComment, 'SNetSendComment');
end;

initialization
  PluginClass := TNetSendPlugin;

end.
