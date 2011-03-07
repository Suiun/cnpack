unit CTPluginIntf;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��������
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע�������������嵥Ԫ
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTPluginIntf.pas,v 1.2 2007/02/09 12:08:45 zjy Exp $
* ���¼�¼��2005.03.30
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, SysUtils;

type

//------------------------------------------------------------------------------
// ������ӿ�
//------------------------------------------------------------------------------

  PVersion = ^TVersion;
  TVersion = packed record
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwReleaseVersion: DWORD;
    dwBuildNumber: DWORD;
  end;

  TGetLangIDProc = function (): Integer; stdcall;
  TGetPCharProc = function (): PChar; stdcall;
  TLogProc = procedure (Text: PChar); stdcall;

  PHostIntf = ^THostIntf;
  THostIntf = packed record
    dwSize: DWORD;
    Version: TVersion;
    GetDBPath: TGetPCharProc;
    GetLangPath: TGetPCharProc;
    GetLangID: TGetLangIDProc;
    Log: TLogProc;
  end;

//------------------------------------------------------------------------------
// ����ӿ�
//------------------------------------------------------------------------------

  PTicketInfo = ^TTicketInfo;
  TTicketInfo = packed record
    dwSize: DWORD;
    DBName: PChar;
    DBFileName: PChar;
    LocalServer: PChar;
    Port: Integer;
    TicketNo: Integer;
    TicketType: PChar;
    TicketStatus: PChar;
    OrigTime: PChar;
    ChangeTime: PChar;
    DerivedFrom: PChar;
    Version: PChar;
    AssignedTo: PChar;
    Severity: PChar;
    Priority: PChar;
    SubSystem: PChar;
    Owner: PChar;
    Title: PChar;
    Description: PChar;
    Remarks: PChar;
    Contact: PChar;
    Modificator: PChar;
    // Extra Field Name and Text
    Extra_Name: array[1..5] of PChar;
    Extra: array[1..5] of PChar;
  end;

  PPluginInfo = ^TPluginInfo;
  TPluginInfo = packed record
    dwSize: DWORD;
    Name: PChar;
    Comment: PChar;
    Version: TVersion;
    Author: PChar;
    WebSite: PChar;
    Email: PChar;
  end;

  TGetPluginInfoProc = function (): PPluginInfo; stdcall;
  TPluginExecuteProc = function (IniFileName: PChar;
    TicketInfo: PTicketInfo): BOOL; stdcall;
  TConfigPluginProc = function (Owner: HWND): BOOL; stdcall;
  TConfigDatabaseProc = function (Owner: HWND; DBName, DBFileName,
    IniFileName: PChar): BOOL; stdcall;
  TLangChangedProc = procedure (LangID: Integer); stdcall;

  PPluginIntf = ^TPluginIntf;
  TPluginIntf = packed record
    dwSize: DWORD;
    GetPluginInfo: TGetPluginInfoProc;
    Execute: TPluginExecuteProc;
    ConfigPlugin: TConfigPluginProc;
    ConfigDatabase: TConfigDatabaseProc;
    LangChanged: TLangChangedProc;
  end;

  TPluginInitProc = function (HostIntf: PHostIntf; var PluginIntf: PPluginIntf):
    BOOL; stdcall; 

const
  csPluginExportProc = 'InitProc001';

function MakeVersion(Major, Minor, Release, Build: DWORD): TVersion;
function VersionToStr(Version: TVersion): string;

implementation

function MakeVersion(Major, Minor, Release, Build: DWORD): TVersion;
begin
  Result.dwMajorVersion := Major;
  Result.dwMinorVersion := Minor;
  Result.dwReleaseVersion := Release;
  Result.dwBuildNumber := Build;
end;

function VersionToStr(Version: TVersion): string;
begin
  with Version do
    Result := Format('%d.%d.%d.%d', [dwMajorVersion, dwMinorVersion,
      dwReleaseVersion, dwBuildNumber]);
end;

end.



