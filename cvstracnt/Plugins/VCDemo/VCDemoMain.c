/*******************************************************************************
* ������ƣ�CVSTracNT
* ��Ԫ���ƣ�VC ������ӹ�������Ԫ
* ��Ԫ���ߣ��ܾ��� (zjy@cnpack.org)
* ��    ע��
* ����ƽ̨��PWindows XP SP2 + VC6
* �� �� �����õ�Ԫ�е��ַ������ϱ��ػ�����ʽ
* ��Ԫ��ʶ��$Id: VCDemoMain.c,v 1.1 2005/04/29 02:10:01 zjy Exp $
* ���¼�¼��2005.04.13
*               ������Ԫ
*******************************************************************************/

#include <WINDOWS.H>
#include "CTPluginIntf.h"

/* DLL ��ں��� */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					           )
{
  switch (ul_reason_for_call)
  {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
  }
  return TRUE;
}

/* �����Ϣ */
TPluginInfo PluginInfo = 
{
  sizeof(TPluginInfo),
  "VC ���Բ��",
  "ʹ�� VC �����Ĳ��Բ��",
  {1, 0, 0, 0},
  "�ܾ���",
  "http://www.cnpack.org",
  "master@cnpack.org"  
};

/* ������ӿ� */
PHostIntf Host;

/* ����ӿ� */
TPluginIntf Plugin;

/* ���ز����Ϣ�ṹ */
PPluginInfo CTAPI GetPluginInfo () {
  return &PluginInfo;
}

/* ִ�з������񵥸�����Ϣ���� */
BOOL CTAPI Execute (char * IniFileName, PTicketInfo TicketInfo) {
  /* Todo: ������Ϣ */
  return TRUE;
}

/* �������������ò�������������粻�����ÿ���Ϊ NULL */
BOOL CTAPI ConfigPlugin (HWND Owner) {
  MessageBox(Owner, "���� VC ���Բ��", "����", MB_OK | MB_ICONINFORMATION);
  return TRUE;
}

/* �����ݿ����ý��������ò���������粻�����ÿ���Ϊ NULL */
BOOL CTAPI ConfigDatabase (HWND Owner, char * DBName, char * DBFileName, 
                           char * IniFileName) {
  MessageBox(Owner, "�������ݿ�֪ͨ��ʽ", "����", MB_OK | MB_ICONINFORMATION);
  return TRUE;
}

/* ��������������л��¼� */
void CTAPI LangChanged (int LangID) {
  /* Todo: �л��������� */
}
  
/* ��������Ĺ���������õĺ�������д���ʱ��Ҫ�� def �ļ��е����ú��� */
DllExport BOOL CTAPI InitProc001 (PHostIntf HostIntf, PPluginIntf * PluginIntf)
{
  Host = HostIntf;
  memset(&Plugin, 0, sizeof(TPluginInfo));
  Plugin.dwSize = sizeof(TPluginInfo);
  Plugin.GetPluginInfo = GetPluginInfo;
  Plugin.Execute = Execute;
  Plugin.ConfigPlugin = ConfigPlugin;
  Plugin.ConfigDatabase = ConfigDatabase;
  Plugin.LangChanged = LangChanged;
  *PluginIntf = &Plugin;
  return TRUE;
}
