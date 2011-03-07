/*******************************************************************************
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ�C ����ӿڶ��嵥Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��ʹ�� C/C++ ��д CVSTracNT ���ʱ����Ҫ������ͷ�ļ���ʵ�ֲ�����
*           InitProc001 ��������ʾ�����̡�
* ����ƽ̨��PWindows XP SP2 + VC6
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: CTPluginIntf.h,v 1.2 2007/02/09 12:08:45 zjy Exp $
* ���¼�¼��2005.04.13
*               ������Ԫ
*******************************************************************************/

#ifndef CTPLUGININTF_H
#define CTPLUGININTF_H

#ifdef __cplusplus
  #define DllExport    extern "C"
#else
  #define DllExport    extern
#endif

#define CTAPI          __stdcall

/*******************************************************************************
* ������ӿ�
*******************************************************************************/

/* �汾�Žṹ */
typedef struct VERSION_struct {
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwReleaseVersion;
  DWORD dwBuildNumber;
} TVersion, * PVersion;

/* �������ṩ�ķ���ӿڽṹ */
typedef struct HOST_INTF_struct {
  DWORD dwSize;                           /* �ṹ��С */
  TVersion Version;                       /* ������汾�� */
  char * (CTAPI * GetDBPath) ();          /* ȡ�����ݿ��·�� */
  char * (CTAPI * GetLangPath) ();        /* ȡ�ö����ļ�·�� */
  int (CTAPI * GetLangID) ();             /* ȡ������ǰ������ ID */
  void (CTAPI * Log) (char * Text);       /* ������������־ */
} HOST_INTF, THostIntf, * PHostIntf;

/*******************************************************************************
* ����ӿ�
*******************************************************************************/

/* ������Ϣ�ṹ */
typedef struct TICKET_INFO_struct {
  DWORD dwSize;                  /* �ṹ��С */
  char * DBName;                 /* ���ݿ����� */
  char * DBFileName;             /* ����ȫ·���ļ��� */
  char * LocalServer;            /* ���ط����� URL */
  int Port;                      /* ���ط���˿ں� */
  int TicketNo;                  /* ���񵥱�� */
  char * TicketType;             /* ���� */
  char * TicketStatus;           /* ״̬ */
  char * OrigTime;               /* ����ʱ�� */
  char * ChangeTime;             /* �޸�ʱ�� */
  char * DerivedFrom;            /* ������ */
  char * Version;                /* ��ذ汾�� */
  char * AssignedTo;             /* ָ���޸��� */
  char * Severity;               /* ���س̶� */
  char * Priority;               /* ���ȼ� */
  char * SubSystem;              /* ��ϵͳ */
  char * Owner;                  /* ������ */
  char * Title;                  /* ���� */
  char * Description;            /* ���� */
  char * Remarks;                /* ע�� */
  char * Contact;                /* ��ϵ��ʽ */
  char * Modificator;            /* �����޸��� */
  // Added in v2.0.1 
  char * Extra_Name[5];          /* ��չ�ֶ����� */
  char * Extra[5];               /* ��չ�ֶ�ֵ */
} TICKET_INFO, TTicketInfo, * PTicketInfo;
  
/* �����Ϣ�ṹ */
typedef struct PLUGIN_INFO_struct {
  DWORD dwSize;                  /* �ṹ��С */
  char * Name;                   /* ������� */
  char * Comment;                /* ������� */
  TVersion Version;              /* ����汾�� */
  char * Author;                 /* ������� */
  char * WebSite;                /* ������վ */
  char * Email;                  /* �������� */
} PLUGIN_INFO, TPluginInfo, * PPluginInfo;

/* �ɲ��ʵ�ֵĽӿڽṹ */
typedef struct PLUGIN_INTF_struct {
  DWORD dwSize;                                       /* �ṹ��С */
  PPluginInfo (CTAPI * GetPluginInfo) ();             /* ���ز����Ϣ�ṹ */

  /* ִ�з������񵥸�����Ϣ���� */
  BOOL (CTAPI * Execute) (char * IniFileName,         /* ���ݿ��ļ���ص�ȫ·�� INI �ļ��� */
                          PTicketInfo TicketInfo);    /* ������Ϣ */

  /* �������������ò�������������粻�����ÿ���Ϊ NULL */
  BOOL (CTAPI * ConfigPlugin) (HWND Owner);           /* �������� */

  /* �����ݿ����ý��������ò���������粻�����ÿ���Ϊ NULL */
  BOOL (CTAPI * ConfigDatabase) (HWND Owner,          /* �������� */
                                 char * DBName,       /* �������õ����ݿ��� */
                                 char * DBFileName,   /* ���ݿ�ȫ·���ļ��� */
                                 char * IniFileName); /* ���ݿ���ص�ȫ·�� INI �ļ��� */

  /* ��������������л��¼� */
  void (CTAPI * LangChanged) (int LangID);            /* �µ����� ID */
} PLUGIN_INTF, TPluginIntf, * PPluginIntf;

/* ��������Ĺ���������õĺ��� */
DllExport BOOL CTAPI InitProc001 (PHostIntf HostIntf,        /* �����򴫵������Ľӿڽṹ */
                                  PPluginIntf * PluginIntf); /* ���ظ�������Ĳ���ṹָ�� */

#endif /* CTPLUGININTF_H */