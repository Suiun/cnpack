unit CTXDatabaseFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ����ݿ��ʼ�֪ͨ���ô���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTXDatabaseFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.31
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, CTXSettings, CTMultiLangFrm, Spin;

type
  TCTXDatabaseForm = class(TCTMultiLangForm)
    grp1: TGroupBox;
    chkToAll: TCheckBox;
    chkToAssigned: TCheckBox;
    chkToContact: TCheckBox;
    btnClose: TButton;
    btnHelp: TButton;
    chkToOwner: TCheckBox;
    lbl1: TLabel;
    lbl2: TLabel;
    mmoUsers: TMemo;
    chkToAllRTXUsers: TCheckBox;
    grp2: TGroupBox;
    rbSysMsg: TRadioButton;
    rbNormalMsg: TRadioButton;
    lbl3: TLabel;
    edtTitle: TEdit;
    lbl4: TLabel;
    lbl5: TLabel;
    seMsgDelay: TSpinEdit;
    procedure rbNormalMsgClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

function ShowDBOptionForm(Settings: TRTXDBSettings): Boolean;

implementation

{$R *.dfm}

function ShowDBOptionForm(Settings: TRTXDBSettings): Boolean;
begin
  with Settings, TCTXDatabaseForm.Create(Application) do
  try
    chkToAllRTXUsers.Checked := ToAllRTXUsers;
    chkToAll.Checked := ToAllUser;
    chkToAssigned.Checked := ToAssigned;
    chkToOwner.Checked := ToOwner;
    chkToContact.Checked := ToContact;
    mmoUsers.Lines := Users;
    edtTitle.Text := Title;
    rbNormalMsg.Checked := not SysMsg;
    rbSysMsg.Checked := SysMsg;
    seMsgDelay.Value := MsgDelay;
    rbNormalMsgClick(nil);

    Result := ShowModal = mrOk;
    if Result then
    begin
      ToAllRTXUsers := chkToAllRTXUsers.Checked;
      ToAllUser := chkToAll.Checked;
      ToAssigned := chkToAssigned.Checked;
      ToOwner := chkToOwner.Checked;
      ToContact := chkToContact.Checked;
      Users.Assign(mmoUsers.Lines);
      Title := edtTitle.Text;
      SysMsg := rbSysMsg.Checked;
      MsgDelay := seMsgDelay.Value;
    end;
  finally
    Free;
  end;
end;

procedure TCTXDatabaseForm.rbNormalMsgClick(Sender: TObject);
begin
  inherited;
  seMsgDelay.Enabled := rbNormalMsg.Checked;
end;

end.
