unit CTMultiLangFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ������Ի�����
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMultiLangFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.04.04
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, CnLangMgr;

type
  TCTMultiLangForm = class(TForm)
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

procedure TCTMultiLangForm.FormCreate(Sender: TObject);
begin
  CnLanguageManager.TranslateForm(Self);
end;

end.
