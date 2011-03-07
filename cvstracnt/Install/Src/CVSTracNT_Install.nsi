;******************************************************************************
;                                CVSTracNT ���İ�
;                   ���İ�Ȩ (C)Copyright 2003-2007 CnPack ������
;******************************************************************************

; ���½ű��������� CVSTracNT ���İ� װ���� CVSTracNT.exe �ļ�
; �ýű����� NSIS 2.0 �±���ͨ������֧�ָ��ͣ�����ߣ��İ汾��ʹ��ʱ��ע��

!include "MUI.nsh"

;------------------------------------------------------------------------------
; ����汾�ţ�����ʵ�ʰ汾�Ž��и���
;------------------------------------------------------------------------------

; ������汾��
!define VER_MAJOR "2"
; ����Ӱ汾��
!define VER_MINOR "0.1_20080601"

;------------------------------------------------------------------------------
; ��Ҫ�����Դ�����ַ���
;------------------------------------------------------------------------------

; ��ݷ�ʽ��
LangString SREADME 1033 "Readme"
LangString SREADME 2052 "�����ļ�"

LangString SLICENSE 1033 "License"
LangString SLICENSE 2052 "��Ȩ�ļ�"

LangString SOPTION 1033 "CVSTrac Option"
LangString SOPTION 2052 "CVSTrac ����"

LangString SUNINSTALL 1033 "Uninstall"
LangString SUNINSTALL 2052 "ж��"

; �ļ���
LangString README_FILE 1033 "Readme_enu.txt"
LangString README_FILE 2052 "Readme_chs.txt"

LangString LICENSE_FILE 1033 "License_enu.txt"
LangString LICENSE_FILE 2052 "License_chs.txt"

; �Ի�����ʾ��Ϣ
LangString SQUERYDELETE 1033 "Delete user data files and settings?$\n(If you want to keep them, please click [No].)"
LangString SQUERYDELETE 2052 "�Ƿ�ɾ���û������ļ���������Ϣ��$\n(����Ҫ������Щ�ļ������������ [��] ��ť)"

;------------------------------------------------------------------------------
; �������Ϣ
;------------------------------------------------------------------------------

!define SOFT_NAME "CVSTracNT"

; �������
!define FULL_NAME "${SOFT_NAME}"

; ��װ�����·��ָ��߱���
!define INSTALL_NAME "${SOFT_NAME}"

; �������
Name "${FULL_NAME} ${VER_MAJOR}.${VER_MINOR}"
; ��������
Caption "${FULL_NAME}"
; ���Ƶ�����
BrandingText "${INSTALL_NAME}"

; ��װ��������ļ���
OutFile "..\Output\CVSTracNT_${VER_MAJOR}.${VER_MINOR}.exe"

;------------------------------------------------------------------------------
; ��������ѡ��
;------------------------------------------------------------------------------

; �����ļ����Ǳ��
SetOverwrite on
; ����ѹ��ѡ��
SetCompress auto
; ѡ��ѹ����ʽ
SetCompressor /solid lzma
; �������ݿ��Ż�
SetDatablockOptimize on
; ������������д���ļ�ʱ��
SetDateSave on


;------------------------------------------------------------------------------
; �����ļ��� Modern UI ����
;------------------------------------------------------------------------------

!verbose 3

; ����Ҫ��ʾ��ҳ��

!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install-blue.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall-blue.ico"

!define MUI_ABORTWARNING

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "cnpack.bmp"

LicenseLangString SLICENSEFILE 1033 "..\..\Bin\License_enu.txt"
LicenseLangString SLICENSEFILE 2052 "..\..\Bin\License_chs.txt"

; ��װ����ҳ��
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE $(SLICENSEFILE)
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

; ж�س���ҳ��
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ��ɺ�ִ�����ó���
!define MUI_FINISHPAGE_RUN "$INSTDIR\CVSTracOption.exe"
; ��װ��ɺ���ʾ�����ļ�
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\$(README_FILE)"
; ��װ����Ҫ����
!define MUI_FINISHPAGE_NOREBOOTSUPPORT

!insertmacro MUI_PAGE_FINISH

;����֧��
!define MUI_LANGDLL_REGISTRY_ROOT "HKCU"
!define MUI_LANGDLL_REGISTRY_KEY "Software\CnPack"
!define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"
;!insertmacro MUI_LANGUAGE "TradChinese"

!verbose 4


;------------------------------------------------------------------------------
; ��װ��������
;------------------------------------------------------------------------------

; ���� WindowsXP ���Ӿ���ʽ
XPstyle on

