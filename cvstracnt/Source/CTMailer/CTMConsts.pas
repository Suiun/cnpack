unit CTMConsts;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��ʼ��������嵥Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTMConsts.pas,v 1.2 2008/07/10 13:07:47 zjy Exp $
* ���¼�¼��2005.04.01
*               ������Ԫ
================================================================================
|</PRE>}

interface

const
  csConnectTimeOut = 60;

var
  SMailerName: string = '�ʼ����';
  SMailerComment: string = '���񵥸���ʱ�����ʼ�֪ͨ��ָ��������';

  SBeginTest: string = '��ʼ�����ʼ�����...';
  SBeginConnect: string = '���������ʼ�������...';
  SBeginLogin: string = '����ִ�е�¼��֤...';
  STestSucc: string = '�ʼ����Ӳ���ͨ����';
  SLoginFail: string = '��¼��֤ʧ�ܣ�';
  STestFail: string = '�ʼ����Ӳ���ʧ��:';
  SCharSet: string = 'GB2312';
  
implementation

end.
