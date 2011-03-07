unit CTConsts;
{* |<PRE>
================================================================================
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ��������嵥Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע�������������嵥Ԫ
* ����ƽ̨��PWindows Server 2003 + Delphi 7.0
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTConsts.pas,v 1.7 2008/06/01 16:24:00 zjy Exp $
* ���¼�¼��2003.11.09
*               ������Ԫ
================================================================================
|</PRE>}

interface

type
  TNotifyKind = (nkNone, nkPlugin, nkOther);

  TSCMKind = (skNone, skCvs, skSvn, skGit);

  PDBOptionInfo = ^TDBOptionInfo;
  TDBOptionInfo = record
    Database: string;
    SCM: TSCMKind;
    Home: string;
    Module: string;
    CvsUser: string;
    Charset: string;
    Passwd: Boolean;
    NotifyKind: TNotifyKind;
  end;

const
  csIniName = 'CVSTracSvc.ini';
  csCTSenderName = 'CTSender.exe';
  csCVSTracSvcName = 'CVSTracSvc.exe';
  csServiceName = 'CVSTracService';
  csServiceDesc = 'CVSTrac Service';
  csDBDirName = 'Database';
  csLangDirName = 'Lang';
  csPluginDirName = 'Plugin';
  csLogDirName = 'Log';
  csDefaultPort = 2040;
  csActiveSection = 'Active';
  csDefBackupCount = 7;

  csSCMs: array[TSCMKind] of string = ('', 'cvs', 'svn', 'git');
  csSCMNames: array[TSCMKind] of string = ('', 'CVS', 'Subversion', 'GIT');

resourcestring
  SDefSenderName = '[CVSTrac]';

var
  // FileName
  SExeName: string = 'cvstrac_chs.exe';
  SReadmeName: string = 'Readme_chs.txt';

  // CTOMainForm
  SAppTitle: string = 'CVSTrac ���ó���';
  SDeleteQuery: string = '��ȷ��Ҫɾ����һ����';
  SAutoGenHisFileQuery: string =
    '���ó������� %d �� CVS �ֿ��²����� history �ļ���' + #13#10 +
    '�������������ʹ���� 2.5.x ����߰汾�� CVSNT ���¡�' + #13#10#13#10 +
    'CVSTrac ��ʱ���߹��������� history �ļ��е����ݼ�¼��' + #13#10 +
    '���Ƿ���Ҫ�Զ�Ϊ��Щ�ֿⴴ�� history �ļ���' + #13#10#13#10 +
    '���� history �������ܻ���Ҫ�� cvs commit -f -R ����' + #13#10 +
    'ǿ�ƽ���һ���ύ�������ʱ�����п������ݡ�';
  SGetDir: string = '��ѡ�����ݿ��ļ�Ŀ¼';
  SImportOk: string = '�Զ�������ɣ�����ʼ�����ݿ� %d ����' + #13#10#13#10 +
    '�����Ե�����������ť������ CVSTrac ҳ�档' + #13#10 +
    '��ʼ���û��������붼�� setup';
  SImportEmpty: string = 'û����Ҫ��ʼ���� CVS �ֿ⣡';
  SInitRepository: string = '���Ƿ���Ҫ�Զ����� CVS �ֿⲢ��ʼ�����ݿ⣿';
  SUseStr: string = 'ʹ��';
  SRestartService: string = '��������ֻ��������������������Ч���Ƿ���������������';
  SNotifyKinds: array[TNotifyKind] of string = ('��', '֪ͨ��', '����');
  SBackupOk: string = '���ݿⱸ����ɣ�';
  SDBFormatError: string = '���ݿ��ʽ����';
  SDBIsSQLite3: string = '���ݿ� %s �Ѿ����µĸ�ʽ�ˣ�';
  SDBUpgradeSucc: string = '���ݿ� %s �����ɹ���';
  SDBUpgradeFail: string = '���ݿ� %s ����ʧ�ܣ�';
  SDBUpgradeAllSucc: string = '�ɹ��������ݿ� %d ����';
  SDBUpgradeQuery: string = 'CVSTracNT 2.x ʹ���µ����ݿ��ʽ��' + #13#10 +
    '����Ҫ�����������ݿ��ļ���';

  // CTOEditForm
  SEditIsEmpty: string = '���ݿ����Ʋ���Ϊ�գ�';
  SGetCVSDir: string = '��ѡ�� CVS �ֿ�Ŀ¼';
  SNotCVSDir: string = '��Ŀ¼���ܲ��� CVS �ֿ�Ŀ¼���Ƿ������';
  SExportSucc: string = '�û��б����ɹ���';
  SExportFail: string = '�û��б���ʧ�ܣ�';
  SImportSucc: string = '�û��б���ɹ���';
  SImportFail: string = '�û��б���ʧ�ܣ�';

implementation

end.


