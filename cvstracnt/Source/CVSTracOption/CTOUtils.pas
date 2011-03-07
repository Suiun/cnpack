unit CTOUtils;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT �������ó���
* ��Ԫ���ƣ��������̵�Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows Server 2003 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTOUtils.pas,v 1.5 2007/02/09 12:08:45 zjy Exp $
* ���¼�¼��2003.11.14
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, SysUtils, Classes, CnCommon, SQLite3, SQLiteTable3, CTConsts;

function FmtPath(const Path: string): string;
{* ת��·��Ϊ��׼��ʽ}

procedure GetRepositoryList(List: TStrings);
{* ȡ CVSNT ��ע����ж���� CVS �ֿ��б�}

function GetRepositoryInfo(const DBFile: string; var Info: TDBOptionInfo):
  Boolean;
{* �����ݿ��ļ��з��� CVS �ֿ�·����ģ����}

function SetRepositoryInfo(const DBFile: string; Info: TDBOptionInfo): Boolean;
{* д CVS �ֿ�·����ģ���������ݿ��ļ�}

function ExportUsersToFile(const DBFile, ListFile: string): Boolean;
{* �����û��б��ļ�}

function ImportUsersFromFile(const DBFile, ListFile: string): Boolean;
{* ���û��б��ļ��е�������}

function SCMToStr(SCM: TSCMKind; LongStr: Boolean): string;

function StrToSCM(const S: string): TSCMKind;

implementation

const
  csMaxRepository = 64;

function FmtPath(const Path: string): string;
begin
  Result := GetUnixPath(MakeDir(Path));
end;

procedure GetRepositoryList(List: TStrings);
var
  i: Integer;
  AHome: string;
begin
  List.Clear;
  for i := 0 to csMaxRepository - 1 do
  begin
    AHome := RegReadStringDef(HKEY_LOCAL_MACHINE, 'Software\CVS\Pserver',
      'Repository' + IntToStr(i), '');
    AHome := FmtPath(AHome);
    if (AHome <> '') and (List.IndexOf(AHome) < 0) then
      List.Add(AHome);
  end;
end;

function GetRepositoryInfo(const DBFile: string; var Info: TDBOptionInfo):
  Boolean;
var
  DB: TSQLiteDatabase;
  NotifyCmd: string;
  List: TStrings;

  function GetParam(const Name: string): string;
  begin
    try
      Result := DB.GetTableString(Format('SELECT value FROM config WHERE name=''%s'';', [Name]));
    except
      Result := '';
    end;
  end;
begin
  Result := True;
  try
    DB := TSQLiteDatabase.Create(DBFile);
    try
      List := TStringList.Create;
      try
        Info.SCM := StrToSCM(GetParam('scm'));
        Info.Home := GetParam('cvsroot');
        Info.Module := GetParam('module');
        Info.CvsUser := GetParam('cvs_user_id');
        Info.Charset := GetParam('charset');
        Info.Passwd := Copy(GetParam('write_cvs_passwd'), 1, 1) <> 'n';
        NotifyCmd := GetParam('notify');
        if NotifyCmd = '' then
          Info.NotifyKind := nkNone
        else if Pos(csCTSenderName, NotifyCmd) > 0 then
          Info.NotifyKind := nkPlugin
        else
          Info.NotifyKind := nkOther;
      finally
        List.Free;
      end;
    finally
      DB.Free;
    end;
  except
    Result := False;
  end;
end;

function SetRepositoryInfo(const DBFile: string; Info: TDBOptionInfo): Boolean;
const
  SYesNo: array[Boolean] of string = ('no', 'yes');
var
  DB: TSQLiteDatabase;

  function TransFileName(const FileName: string): string;
  begin
    if Pos(' ', FileName) > 0 then
      Result := '"' + FileName + '"'
    else
      Result := FileName;
  end;