; ��װ������ʾ����
WindowIcon on
; �趨���䱳��
BGGradient off
; ִ�� CRC ���
CRCCheck on
; ��ɺ��Զ��رհ�װ����
AutoCloseWindow true
; ��ʾ��װʱ����ʾ��ϸϸ�ڡ��Ի���
ShowInstDetails show
; ��ʾж��ʱ����ʾ��ϸϸ�ڡ��Ի���
ShowUninstDetails show
; �Ƿ�����װ�ڸ�Ŀ¼��
AllowRootDirInstall false

; Ĭ�ϵİ�װĿ¼
InstallDir "$PROGRAMFILES\CVSTracNT"
; ������ܵĻ���ע����м�ⰲװ·��
InstallDirRegKey HKLM \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\CVSTracNT" \
                "UninstallString"

;------------------------------------------------------------------------------
; ��װ�������
;------------------------------------------------------------------------------

; ѡ��Ҫ��װ�����
InstType "Typical"


;------------------------------------------------------------------------------
; ��װ��������
;------------------------------------------------------------------------------

Section "System Data"
  SectionIn 1
  ; �������·����ÿ��ʹ�ö���ı�
  SetOutPath $INSTDIR
  File "..\..\Bin\sqlite.dll"
  File "..\..\Bin\sqlite3.dll"
  File "..\..\Bin\CVSTracOption.exe"
  ExecWait "$INSTDIR\CVSTracOption.exe /u"
  File "..\..\Bin\cvstrac_chs.exe"
  File "..\..\Bin\cvstrac_enu.exe"
  File "..\..\Bin\CVSTracSvc.exe"
  File "..\..\Bin\CTSender.exe"
  File "..\..\Bin\Readme_chs.txt"
  File "..\..\Bin\Readme_enu.txt"
  File "..\..\Bin\License_chs.txt"
  File "..\..\Bin\License_enu.txt"
  File "..\..\Bin\cygwin1.dll"
  File "..\..\Bin\cygintl-1.dll"
  File "..\..\Bin\diff.exe"
  File "..\..\Bin\rcsdiff.exe"
  File "..\..\Bin\rlog.exe"
  File "..\..\Bin\co.exe"
  File "..\..\Bin\sh.exe"
  
  CreateDirectory "$INSTDIR\Database"
  CreateDirectory "$INSTDIR\Log"

  SetOutPath "$INSTDIR\Plugin"
	File "..\..\Bin\Plugin\*.dll"

  SetOutPath "$INSTDIR\Lang\2052"
	File "..\..\Bin\Lang\2052\*.*"

  SetOutPath "$INSTDIR\Lang\1033"
	File "..\..\Bin\Lang\1033\*.*"

  ; Ϊ Windows ж�س���д���ֵ
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\CVSTracNT" "DisplayName" "${FULL_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\CVSTracNT" "UninstallString" '"$INSTDIR\uninst.exe"'

  ; ������ʼ�˵���
  CreateDirectory "$SMPROGRAMS\${FULL_NAME}"
  CreateShortCut "$SMPROGRAMS\${FULL_NAME}\$(SREADME).lnk" "$INSTDIR\$(README_FILE)"
  CreateShortCut "$SMPROGRAMS\${FULL_NAME}\$(SLICENSE).lnk" "$INSTDIR\$(LICENSE_FILE)"
  CreateShortCut "$SMPROGRAMS\${FULL_NAME}\$(SOPTION).lnk" "$INSTDIR\CVSTracOption.exe"
  CreateShortCut "$SMPROGRAMS\${FULL_NAME}\$(SUNINSTALL) ${FULL_NAME}.lnk" "$INSTDIR\uninst.exe"

  ; д������ж�س���
  WriteUninstaller "$INSTDIR\uninst.exe"

  ExecWait "$INSTDIR\CVSTracOption.exe /i"
SectionEnd


;------------------------------------------------------------------------------
; ��װʱ�Ļص�����
;------------------------------------------------------------------------------

; ��װ�����ʼ������
Function .onInit

  ; ��ʾѡ�����ԶԻ���
  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd


;------------------------------------------------------------------------------
; ж�س�������ػص�����
;------------------------------------------------------------------------------

; ж�س�������
Section "Uninstall"
  ExecWait "$INSTDIR\CVSTracOption.exe /u"

  Delete "$INSTDIR\*.exe"
  Delete "$INSTDIR\*.dll"
  Delete "$INSTDIR\*.txt"
	Delete "$INSTDIR\Lang\*.*"
	Delete "$INSTDIR\Plugin\*.dll"
	RMDir /r "$INSTDIR\Lang"
  RMDir /r "$SMPROGRAMS\${FULL_NAME}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\CVSTracNT"
  ; ��ʾ�û��Ƿ�ɾ�������ļ�
  MessageBox MB_YESNO|MB_ICONQUESTION "$(SQUERYDELETE)" IDNO NoDelete

  RMDir /r "$INSTDIR\Database"
  RMDir /r "$INSTDIR"
NODelete:
SectionEnd


; ����