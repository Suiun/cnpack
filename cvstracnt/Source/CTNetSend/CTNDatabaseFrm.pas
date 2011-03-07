unit CTNDatabaseFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ�Net Send ֪ͨ���ô���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTNDatabaseFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.31
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, CTNSettings, StdCtrls, CTMultiLangFrm;

type
  TCTNDatabaseForm = class(TCTMultiLangForm)
    grp1: TGroupBox;
    btnClose: TButton;
    btnHelp: TButton;
    lbl2: TLabel;
    chkAllUsers: TCheckBox;
    chkLoginUsers: TCheckBox;
    mmoUsers: TMemo;
    lbl1: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

function ShowDBOptionForm(Settings: TNetSendDBSettings): Boolean;

implementation

{$R *.dfm}

function ShowDBOptionForm(Settings: TNetSendDBSettings): Boolean;
begin
  with Settings, TCTNDatabaseForm.Create(Application) do
  try
    chkAllUsers.Checked := AllUsers;
    chkLoginUsers.Checked := LoginUsers;
    mmoUsers.Lines.Assign(Users);

    Result := ShowModal = mrOk;
    if Result then
    begin
      AllUsers := chkAllUsers.Checked;
      LoginUsers := chkLoginUsers.Checked;
      Users.Assign(mmoUsers.Lines);
    end;
  finally
    Free;
  end;
end;

end.