begin
  try
    DB := TSQLiteDatabase.Create(DBFile);
    try
      DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''scm'',''%s'');', [SCMToStr(Info.SCM, False)]));
      DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''cvsroot'',''%s'');', [Info.Home]));
      DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''module'',''%s'');', [Info.Module]));
      DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''cvs_user_id'',''%s'');', [Info.CvsUser]));
      if Info.Charset <> '' then
        DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''charset'',''%s'');', [Info.Charset]))
      else
        DB.ExecSQL('DELETE FROM config WHERE (name = ''charset'');');
      DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''write_cvs_passwd'',''%s'');', [SYesNo[Info.Passwd]]));
      if Info.NotifyKind = nkNone then
        DB.ExecSQL('REPLACE INTO config(name,value) VALUES(''notify'','''');')
      else if Info.NotifyKind = nkPlugin then
        DB.ExecSQL(Format('REPLACE INTO config(name,value) VALUES(''notify'',''%s "%s" "%%n" "%%u"'');',
          [GetUnixPath(TransFileName(ExtractFilePath(ParamStr(0)) + csCTSenderName)),
          Info.Database]));
      Result := True;
    finally
      DB.Free;
    end;
  except
    Result := False;
  end;
end;

function ExportUsersToFile(const DBFile, ListFile: string): Boolean;
var
  DB: TSQLiteDatabase;
  Table: TSQLiteTable;
  List: TStrings;
begin
  Result := True;
  try
    DB := TSQLiteDatabase.Create(DBFile);
    try
      List := TStringList.Create;
      try
        Table := DB.GetTable('SELECT id,name,email,passwd,capabilities FROM user');
        try
          Table.MoveFirst;
          while not Table.EOF do
          begin
            List.Add(Format('%s,%s,%s,%s,%s', [Table.FieldAsString(0),
              Table.FieldAsString(1), Table.FieldAsString(2),
              Table.FieldAsString(3), Table.FieldAsString(4)]));
            Table.Next;
          end;
          List.SaveToFile(ListFile);
        finally
          Table.Free;
        end;
      finally
        List.Free;
      end;
    finally
      DB.Free;
    end;
  except
    Result := False;
  end;
end;

function ImportUsersFromFile(const DBFile, ListFile: string): Boolean;
const
  csFieldCount = 5;
var
  DB: TSQLiteDatabase;
  List: TStrings;
  Fields: TStrings;
  i: Integer;
begin
  try
    DB := nil;
    List := nil;
    Fields := nil;
    try
      DB := TSQLiteDatabase.Create(DBFile);
      List := TStringList.Create;
      Fields := TStringList.Create;
      List.LoadFromFile(ListFile);
      for i := 0 to List.Count - 1 do
      begin
        Fields.CommaText := List[i];
        if Fields.Count = csFieldCount then
        begin
          DB.ExecSQL(Format('REPLACE INTO user(id,name,email,passwd,capabilities)' + #13#10 +
            'VALUES(''%s'',''%s'',''%s'',''%s'',''%s'')', [Fields[0], Fields[1],
            Fields[2], Fields[3], Fields[4]]));
        end;
      end;
      Result := True;
    finally
      if Assigned(DB) then DB.Free;
      if Assigned(List) then List.Free;
      if Assigned(Fields) then Fields.Free;
    end;
  except
    Result := False;
  end;
end;

function SCMToStr(SCM: TSCMKind; LongStr: Boolean): string;
begin
  if LongStr then
    Result := csSCMNames[SCM]
  else
    Result := csSCMs[SCM];
end;  

function StrToSCM(const S: string): TSCMKind;
var
  SCM: TSCMKind;
begin
  for SCM := Low(TSCMKind) to High(TSCMKind) do
    if SameText(S, csSCMs[SCM]) or SameText(S, csSCMNames[SCM]) then
    begin
      Result := SCM;
      Exit;
    end;
  Result := skNone;
end;  

end.

