unit CTMDatabaseFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ����ݿ��ʼ�֪ͨ���ô���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMDatabaseFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.31
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, CTMSettings, CTMultiLangFrm;

type
  TCTMDatabaseForm = class(TCTMultiLangForm)
    grp1: TGroupBox;
    chkToAll: TCheckBox;
    chkToAssigned: TCheckBox;
    chkToContact: TCheckBox;
    lbledtRecipients: TLabeledEdit;
    lbledtCopyTo: TLabeledEdit;
    lbledtReplyTo: TLabeledEdit;
    btnClose: TButton;
    btnHelp: TButton;
    chkToOwner: TCheckBox;
    lbl1: TLabel;
    lbledtTitle: TLabeledEdit;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

function ShowDBOptionForm(Settings: TMailerDBSettings): Boolean;

implementation

{$R *.dfm}

function ShowDBOptionForm(Settings: TMailerDBSettings): Boolean;
begin
  with Settings, TCTMDatabaseForm.Create(Application) do
  try
    chkToAll.Checked := ToAllUser;
    chkToAssigned.Checked := ToAssigned;
    chkToOwner.Checked := ToOwner;
    chkToContact.Checked := ToContact;
    lbledtTitle.Text := Title;
    lbledtCopyTo.Text := CopyTo;
    lbledtRecipients.Text := Recipients;
    lbledtReplyTo.Text := ReplyTo;

    Result := ShowModal = mrOk;
    if Result then
    begin
      ToAllUser := chkToAll.Checked;
      ToAssigned := chkToAssigned.Checked;
      ToOwner := chkToOwner.Checked;
      ToContact := chkToContact.Checked;
      Title := lbledtTitle.Text;
      CopyTo := lbledtCopyTo.Text;
      Recipients := lbledtRecipients.Text;
      ReplyTo := lbledtReplyTo.Text;
    end;
  finally
    Free;
  end;
end;

end.
