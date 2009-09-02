{******************************************************************************}
{                       CnPack For Delphi/C++Builder                           }
{                     �й����Լ��Ŀ���Դ�������������                         }
{                   (C)Copyright 2001-2009 CnPack ������                       }
{                   ------------------------------------                       }
{                                                                              }
{            ���������ǿ�Դ���������������������� CnPack �ķ���Э������        }
{        �ĺ����·�����һ����                                                }
{                                                                              }
{            ������һ��������Ŀ����ϣ�������ã���û���κε���������û��        }
{        �ʺ��ض�Ŀ�Ķ������ĵ���������ϸ���������� CnPack ����Э�顣        }
{                                                                              }
{            ��Ӧ���Ѿ��Ϳ�����һ���յ�һ�� CnPack ����Э��ĸ��������        }
{        ��û�У��ɷ������ǵ���վ��                                            }
{                                                                              }
{            ��վ��ַ��http://www.cnpack.org                                   }
{            �����ʼ���master@cnpack.org                                       }
{                                                                              }
{******************************************************************************}

unit CnHashLangStorage;
{* |<PRE>
================================================================================
* �������ƣ�CnPack �����
* ��Ԫ���ƣ�Hash �ı�����洢�����Ԫ
* ��Ԫ���ߣ�CnPack������
* ��    ע���õ�Ԫʵ����Hash TXT ����洢�����
* ����ƽ̨��PWin2000 + Delphi 5.0
* ���ݲ��ԣ�PWin9X/2000/XP + Delphi 5/6/7
* �� �� �����õ�Ԫ�е��ַ��������ϱ��ػ�������ʽ
* ��Ԫ��ʶ��$Id$
* �޸ļ�¼��2004.10.23 V1.2
*               �޸ĳ�ʼ���ļ��Ĵ�����ʽ
*           2003.12.13 V1.1
*               InternalInit �����Ӷ� DefaultFont �Ķ��봦��
*           2003.08.20 V1.0
*               ������Ԫ��ʵ�ֹ���
================================================================================
|</PRE>}

interface

{$I CnPack.inc}

uses
  SysUtils, Classes, Windows, IniFiles, Dialogs, FileCtrl,
  CnConsts, CnLangConsts, CnHashMap, CnLangStorage, CnIniStrUtils;

type
  TCnCustomHashLangStorage = class;

  TCnHashStringIterator = class(TInterfacedObject, ICnLangStringIterator)
  private
    FHashStorage: TCnCustomHashLangStorage;
    FEof: Boolean;
    FBof: Boolean;
    FFrontPattern: string;
    FKey: string;
    FValue: string;
  public
    constructor Create(AHashStorage: TCnCustomHashLangStorage);
    destructor Destroy; override;

    procedure StartIterate(const FrontPattern: string = '');
    procedure Previous;
    procedure Next;
    procedure EndIterate;
    procedure GetCurrentKeyValue(var Key:string; var Value: string);
    function GetCurrentString: string;
    function GetEof: Boolean;
    function GetBof: Boolean;

    property Eof: Boolean read GetEof;
    property Bof: Boolean read GetBof;
  end;

  TCnCustomHashLangStorage = class(TCnCustomLangFileStorage)
  private
    FHashMap: TCnStrToStrHashMap;
    FListLength: Integer;
    FIncSize: Integer;
    procedure SetIncSize(const Value: Integer);
    procedure SetListLength(const Value: Integer);
  protected
    procedure InitHashMap;
    procedure AddStringToHashMap(const Key: string; const Value: string);
    procedure InitFromAFile(const AFileName: string); override;
    procedure CreateCurrentLanguage; override;
    procedure GetComponentInfo(var AName, Author, Email, Comment: string); override;
    property HashMap: TCnStrToStrHashMap read FHashMap;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    class function GetLanguageFileExt: string; override;
    {* ���ض������ļ�����չ��.TXT }
    function GetString(Name: string; var Value: string): Boolean; override;
    {* ���һ������Ŀ�ķ������ַ��� }
    procedure GetNamesList(List: TStrings); override;
    {* ��õ�ǰ���Ե�����������Ŀ�����б� }
    function IsLanguageFile(const FileName: string): Boolean; override;
    {* �ж�һ�ļ��Ƿ�Ϸ��������ļ� }
    procedure SetString(Name, Value: string); override;
    {* ����һ������Ŀ��������򸲸ǣ��������� }
    function CreateIterator: ICnLangStringIterator; override;
    {* ��ñ�������������಻֧�ֱ���������뷵�� nil}
    function LoadCurrentLanguage: Boolean; override;
    {* �� TXT �ļ������뵱ǰ������Ŀ��Ϊ�����ִ���׼�� }
    procedure SaveCurrentLanguage; override;
    {* ���浱ǰ�����ļ� }
    procedure ClearCurrentLanguage; override;
    {* ɾ����ǰ���Ե����з�����Ŀ�б���ͬʱҲ���汾���� }
  published
    property StorageMode;
    {* ����洢��ʽ }
    property LanguagePath;
    {* �����ļ��洢��ͳһ·�� }
    property FileName;
    {* ���ļ��洢ʱ��ͳһ�����ļ��� }
    property Languages;
    {* ���Զ����б� }
    property ListLength: Integer read FListLength write SetListLength;
    {* ��ʼ�б���С }
    property IncSize: Integer read FIncSize write SetIncSize;
    {* �ط���ʱ���ӵĴ�С }
    property AutoDetect;
    {* LanguagePath �ı�ʱ�Ƿ��Զ�������� }
  end;

  TCnHashLangFileStorage = class(TCnCustomHashLangStorage)
  published
    property StorageMode;
    {* ����洢��ʽ }
    property LanguagePath;
    {* �����ļ��洢��ͳһ·�� }
    property Languages;
    {* ���Զ����б� }
    property FileName;
    {* ���ļ��洢ʱ��ͳһ�����ļ��� }
    property ListLength;
    {* ��ʼ�б���С }
    property IncSize;
    {* �ط���ʱ���ӵĴ�С }
    property AutoDetect;
    {* LanguagePath �ı�ʱ�Ƿ��Զ�������� }
  end;

implementation

{************************** TCnCustomHashLangStorage **************************}

constructor TCnCustomHashLangStorage.Create(AOwner: TComponent);
begin
  inherited;
  Self.FListLength := 1024;
  Self.FIncSize := 2;
end;

destructor TCnCustomHashLangStorage.Destroy;
begin
  if Assigned(FHashMap) then
    FHashMap.Free;
  inherited;
end;

procedure TCnCustomHashLangStorage.CreateCurrentLanguage;
begin
  InitHashMap;
end;

function TCnCustomHashLangStorage.GetString(Name: string; var Value: string):
  Boolean;
begin
  Result := False;
  if Assigned(FHashMap) then
  begin
    Result := FHashMap.Find(Name, Value);
    if Result then
      Value := StringReplace(Value, SCnBR, SCnCRLF, [rfReplaceAll, rfIgnoreCase])
    else
      Value := '';
  end;
end;

function TCnCustomHashLangStorage.LoadCurrentLanguage: Boolean;
var
  List: TStrings;
  i, EPos: Integer;
  S: string;
begin
  Result := True;
  InitHashMap;
  
  List := TStringList.Create;
  try
    S := LanguagePath + GetCurrentLanguageFileName;
    List.LoadFromFile(S);
  except
    Result := False;
    List.Free;
    Exit;
  end;

  for i := 0 to List.Count - 1 do
  begin
    S := List[i];
    EPos := Pos(DefEqual, S);
    if EPos > 0 then
      AddStringToHashMap(Copy(S, 1, EPos - 1), Copy(S, EPos + 1,
        Length(S) - EPos))
    else
      AddStringToHashMap(Copy(S, 1, EPos - 1), '');
  end;
  List.Free;
end;

procedure TCnCustomHashLangStorage.SaveCurrentLanguage;
var
  Key, Value, aFileName: string;
  List: TStringList;
begin
  if Assigned(FHashMap) then
  begin
    List := TStringList.Create;
    FHashMap.StartEnum;
    while FHashMap.GetNext(Key, Value) do
      List.Add(Key + DefEqual + Value);
    List.Sort;

    // ������������ֵ��������ļ��洢��Ŀ¼����浽��Ŀ¼��
    if (csDesigning in ComponentState) and (LanguagePath = '') and (DesignLangPath <> '') then
      aFileName := IncludeTrailingBackslash(DesignLangPath) + GetCurrentLanguageFileName
    else
      aFileName := IncludeTrailingBackslash(LanguagePath) + GetCurrentLanguageFileName;

    if not ForceDirectories(ExtractFilePath(aFileName)) then
      raise ELanguageStorageError.Create(SCnCanNotCreateDir + ExtractFilePath(aFileName));

    List.SaveToFile(aFileName);
    List.Free;
  end;
end;

procedure TCnCustomHashLangStorage.SetString(Name, Value: string);
var
  myValue: string;
begin
  if Assigned(FHashMap) then
  begin
    if FHashMap.Find(Name, myValue) then
      FHashMap.Delete(Name);
    AddStringToHashMap(Name, StringReplace(Value, SCnCRLF, SCnBR, [rfReplaceAll, rfIgnoreCase]));
  end;
end;

procedure TCnCustomHashLangStorage.GetNamesList(List: TStrings);
var
  Key, Value: string;
begin
  if List <> nil then
  begin
    List.Clear;
    if Assigned(FHashMap) then
    begin
      FHashMap.StartEnum;
      while FHashMap.GetNext(Key, Value) do
        List.Add(Key);
      if List is TStringList then
        (List as TStringList).Sort;
    end;
  end;
end;

procedure TCnCustomHashLangStorage.ClearCurrentLanguage;
begin
  InitHashMap;
  SaveCurrentLanguage;
end;

class function TCnCustomHashLangStorage.GetLanguageFileExt: string;
begin
  Result := '.txt';
end;

function TCnCustomHashLangStorage.IsLanguageFile(
  const FileName: string): Boolean;
var
  F: Text;
  S: String;
begin
  Result := False;
  try
    AssignFile(F, FileName);
    Reset(F);
  except
    Exit;
  end;
  Readln(F, S);
  CloseFile(F);

  Result := Copy(S, 1, Length(SystemNamePrefix + SCnLanguageID)) =
    SystemNamePrefix + SCnLanguageID;
end;

procedure TCnCustomHashLangStorage.InitHashMap;
begin
  if Assigned(FHashMap) then
    FreeAndNil(FHashMap);
  FHashMap := TCnStrToStrHashMap.Create(FListLength, FIncSize);
end;

procedure TCnCustomHashLangStorage.SetIncSize(const Value: Integer);
begin
  if Value > 0 then
    FIncSize := Value;
end;

procedure TCnCustomHashLangStorage.SetListLength(const Value: Integer);
begin
  if Value > 0 then
    FListLength := Value;
end;

function TCnCustomHashLangStorage.CreateIterator: ICnLangStringIterator;
begin
  Result := TCnHashStringIterator.Create(Self);
end;

procedure TCnCustomHashLangStorage.InitFromAFile(const AFileName: string);
var
  F: Text;
  List: TStrings;
  I: Integer;
  S: string;
begin
  List := TStringList.Create;

  with Languages.Add do
  begin
    LanguageFileName := ExtractFileName(ChangeFileExt(AFileName, ''));
    AssignFile(F, AFileName); Reset(F); List.Clear;

    for I := 0 to 4 do
    begin
      Readln(F, S);
      List.Add(S);
    end;
    Close(F);

    try
      LanguageID := StrToIntDef(List.Values[SystemNamePrefix + SCnLanguageID], 0);
    except
      LanguageID := 0;
    end;

    if LanguageID <> 0 then
    begin
      LanguageName := List.Values[SystemNamePrefix + SCnLanguageName];
      Author := List.Values[SystemNamePrefix + SCnAuthor];
      AuthorEmail := List.Values[SystemNamePrefix + SCnAuthorEmail];
      if List.Values[SystemNamePrefix + SCnDefaultFont] <> '' then
        StringToFont(List.Values[SystemNamePrefix + SCnDefaultFont], DefaultFont);
    end
    else
    begin
      Self.FCurrentLanguageIndex := -1;
      Self.Languages.Delete(Index);
    end;
  end;
  List.Free;
end;

procedure TCnCustomHashLangStorage.GetComponentInfo(var AName, Author,
  Email, Comment: string);
begin
  AName := SCnHashLangStorageName;
  Author := SCnPack_LiuXiao;
  Email := SCnPack_LiuXiaoEmail;
  Comment := SCnHashLangStorageComment;
end;

procedure TCnCustomHashLangStorage.AddStringToHashMap(const Key,
  Value: string);
begin
  FHashMap.Add(Key, Value);
end;

{ TCnHashStringIterator }

constructor TCnHashStringIterator.Create(
  AHashStorage: TCnCustomHashLangStorage);
begin
  inherited Create;
  FHashStorage := AHashStorage;
end;

destructor TCnHashStringIterator.Destroy;
begin
  inherited;

end;

procedure TCnHashStringIterator.EndIterate;
begin
// Do Almost NOTHING.
  FKey := '';
  FValue := '';
end;

function TCnHashStringIterator.GetBof: Boolean;
begin
  Result := FBof;
end;

procedure TCnHashStringIterator.GetCurrentKeyValue(var Key, Value: string);
begin
  Key := FKey;
  Value := FValue;
end;

function TCnHashStringIterator.GetCurrentString: string;
begin
  Result := FKey + DefEqual + FValue;
end;

function TCnHashStringIterator.GetEof: Boolean;
begin
  Result := FEof;
end;

procedure TCnHashStringIterator.Next;
begin
  if FHashStorage.FHashMap <> nil then
  begin
    repeat
      FEof := not FHashStorage.FHashMap.GetNext(FKey, FValue);
    until FEof or (FFrontPattern = '') or (Pos(FFrontPattern, FKey) = 1);
  end
  else
    FEof := True;
end;

procedure TCnHashStringIterator.Previous;
begin
  raise ELanguageStorageError.Create('Previous operation NOT supported.');
end;

procedure TCnHashStringIterator.StartIterate(const FrontPattern: string);
begin
  Assert(FHashStorage <> nil);

  if FHashStorage.FHashMap <> nil then
  begin
    FHashStorage.FHashMap.StartEnum;
    FFrontPattern := FrontPattern;
    repeat
      FEof := not FHashStorage.FHashMap.GetNext(FKey, FValue);
    until FEof or (FFrontPattern = '') or (Pos(FFrontPattern, FKey) = 1);
    FBof := FEof;
  end;
end;

end.