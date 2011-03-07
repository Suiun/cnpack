unit CTOMailFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��ʼ��������ô���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע�������������嵥Ԫ
* ����ƽ̨��PWindows Server 2003 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ����ݲ����ϱ��ػ�����ʽ
* ���¼�¼��2003.12.13
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, CTUtils, Spin, CnLangMgr;

type
  TCTOMailForm = class(TForm)
    grp1: TGroupBox;
    lbl1: TLabel;
    edtSmtpServer: TEdit;
    chkNeedAuth: TCheckBox;
    lbl2: TLabel;
    lbl3: TLabel;
    edtSenderMail: TEdit;
    edtUserName: TEdit;
    lbl4: TLabel;
    edtPassword: TEdit;
    btnClose: TButton;
    btnHelp: TButton;
    lbl5: TLabel;
    edtLocalServer: TEdit;
    lbl6: TLabel;
    lbl7: TLabel;
    seSmtpPort: TSpinEdit;
    lbl8: TLabel;
    edtSenderName: TEdit;
    procedure chkNeedAuthClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

function ShowMailForm(var Settings: TSettingsInfo): Boolean;

implementation

{$R *.DFM}

function ShowMailForm(var Settings: TSettingsInfo): Boolean;
begin
  with Settings, TCTOMailForm.Create(nil) do
  try
    edtSenderMail.Text := SenderMail;
    edtSenderName.Text := SenderName;
    edtSmtpServer.Text := SmtpServer;
    seSmtpPort.Value := SmtpPort;
    chkNeedAuth.Checked := NeedAuth;
    edtUserName.Text := UserName;
    edtPassword.Text := Password;
    edtLocalServer.Text := LocalServer;
    chkNeedAuthClick(nil);

    Result := ShowModal = mrOk;
    if Result then
    begin
      SenderMail := edtSenderMail.Text;
      SenderName := edtSenderName.Text;
      SmtpServer := edtSmtpServer.Text;
      SmtpPort := seSmtpPort.Value;
      NeedAuth := chkNeedAuth.Checked;
      UserName := edtUserName.Text;
      Password := edtPassword.Text;
      LocalServer := edtLocalServer.Text;
    end;
  finally
    Free;
  end;
end;

procedure TCTOMailForm.chkNeedAuthClick(Sender: TObject);
begin
  edtUserName.Enabled := chkNeedAuth.Checked;
  edtPassword.Enabled := chkNeedAuth.Checked;
end;

procedure TCTOMailForm.FormCreate(Sender: TObject);
begin
  CnLanguageManager.TranslateForm(Self);
end;

end.
