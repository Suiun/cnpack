CVSTracNT ���İ�Դ��˵�� 
========================

CnPack ������ �ܾ���
http://www.cnpack.org

1. Ŀ¼�ṹ
-----------
BuildAll.bat    �Զ�����������

Bin             ��Ŷ������ļ������� Readme
  co.exe            ���� check out �ļ���cvstrac ��ʹ��
  cvstrac_*.exe     cvstrac �����򣨶������ cygwin �±������ɣ�����
  CVSTracOption.exe ���ù��ߣ�Delphi 7 �±�������
  CVSTracSvc.exe    cvstrac ��Ƿ������Delphi 7 �±�������
  cygintl-1.dll     diff.exe ʹ�õ��Ŀ�
  cygwin1.dll       cvstrac.exe ���� cygwin �±���ĳ���ʹ�õĿ�
  diff.exe          ���ڱȽ�Դ�����ļ�
  License_*.txt     ��Ȩ�ļ������
  rcsdiff.exe       ���ڱȽ� RCS �ļ��в�ͬ�汾������
  Readme_*.txt      ����˵���ļ������
  rlog.exe          ����ȡ�� RCS �ļ��汾��Ϣ
  sh.exe            cygwin ����ͨ���ܵ������ⲿ����ʱʹ�õ���ǳ���
  sqlite.dll        ���ó�����������������ݿ�

  Database          ������ݿ��ļ�
  Lang              ��������ļ���һ������һ��Ŀ¼
  Log               ��־�ļ�Ŀ¼
  Plugin            ����֪ͨ���Ŀ¼

Dcu             ��ű�����ʱ�ļ�

Make            ����Զ� Make �ļ�

Source          Դ����Ŀ¼
  cvstrac           cvstrac ��ֲ�棬NT �������� CVSTracNT_CHS ��ǩȡ��
  CVSTracOption     ���ù���Դ�룬Delphi 7 �±���
  CVSTracService    cvstrac ��Ƿ���Դ�룬Delphi 7 �±���
  CTSender          ���񵥸���֪ͨ����Դ�룬����֪ͨ�����Delphi 7 �±���
  CTMailer          �ʼ�֪ͨ���Դ�룬Delphi 7 �±���
  CTNetSend         ��ʹ����֪ͨ���Դ�룬Delphi 7 �±���
  Public            Դ�빫��Ŀ¼
  MultiLang         �����Դ�����Ŀ¼

Plugins         ���Դ��Ŀ¼
  Include           ���������ļ�
  VCDemo            ʹ�� VC6 ��д�ļ򵥲��ʾ��


2. Delphi Դ�������
--------------------
Delphi Դ������ D7 �±���ͨ��������ʱ��Ҫʹ�� CnPack ���е� CnCommon.pas �Լ����������������� CnPack �� CVS ��������ȡ�� cnpack ģ��Ĵ����� cvstracnt ����ͬһ��Ŀ¼�±��롣


3. cvstrac Դ�������
---------------------
���벽�裺

  * ��װ cygwin (http://www.cygwin.com)����װʱҪѡ�� develop �µ� gcc��automake��
  * ���� sqlite Դ�� (http://www.sqlite.org)���� cygwin �±��롣
  * ȡ�� CVSTracNT_CHS ��֧�� cvstrac Դ��ŵ� Source/cvstrac_chs Ŀ¼��
  * ȡ�� CVSTracNT_ENU ��֧�� cvstrac Դ��ŵ� Source/cvstrac_enu Ŀ¼��
  * ִ�� BuildAll.bat ���� cvstrac Դ�뼰���ɰ�װ����

