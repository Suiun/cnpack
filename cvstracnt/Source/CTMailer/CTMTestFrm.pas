unit CTMTestFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��ʼ����ò��Դ���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMTestFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.30
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Buttons;

type
  TCTMTestForm = class(TForm)
    btn1: TSpeedButton;
    img1: TImage;
    lblText: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

procedure ShowTestForm(const Text: string; Font: TFont);
procedure HideTestForm;
procedure UpdateTestForm(const Text: string);

implementation

{$R *.dfm}

var
  FCTMTestForm: TCTMTestForm;

procedure ShowTestForm(const Text: string; Font: TFont);
begin
  if not Assigned(FCTMTestForm) then
    FCTMTestForm := TCTMTestForm.Create(Application);
  FCTMTestForm.lblText.Caption := Text;
  FCTMTestForm.Font.Assign(Font);
  FCTMTestForm.Show;
  FCTMTestForm.BringToFront;
  Application.ProcessMessages;
end;

procedure HideTestForm;
begin
  if Assigned(FCTMTestForm) then
    FreeAndNil(FCTMTestForm);
  Application.ProcessMessages;
end;

procedure UpdateTestForm(const Text: string);
begin
  if Assigned(FCTMTestForm) then
    FCTMTestForm.lblText.Caption := Text;
  Application.ProcessMessages;
end;

end.
