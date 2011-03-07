unit CTMultiLangPlugin;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ�֧�ֶ����ԵĲ����Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMultiLangPlugin.pas,v 1.2 2007/02/09 12:08:45 zjy Exp $
* ���¼�¼��2005.04.04
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, SysUtils, Classes, CTPluginIntf, CTPlugin;
  
type
  TMultiLangPlugin = class(TPlugin)
  protected
    procedure LangChanged(LangID: Integer); override;
  public
    procedure Loaded; override;
  end;

implementation

uses
  CnLangMgr, CTMultiLang, CnConsts;

{ TMultiLangPlugin }

procedure TMultiLangPlugin.LangChanged(LangID: Integer);
begin
  inherited;
  UpdateLangID(LangID);
  
  // Common
  TranslateStr(SCnInformation, 'SCnInformation');
  TranslateStr(SCnWarning, 'SCnWarning');
  TranslateStr(SCnError, 'SCnError');
  TranslateStr(SCnEnabled, 'SCnEnabled');
  TranslateStr(SCnDisabled, 'SCnDisabled');
  TranslateStr(SCnMsgDlgOK, 'SCnMsgDlgOK');
  TranslateStr(SCnMsgDlgCancel, 'SCnMsgDlgCancel');
  TranslateStr(SCnPack_Zjy, 'SCnPack_Zjy');
end;

procedure TMultiLangPlugin.Loaded;
begin
  inherited;
  InitLangManager(GetLangPath, GetLangID);
end;

end.
