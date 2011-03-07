unit CTXOptionFrm;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��ʼ��������ô���
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTXOptionFrm.pas,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.03.31
*               ������Ԫ
================================================================================
|</PRE>}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Spin, CTXSettings, CnCommon, CnConsts, CTMultiLangFrm, ActiveX,
  ComObj;

type
  TCTXOptionForm = class(TCTMultiLangForm)
    grp1: TGroupBox;
    lbl1: TLabel;
    edtServerAddress: TEdit;
    btnClose: TButton;
    btnHelp: TButton;
    lbl7: TLabel;
    seServerPort: TSpinEdit;
    lbl2: TLabel;
    btnTest: TButton;
    procedure btnTestClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

function ShowOptionForm(Settings: TRTXSettings): Boolean;

implementation

{$R *.DFM}

uses
  CTXConsts;

function ShowOptionForm(Settings: TRTXSettings): Boolean;
begin
  with Settings, TCTXOptionForm.Create(Application) do
  try
    edtServerAddress.Text := ServerAddress;
    seServerPort.Value := ServerPort;

    Result := ShowModal = mrOk;
    if Result then
    begin
      ServerAddress := Trim(edtServerAddress.Text);
      ServerPort := seServerPort.Value;
    end;
  finally
    Free;
  end;
end;

procedure TCTXOptionForm.btnTestClick(Sender: TObject);
var
  RTXObj: Variant;
begin
  inherited;
  try
    RTXObj := CreateOleObject('RTXServer.RTXObj');
    RTXObj.ServerIP := Trim(edtServerAddress.Text);
    RTXObj.ServerPort := seServerPort.Value;
    InfoDlg(SRTXTestSucc);
  except
    ErrorDlg(SRTXTestError);
  end;
end;

end.
