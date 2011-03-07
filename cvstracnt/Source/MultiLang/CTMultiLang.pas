unit CTMultiLang;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ������Դ�������Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMultiLang.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.30
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, SysUtils, Classes, CnLangMgr, CnHashLangStorage, CnLangStorage;

procedure InitLangManager(const LangPath: string; LangID: Integer;
  FileName: string = '');

procedure UpdateLangID(LangID: Integer);

implementation

const
  csLanguage = 'Language';
  csEnglishID = 1033;

var
  FStorage: TCnHashLangFileStorage;

procedure InitLangManager(const LangPath: string; LangID: Integer;
  FileName: string = '');
begin
  if CnLanguageManager = nil then
    CreateLanguageManager;
    
  CnLanguageManager.AutoTranslate := False;
  CnLanguageManager.TranslateTreeNode := True;
  CnLanguageManager.UseDefaultFont := True;
  FStorage := TCnHashLangFileStorage.Create(nil);
  if FileName = '' then
    FileName := ChangeFileExt(ExtractFileName(GetModuleName(HInstance)), '.txt');
  FStorage.FileName := FileName;
  FStorage.StorageMode := smByDirectory;
  FStorage.LanguagePath := LangPath;
  CnLanguageManager.LanguageStorage := FStorage;

  if FStorage.Languages.Find(LangID) >= 0 then
    CnLanguageManager.CurrentLanguageIndex := FStorage.Languages.Find(LangID)
  else
    CnLanguageManager.CurrentLanguageIndex := FStorage.Languages.Find(csEnglishID);
end;

procedure UpdateLangID(LangID: Integer);
begin
  if FStorage.Languages.Find(LangID) >= 0 then
    CnLanguageManager.CurrentLanguageIndex := FStorage.Languages.Find(LangID);
end;

end.

