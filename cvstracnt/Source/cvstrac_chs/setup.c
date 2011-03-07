/*
** Copyright (c) 2002 D. Richard Hipp
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public
** License along with this library; if not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA  02111-1307, USA.
**
** Author contact information:
**   drh@hwaci.com
**   http://www.hwaci.com/drh/
**
** �������ķ���: �ܾ��� (zjy@cnpack.org) 2003-11-09
**
*******************************************************************************
**
** Implementation of the Setup page
*/
#include <assert.h>
#include "config.h"
#include "setup.h"


/*
** Output a single entry for a menu generated using an HTML table.
** If zLink is not NULL or an empty string, then it is the page that
** the menu entry will hyperlink to.  If zLink is NULL or "", then
** the menu entry has no hyperlink - it is disabled.
*/
static void menu_entry(
  const char *zTitle,
  const char *zLink,
  const char *zDesc
){
  @ <dt>
  if( zLink && zLink[0] ){
    @ <a href="%s(zLink)">%h(zTitle)</a>
  }else{
    @ %h(zTitle)
  }
  @ </dt>
  @ <dd>%h(zDesc)</dd>
}

/*
** WEBPAGE: /setup
*/
void setup_page(void){
  /* The user must be at least the administrator in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okAdmin ){
    login_needed();
    return;
  }

  common_standard_menu("setup", 0);
  common_add_help_item("CvstracAdmin");
  common_header("���ò˵�");

  @ <dl id="setup">
  if( g.okSetup ){
    menu_entry(mprintf("%s �ֿ�",g.scm.zName), "setup_repository",
      "ָ���÷��������ӵ��Ĳֿ�·����");
    if( g.scm.pxUserWrite || g.scm.pxUserRead ){
      menu_entry("�û����ݿ�", "setup_user", 
        mprintf("���� CVSTrac ��δ��� %h �û�"
                "���������ݿ⡣", g.scm.zName));
    }
    menu_entry("��־�ļ�", "setup_log",
      "���Ʒ�����־�ļ�������رա�");
    menu_entry("����", "setup_attach",
      "��������ĸ����ļ���󳤶ȡ�");
    menu_entry("��������", "setup_throttle",
      "�������������ֹ wiki ������");
  }
  menu_entry("��������", "setup_enum?e=type",
    "�г��ܱ����뵽ϵͳ�е�����"
    "���͡�");
  menu_entry("����״̬", "setup_enum?e=status",
    "�������� \"״̬\" ���������ֵ��");
  menu_entry("������Ĭ��ֵ", "setup_newtkt",
    "ָ��������һ���µ�����ʱ���Զ��趨��"
    "����Ĭ��ֵ��");
  menu_entry("��ϵͳ����", "setup_enum?e=subsys",
    "�г��������� \"��ϵͳ\" ����"
    "����ʹ�õ����ơ�");
  menu_entry("�Զ����ֶ�", "setup_udef",
    "�������񵥱��п����û��Զ�������ݿ���Ŀ��");
  if( g.okSetup ){
    menu_entry("�ȽϺ͹��˳���", "setup_diff",
      "ָ��һ���ⲿ�����ű������Ƚ�ͬһ�ļ������汾"
      "֮��Ĳ����Լ���������ļ���");
    menu_entry("�ⲿ����", "setup_tools",
      "������ CVSTrac ������ⲿ���ߡ�" );
    menu_entry("����֪ͨ", "setup_chng",
      "����һ���ⲿ���������񵥴������޸�ʱ"
      "�Զ������Ի��֪ͨ��");
    menu_entry("������ʽ", "setup_style",
      "����ҳü��ҳ�š���ʽ�������ҳ��Ԫ�ء�");
    menu_entry("�û�����", "setup_interface",
      "�����û����湦�ܡ�" );
    menu_entry("Wiki ���", "setup_markup",
      "����ɶ��Ƶ� Wiki ��ǡ�" );
    menu_entry("���ݺͻָ�", "setup_backup",
      "�������ݿⱸ���ļ���ӱ����ļ���"
      "�ָ����ݿ⡣");
    menu_entry("ʱ���ߺ� RSS", "setup_timeline", 
      "����ʱ���� Cookie �����ں� RSS \"Time To Live\"��");
  }
  @ </dl>
  common_footer();
}

/*
** WEBPAGE: /setup_repository
*/
void setup_repository_page(void){
  const char *zRoot, *zOldRoot;
  const char *zModule, *zOldModule;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** The "r" query parameter is the name of the CVS repository root
  ** directory.  Change it if it has changed.
  */
  zOldRoot = db_config("cvsroot","");
  zRoot = P("r");
  if( zRoot && strcmp(zOldRoot,zRoot)!=0 ){
    db_execute("REPLACE INTO config(name,value) VALUES('cvsroot','%q');",
      zRoot);
    zOldRoot = zRoot;
    db_config(0,0);
  }

  /*
  ** The "m" query parameter is the name of the module within the
  ** CVS repository that this CVSTrac instance is suppose to track.
  ** Change it if it has changed.
  */
  zOldModule = db_config("module","");
  zModule = P("m");
  if( zModule && strcmp(zOldModule,zModule)!=0 ){
    db_execute("REPLACE INTO config(name,value) VALUES('module','%q');",
      zModule);
    zOldModule = zModule;
    db_config(0,0);
  }

  /*
  ** The "rrh" query parameter is present if the user presses the
  ** "Reread Revision History" button.  This causes the CVSROOT/history
  ** file to be reread.  Do this with caution as it erases any edits
  ** to the history that are currently in the database.  Only the
  ** setup user can do this.
  */
  if( P("rrh") ){
    common_add_action_item("setup_repository", "ȡ��");
    common_header("ȷ�����¶�ȡ�ֿ������ļ�");
    @ <h3>���棡</h3>
    @ <p>
    @ ����������� <b>���¹���</b> ��ʽ������ʷ���ݿ⣬
    @ �����ύ��¼���������±�š�����ܻ������񵥺�
    @ wiki ҳ�����ύ��¼֮��Ĺ�ϵ�����Լ����ύע
    @ �͵��޸�ͬ���ᶪʧ��</p>
    @
    @ <p> һ������ȫ�취��ѡ�� <b>����ɨ��</b>������
    @ �����Ա����Ѵ��ڵ��ύ��ź��ύע���޸ġ�
    @ </p>
    @
    @ <p>�����������������ȴ���һ�����ݿ� <a href="setup_backup">
    @ ����</a> ����������������κδ���ʱ�����Իָ�
    @ ��ԭ����״̬��</p>
    @
    @ <form action="%s(g.zPath)" method="POST">
    @ <p>
    @ <input type="submit" name="rrh2" value="���¹���">
    @ ���¿�ʼ�����ύ��¼���ݿ⡣
    @ </p>
    @ <p>
    @ <input type="submit" name="rrh3" value="����ɨ��">
    @ ����ʹ�����е��ύ��¼��š�
    @ </p>
    @ <p>
    @ <input type="submit" name="cancel" value="ȡ��">
    @ ȡ���˴β�����
    @ </p>
    @ </form>
    common_footer();
    return;
  }
  if( P("rrh2") ){
    db_execute(
      "BEGIN;"
      "DELETE FROM chng WHERE not milestone;"
      "DELETE FROM filechng;"
      "DELETE FROM file;"
      "UPDATE config SET value=0 WHERE name='historysize';"
    );

    if( g.scm.pxHistoryReconstructPrep ) g.scm.pxHistoryReconstructPrep();

    db_execute("COMMIT; VACUUM;");

    db_config(0,0);
    history_update(0);
  }
  if( P("rrh3") ){
    db_execute(
      "BEGIN;"
      "DELETE FROM filechng WHERE rowid NOT IN ("
         "SELECT min(rowid) FROM filechng "
         "GROUP BY filename, vers||'x'"
      ");"
      "DELETE FROM chng WHERE milestone=0 AND cn NOT IN ("
         "SELECT cn FROM filechng"
      ");"
      "UPDATE config SET value=0 WHERE name='historysize';"
    );

    if( g.scm.pxHistoryRescanPrep ) g.scm.pxHistoryRescanPrep();

    db_execute(
      "COMMIT;"
      "VACUUM;"
    );
    db_config(0,0);
    history_update(1);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminRepository");
  common_header("���òֿ�");
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>������ı༭��������
  @ %s(g.scm.zName) �ֿ��Ŀ¼������·����
  if( g.scm.canFilterModules ){
    @ �������Ҫ����
    @ �÷���ֻ�ܿ�
    @ ���� %s(g.scm.zName) �ֿ���һ���Ӽ����ļ�
    @ �����磬�����ϣ��ֻ�ܿ���һ��ģ�飬
    @ ���ֿ⻹����������������ص�ģ�飩��
    @ ���ڵڶ�����������������뿴�����ļ�����
    @ ·��ǰ׺��ģ��ǰ׺����ʹ��������ʽ������
    @ ƥ����ģ�顣��ע�⣬һ��������ʽ�����
    @ ���׿�ʼ���(������ ^ ��ͷ)�Żᱻ��Ϊ����
    @ Ч�ġ�
  }
  @ </p>
  @ <table>
  @ <tr>
  @   <td align="right">%s(g.scm.zName) �ֿ�:</td>
  @   <td><input type="text" name="r" size="40" value="%h(zOldRoot)"></td>
  @ </tr>

  if( g.scm.canFilterModules ){
    @ <tr>
    @   <td align="right">ģ��ǰ׺:</td>
    @   <td><input type="text" name="m" size="40" value="%h(zOldModule)"></td>
    @ </tr>
  }

  @ </table><br>
  @ <input type="submit" value="�ύ">
  @
  @ <p>
  @ ��ǰ���޸��� %s(g.scm.zName) �ֿ�·����ͨ�������ܻ���Ҫ
  @ �������İ�ť�����µĲֿ�������
  @ ��ȡ�����ļ�����Ҳ����ʹ�������ť
  @ ������ͬ������ԭ����ȡ����ʧ�ܻ�
  @ ���ֹ��޸��������ļ����������(�Ⲣ����һ��������)��
  @ <p><input type="submit" name="rrh" value="���¶�ȡ�ֿ�"></p>
  @ </form>
  @ <hr>
  common_footer();
}

/*
** WEBPAGE: /setup_user
*/
void setup_user_page(void){
  const char *zWPswd, *zOldWPswd;

  /* The user must be at least the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** The "wpw" query parameter is "yes" if the CVSROOT/passwd file is
  ** writable and "no" if not.
  ** Change it if it has changed.
  */
  zOldWPswd = db_config("write_cvs_passwd","yes");
  zWPswd = P("wpw");
  if( zWPswd && strcmp(zOldWPswd,zWPswd)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('write_cvs_passwd','%q');",
      zWPswd
    );
    zOldWPswd = zWPswd;
    db_config(0,0);
  }

  /*
  ** Import users out of the CVSROOT/passwd file if the user pressed
  ** the Import Users button.  Only setup can do this.
  */
  if( P("import_users") && g.scm.pxUserRead ){
    g.scm.pxUserRead();
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminUserDatabase");
  common_header("�����û����ݿ�����");
  if( g.scm.pxUserWrite ){
    @ <form action="%s(g.zPath)" method="POST">
    @ <p>CVSTrac �ܸ��� CVSTrac �������û���������
    @ �Զ����� CVSROOT/passwd �ļ������������
    @ ������ֹ��һ���ܡ�</p>
    @ <p>���û����д�� CVSROOT/passwd��
    cgi_optionmenu(0, "wpw", zOldWPswd, "��", "yes", "��", "no", NULL);
    @ <input type="submit" value="�ύ">
    @ </p>
    @ </form>
  }
  if( g.scm.pxUserRead ){
    @ <form action="%s(g.zPath)" method="POST">
    @ <p>ʹ������İ�ť�Զ����ݵ�ǰ CVSROOT/passwd �ļ�Ϊ
    @ ÿһ�����е��û����� CVSTrac �ʺš��µ��û������
    @ �� anonymous �����ʺ���ͬ��Ȩ�ޣ���� CVS �����û�
    @ ��д���������ȡ�����ύ��Ȩ�ޡ�</p>
    @ <p><input type="submit" name="import_users" value="���� CVS �û�"></p>
    @ </form>
  }
  common_footer();
}

/*
** WEBPAGE: /setup_log
*/
void setup_logfile_page(void){
  const char *zLog, *zOldLog;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** The "log" query parameter specifies a log file into which a record
  ** of all HTTP hits is written.  Write this value if this has changed.
  ** Only setup can make this change.
  */
  zOldLog = db_config("logfile","");
  zLog = P("log");
  if( zLog && strcmp(zOldLog,zLog)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('logfile','%q');",
      zLog
    );
    zOldLog = zLog;
    db_config(0,0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminLog");
  common_header("������־�ļ�");
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>����һ���ļ����������������жԸ÷���
  @ ���ķ�����־�����ս�������־����:
  @ </p>
  @ <p>��־�ļ�: <input type="text" name="log" size="40" value="%h(zOldLog)">
  @ <input type="submit" value="�ύ"></p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_newtkt
*/
void setup_newticket_page(void){
  char **azResult;
  const char *zState, *zOldState;
  const char *zAsgnto, *zOldAsgnto;
  const char *zType, *zOldType;
  const char *zPri, *zOldPri;
  const char *zSev, *zOldSev;

  /* The user must be at least the administrator in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okAdmin ){
    login_needed();
    return;
  }

  /*
  ** The "asgnto" query parameter specifies a userid who is assigned to
  ** all new tickets.  Record this value in the configuration table if
  ** it has changed.
  */
  zOldAsgnto = db_config("assignto","");
  zAsgnto = P("asgnto");
  if( zAsgnto && strcmp(zOldAsgnto,zAsgnto)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('assignto','%q');", zAsgnto
    );
    zOldAsgnto = zAsgnto;
    db_config(0,0);
  }

  /*
  ** The "istate" query parameter specifies the initial state for new
  ** tickets.  Record any changes to this value.
  */
  zOldState = db_config("initial_state","");
  zState = P("istate");
  if( zState && strcmp(zOldState,zState)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('initial_state','%q');",
      zState
    );
    zOldState = zState;
    db_config(0,0);
  }

  /*
  ** The "type" query parameter specifies the initial type for new
  ** tickets.  Record any changes to this value.
  */
  zOldType = db_config("dflt_tkt_type","");
  zType = P("type");
  if( zType && strcmp(zOldType,zType)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('dflt_tkt_type','%q');",
      zType
    );
    zOldType = zType;
    db_config(0,0);
  }

  /*
  ** The "pri" query parameter specifies the initial priority for new
  ** tickets.  Record any changes to this value.
  */
  zOldPri = db_config("dflt_priority","1");
  zPri = P("pri");
  if( zPri && strcmp(zOldPri,zPri)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('dflt_priority','%q');",
      zPri
    );
    zOldPri = zPri;
    db_config(0,0);
  }

  /*
  ** The "sev" query parameter specifies the initial severity for new
  ** tickets.  Record any changes to this value.
  */
  zOldSev = db_config("dflt_severity","1");
  zSev = P("sev");
  if( zSev && strcmp(zOldSev,zSev)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('dflt_severity','%q');",
      zSev
    );
    zOldSev = zSev;
    db_config(0,0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminNewTicket");
  common_header("����������Ĭ��ֵ");
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ѡ�񵱴���������ʱĬ�Ϸ��䵽���û���:</p><p>
  @ Ĭ�Ϸ���:
  azResult = db_query("SELECT id FROM user UNION SELECT '' ORDER BY id");
  cgi_v_optionmenu(0, "asgnto", zOldAsgnto, (const char**)azResult);
  @ </p>
  @
  @ <p>
  @ ѡ�񵱴���������ʱ�ĳ�ʼ״̬:</p><p>
  @ ��ʼ״̬:
  cgi_v_optionmenu2(0, "istate", zOldState, (const char**)db_query(
     "SELECT name, value FROM enums WHERE type='status'"));
  @ </p>
  @
  @ <p>
  @ ѡ�������񵥵�Ĭ������:</p><p>
  @ Ĭ������:
  cgi_v_optionmenu2(0, "type", zOldType, (const char**)db_query(
     "SELECT name, value FROM enums WHERE type='type'"));
  @ </p>
  @
  @ <p>
  @ ѡ�������񵥵�Ĭ�����ȼ�:</p><p>
  @ Ĭ�����ȼ�:
  cgi_optionmenu(0, "pri", zOldPri, "1", "1", "2", "2", "3", "3", "4", "4",
      "5", "5", NULL);
  @ </p>
  @
  @ <p>
  @ ѡ�������񵥵�Ĭ�����ض�:</p><p>
  @ Ĭ�����ض�:
  cgi_optionmenu(0, "sev", zOldSev, "1", "1", "2", "2", "3", "3", "4", "4",
      "5", "5", NULL);
  @ </p>
  @
  @ <p>
  @ <input type="submit" value="�ύ">
  @ </p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_interface
*/
void setup_interface_page(void){
  int atkt, ack, tkt, ck, cols, rows, st;
  const char *zBrowseUrl;
  const char *zWrap;
  int nCookieLife;

  /* The user must be at least the administrator in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okAdmin ){
    login_needed();
    return;
  }

  if( P("update") ){
    cols = atoi(PD("cols",db_config("wiki_textarea_cols",WIKI_TEXTAREA_COLS)));
    if (cols < 20) cols = 20;

    rows = atoi(PD("rows",db_config("wiki_textarea_rows",WIKI_TEXTAREA_ROWS)));
    if (rows < 5) rows = 5;

    db_execute(
      "REPLACE INTO config(name,value) VALUES('anon_ticket_linkinfo',%d);"
      "REPLACE INTO config(name,value) VALUES('anon_checkin_linkinfo',%d);"
      "REPLACE INTO config(name,value) VALUES('ticket_linkinfo',%d);"
      "REPLACE INTO config(name,value) VALUES('checkin_linkinfo',%d);"
      "REPLACE INTO config(name,value) VALUES('browse_url_cookie_life',%d);"
      "REPLACE INTO config(name,value) VALUES('default_browse_url','%q');"
      "REPLACE INTO config(name,value) VALUES('wiki_textarea_wrap','%q');"
      "REPLACE INTO config(name,value) VALUES('wiki_textarea_cols',%d);"
      "REPLACE INTO config(name,value) VALUES('wiki_textarea_rows',%d);"
      "REPLACE INTO config(name,value) VALUES('safe_ticket_editting',%d);",
      atoi(PD("atkt",db_config("anon_ticket_linkinfo","0"))),
      atoi(PD("ack",db_config("anon_checkin_linkinfo","0"))),
      atoi(PD("tkt",db_config("ticket_linkinfo","1"))),
      atoi(PD("ck",db_config("checkin_linkinfo","0"))),
      atoi(PD("cl",db_config("browse_url_cookie_life", "90"))),
      PD("bu",db_config("default_browse_url","dir")),
      PD("wrap",db_config("wiki_textarea_wrap",WIKI_TEXTAREA_WRAP)),
      cols,
      rows,
      atoi(PD("st",db_config("safe_ticket_editting", "0")))
    );
    db_config(0, 0);
  }

  atkt = atoi(db_config("anon_ticket_linkinfo","0"));
  ack = atoi(db_config("anon_checkin_linkinfo","0"));
  tkt = atoi(db_config("ticket_linkinfo","1"));
  ck = atoi(db_config("checkin_linkinfo","0"));
  st = atoi(db_config("safe_ticket_editting","0"));
  cols = atoi(db_config("wiki_textarea_cols",WIKI_TEXTAREA_COLS));
  rows = atoi(db_config("wiki_textarea_rows",WIKI_TEXTAREA_ROWS));
  zWrap = db_config("wiki_textarea_wrap",WIKI_TEXTAREA_WRAP);
  zBrowseUrl = db_config("default_browse_url","dir");
  nCookieLife = atoi(db_config("browse_url_cookie_life", "90"));

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminInterface");
  common_header("�����û�����");

  @ <form action="%s(g.zPath)" method="POST">
  @ <h1>���񵥺��ύ/��̱�������Ϣ</h1>
  @ <p>���񵥺��ύ/��̱�������Ϣ�����ڴ�����������ʵ��
  @ ������ʾ�����磬
  @ <a href="tktview?tn=1" title="��һ������">#1</a> ��
  @ <a href="chngview?cn=1" title="�ύ [1]: ��һ���ύ
  @ (�� anonymous)">[1]</a>��������ܽ��ṩ���û�����
  @ ����Ϣ������Ҫ���������ӣ��⽫����һ
  @ ��������ĸ���������ҳ���С���ӡ�
  @ �ύ������Ϣ����ͨ��������û��� Wiki
  @ ��ע���м����˴������ύ����ʱ��
  @ ���á�
  @ </p>
  @ <p>
  @ <label for="atkt"><input type="checkbox" name="atkt" id="atkt"
  @   %s(atkt?" checked":"") value="1">
  @ Ϊ�����û���������������Ϣ���ܡ�</label>
  @ <br>
  @ <label for="ack"><input type="checkbox" name="ack" id="ack"
  @   %s(ack?" checked":"") value="1">
  @ Ϊ�����û������ύ/��̱�������Ϣ���ܡ�</label>
  @ <br>
  @ <label for="tkt"><input type="checkbox" name="tkt" id="tkt"
  @   %s(tkt?" checked":"") value="1">
  @ Ϊ��¼�û���������������Ϣ���ܡ�</label>
  @ <br>
  @ <label for="ck"><input type="checkbox" name="ck" id="ck"
  @   %s(ck?" checked":"") value="1">
  @ Ϊ��¼�û������ύ/��̱�������Ϣ���ܡ�</label>
  @ </p>
  @ <p>
  cgi_submit("update", 0, 0, 0, 0, "�ύ");
  @ </p>
  @ </form>

  @ <form class="setup-section" action="%s(g.zPath)" method="POST">
  @ <h1>�ֿ�</h1>
  @ <p>������ֿ�ʱ��������ʾ�ļ���Ŀ¼�ķ�����
  @ <em>���</em> ��ͼ����ѹ���б�ķ�ʽ�������ļ�
  @ ��Ŀ¼��ʾ�������С�<em>��ϸ</em> ��ͼ
  @ Ϊÿһ���ļ�����ʾ���ڲֿ����������Ϣ��</p>
  @ <p><label for="bu0"><input type="radio" name="bu" id="bu0"
  @    %s(strcmp("dirview",zBrowseUrl)==0?" checked":"") value="dirview">
  @ ��ϸ��ͼ</label><br>
  @ <label for="bu1"><input type="radio" name="bu" id="bu1"
  @   %s(strcmp("dir",zBrowseUrl)==0?" checked":"") value="dir">
  @ �����ͼ</label>
  @ <p>
  cgi_submit("update", 0, 0, 0, 0, "�ύ");
  @ </p>
  @ </form>

  @ <form class="setup-section" action="%s(g.zPath)" method="POST">
  @ <h1>Cookies</h1>
  @ <p>
  @ �������û�������� Cookie ��Ҫ�����������
  @ �� Cookie ���������û��������ʽ����Ϊ�Ժ���ʵ���ѡ
  @ �����ʽ��<br>
  @ �ù��ܶ������û���Ч��<br>
  @ ����Ϊ 0 ����������� Cookie��
  @ </p>
  @ <p>
  @ Cookie ������:
  @ <input type="text" name="cl" value="%d(nCookieLife)" size=5> ��
  @ </p>
  @ <p>
  cgi_submit("update", 0, 0, 0, 0, "�ύ");
  @ </p>
  @ </form>

  @ <form class="setup-section" action="%s(g.zPath)" method="POST">
  @ <h1>Wiki �ı�����</h1>
  @ <p>ͨ���������µĲ��������� Wiki �ı�����/�༭�Ի���
  @ ���������з�ʽָ�������ı��ύ������ķ�ʽ��
  @ ������з�ʽ����Ϊ <em>Ӳ����</em>
  @ ��������ڵĵ����ı��Զ�����ʱ���Զ�����Ӳ�س�����
  @ <em>����</em> ���з�ʽ�򲻻��Զ�����Ӳ�س�����
  @ ���������ı���Ҫ����ԭʼ��ʽ�����ѡ��Ӧ����Ϊ
  @ <em>����</em> ��ʽ��</p>
  @ <p>�����������Ļ��СҲ�������á���ע�⣬
  @ ���õ�����ֻ��һ�� <i>���ֵ</i>��ĳЩ�ı��༭��
  @ ���ܸ�СһЩ��</p>
  @ <p>Wiki �ı����뻻��:
  cgi_optionmenu(0, "wrap", zWrap,
                 "physical", "Ӳ����", "virtual", "����", NULL);
  @ </p>
  @ <p>���������С:
  @ <input name="cols" size="3" value="%d(cols)"/> �� 
  @ <input name="rows" size="3" value="%d(rows)"/> ��
  @ </p>
  @ <p>
  cgi_submit("update", 0, 0, 0, 0, "�ύ");
  @ </p>
  @ </form>

  @ <form class="setup-section" action="%s(g.zPath)" method="POST">
  @ <h1>��ȫ�����񵥱༭</h1>
  @ <p>���ø�ѡ����� CVSTrac ��׼���༭
  @ ����ǰ���м�飬�����������һ�����ڸ������񵥵Ĳ�����ͻ��
  @ ������һ������
  @ </p>
  @ <p>
  @ <label for="st">
  @ <input type="checkbox" name="st" id="st" %s(st?" checked":"") value="1"/>
  @ ������ȫ���񵥱༭ģʽ��</label>
  @ <br>
  cgi_submit("update", 0, 0, 0, 0, "����");
  @ </p>
  @ </form>

  common_footer();
}

/*
** Generate a string suitable for inserting into a <TEXTAREA> that
** describes all allowed values for a particular enumeration.
*/
static char *enum_to_string(const char *zEnum){
  char **az;
  char *zResult;
  int i, j, nByte;
  int len1, len2, len3;
  int mx1, mx2, mx3;
  int rowCnt;
  az = db_query("SELECT name, value, color FROM enums "
                "WHERE type='%s' ORDER BY idx", zEnum);
  rowCnt = mx1 = mx2 = mx3 = 0;
  for(i=0; az[i]; i+=3){
    len1 = strlen(az[i]);
    len2 = strlen(az[i+1]);
    len3 = strlen(az[i+2]);
    if( len1>mx1 ) mx1 = len1;
    if( len2>mx2 ) mx2 = len2;
    if( len3>mx3 ) mx3 = len3;
    rowCnt++;
  }
  if( mx2<mx1 ) mx2 = mx1;
  nByte = (mx1 + mx2 + mx3 + 11)*rowCnt + 1;
  zResult = malloc( nByte );
  if( zResult==0 ) exit(1);
  for(i=j=0; az[i]; i+=3){
    const char *z1 = az[i];
    const char *z2 = az[i+1];
    const char *z3 = az[i+2];
    if( z1[0]==0 ){ z1 = "?"; }
    if( z2[0]==0 ){ z2 = z1; }
    if( z3[0] ){
      bprintf(&zResult[j], nByte-j, "%*s    %*s   (%s)\n",
              -mx1, z1, -mx2, z2, z3);
    }else{
      bprintf(&zResult[j], nByte-j, "%*s    %s\n", -mx1, z1, z2);
    }
    j += strlen(&zResult[j]);
  }
  db_query_free(az);
  zResult[j] = 0;
  return zResult;
}

/*
** Given text that describes an enumeration, fill the ENUMS table with
** coresponding entries.
**
** The text line oriented.  Each line represents a single value for
** the enum.  The first token on the line is the internal name.
** subsequent tokens are the human-readable description.  If the last
** token is in parentheses, then it is a color for the entry.
*/
static void string_to_enum(const char *zEnum, const char *z){
  int i, j, n;
  int cnt = 1;
  char *zColor;
  char zName[50];
  char zDesc[200];

  db_execute("DELETE FROM enums WHERE type='%s'", zEnum);
  while( isspace(*z) ){ z++; }
  while( *z ){
    assert( !isspace(*z) );
    for(i=1; z[i] && !isspace(z[i]); i++){}
    n = i>49 ? 49 : i;
    memcpy(zName, z, n);
    zName[n] = 0;
    z += i;
    while( *z!='\n' && isspace(z[1]) ){ z++; }
    if( *z=='\n' || *z==0 ){
      strcpy(zDesc, zName);
      zColor = "";
    }else{
      int lastP1 = -1;
      int lastP2 = -1;
      z++;
      for(j=i=0; *z && *z!='\n'; z++){
        if( j<199 && (j==0 || !isspace(*z) || !isspace(zDesc[j-1])) ){
          zDesc[j++] = *z;
        }
        if( *z=='(' ){ lastP1 = j-1; }
        else if( *z==')' ){ lastP2 = j-1; }
        else if( !isspace(*z) ){ lastP2 = -1; }
      }
      zDesc[j] = 0;
      if( lastP2>lastP1 && lastP1>1 ){
        zColor = &zDesc[lastP1+1];
        zDesc[lastP2] = 0;
        zDesc[lastP1] = 0;
        j = lastP1;
        while( j>0 && isspace(zDesc[j-1]) ){ j--; }
        zDesc[j] = 0;
      }else{
        j = strlen(zDesc);
        while( j>0 && isspace(zDesc[j-1]) ){ j--; }
        zDesc[j] = 0;
        zColor = "";
      }
    }
    db_execute(
       "INSERT INTO enums(type,idx,name,value,color) "
       "VALUES('%s',%d,'%q','%q','%q')",
       zEnum, cnt++, zName, zDesc, zColor
    );
    while( isspace(*z) ) z++;
  }

  /* If the enums were updated such that one of the defaults was removed,
  ** choose a new default.
  */
  if( !strcmp(zEnum,"status") ){
    const char* zDefault = db_config("initial_state","new");
    char* z = db_short_query("SELECT name FROM enums "
                             "WHERE type='status' AND name='%q'", zDefault);
    if( z==0 || z[0]==0 ) {
      /* gone missing, update */
      db_execute(
        "REPLACE INTO config(name,value) "
        "VALUES('initial_state',(SELECT name FROM enums WHERE type='status'));"
      );
    }
  }else if( !strcmp(zEnum,"type") ){
    const char* zDefault = db_config("dflt_tkt_type","code");
    char* z = db_short_query("SELECT name FROM enums "
                             "WHERE type='type' AND name='%q'", zDefault);
    if( z==0 || z[0]==0 ) {
      /* gone missing, update */
      db_execute(
        "REPLACE INTO config(name,value) "
        "VALUES('dflt_tkt_type',(SELECT name FROM enums WHERE type='type'));"
      );
    }
  }
}

/*
** WEBPAGE: /setup_enum
*/
void setup_enum_page(void){
  char *zText;
  const char *zEnum;
  int nRow;
  const char *zTitle;
  const char *zName;

  /* The user must be at least the administrator in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okAdmin ){
    login_needed();
    return;
  }

  /* What type of enumeration are we entering.
  */
  zEnum = P("e");
  if( zEnum==0 ){ zEnum = "subsys"; }
  if( strcmp(zEnum,"subsys")==0 ){
    zTitle = "������ϵͳ����";
    zName = "��ϵͳ";
    nRow = 20;
    common_add_help_item("CvstracAdminSubsystem");
  }else
  if( strcmp(zEnum,"type")==0 ){
    zTitle = "������������";
    zName = "����";
    nRow = 6;
    common_add_help_item("CvstracAdminTicketType");
  }else
  if( strcmp(zEnum,"status")==0 ){
    zTitle = "��������״̬";
    zName = "״̬";
    nRow = 10;
    common_add_help_item("CvstracAdminTicketState");
  }else
  {
    common_add_nav_item("setup", "�����ò˵�");
    common_header("δ֪��ö������");
    @ <p>URL ����:  "e" ��ѯ����ָ����һ��
    @ δ֪��ö������: "%h(zEnum)".</p>
    @
    @ <p>��� "����" ���ӷ��ص����ò˵���</p>
    common_footer();
    return;
  }

  /*
  ** The "s" query parameter is a long text string that specifies
  ** the names of all subsystems.  If any subsystem names have been
  ** added or removed, then make appropriate changes to the subsyst
  ** table in the database.
  */
  if( P("x") ){
    db_execute("BEGIN");
    string_to_enum(zEnum, P("x"));
    db_execute("COMMIT");
  }

  /* Genenerate the page.
  */
  common_add_nav_item("setup", "�����ò˵�");
  common_header(zTitle);
  zText = enum_to_string(zEnum);
  @ <p>
  @ �����г��������񵥵� "%s(zName)" ����
  @ �������ֵ��
  @ �����Ա༭������ı������Ӧ�����޸���
  @ �����ֵ��
  @ </p>
  @
  @ <p>
  @ ��ߵı���Ǳ��浽���ݿ��е�ֵ��
  @ ���ı����������ʾ�Ŀɶ��������ı���
  @ �����ı�������һ����ѡ����Բ���Ű�
  @ ������ɫ�������ڱ�����ʾ�С�
  @ </p>
  @
  @ <form action="%s(g.zPath)" method="POST">
  @ <p><input type="hidden" name="e" value="%s(zEnum)">
  @ <textarea cols=60 rows=%d(nRow) name="x">%h(zText)</textarea></p>
  @ <p><input type="submit" value="�ύ"></p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_udef
*/
void setup_udef_page(void){
  int idx, i;
  const char *zName;
  const char *zText;

  /* The user must be at least the administrator in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okAdmin ){
    login_needed();
    return;
  }

  /* Write back results if requested.
  */
  idx = atoi(PD("idx","0"));
  zName = P("n");
  zText = P("x");
  if( idx>=1 && idx<=5 && zName && zText ){
    char zEnum[20];
    char *zName2 = trim_string(zName);
    char *zDesc2 = trim_string(PD("d",""));
    bprintf(zEnum,sizeof(zEnum),"extra%d", idx);
    db_execute("BEGIN");

    /* Always delete... A missing description is meaningful for /tktnew */
    db_execute("DELETE FROM config WHERE name='%s_desc'", zEnum);

    if( zName2[0] ){
      string_to_enum(zEnum, zText);
      db_execute(
        "REPLACE INTO config(name,value) VALUES('%s_name','%q');",
        zEnum, zName2
      );
      if( zDesc2 && zDesc2[0] ){
        db_execute(
          "REPLACE INTO config(name,value) VALUES('%s_desc','%q');",
          zEnum, zDesc2
        );
      }
    }else{
      db_execute("DELETE FROM config WHERE name='%s_name'", zEnum);
      db_execute("DELETE FROM enums WHERE type='%s'", zEnum);
    }
    db_execute("COMMIT");
    db_config(0,0);
  }

  /* Genenerate the page.
  */
  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminUserField");
  common_header("�����û��Զ����ֶ�");
  @ <p>
  @ ���ݿ����񵥱� TICKET �а������������Ϊ "extra1" �� "extra5"
  @ ����չ�ֶΡ���Щ�ֶ���Ŀ�ĺ�������ڱ�����ҳ�����û������ض���
  @ Ӧ���Լ����塣
  @ </p>
  @
  @ <p>
  @ ÿһ����Ŀ����������������ؿ��ơ����ҽ�������Ŀ
  @ ����ʾ����Ϊ��ʱ��������ʾ�����񵥱����С��û�
  @ �ڱ����п�������Ŀ����ʾ�������������Ƶ�
  @ "extra1"��
  @ </p>
  @
  @ <p>
  @ ÿ����Ŀ�����ֵ����������ı༭����ָ����
  @ �˴���ʹ�õĸ�ʽ��ͬ����
  @ ָ�� <a href="setup_enum?e=type">��������</a>��
  @ <a href="setup_enum?e=status">����״̬</a> ��
  @ <a href="setup_enum?e=subsys">��ϵͳ����</a> ʱ�ĸ�ʽ��
  @ ÿ�ж�Ӧһ�������ֵ��
  @ ��ߵı���Ǳ��浽���ݿ��е�ֵ��
  @ ���ı����������ʾ�Ŀɶ��������ı���
  @ �����ı�������һ����ѡ����Բ���Ű�
  @ ������ɫ�������ڱ�����ʾ�С�
  @ </p>
  @
  @ <p>
  @ ����ֵ�༭��Ҳ�������ա�
  @ ���Ϊһ����Ŀ����������ֵ�б��û��Ը���Ŀ���ݵ�
  @ �޸Ľ���������Щֵ֮�С�
  @ ���û�ж�������ֵ�б�����Ŀ�����ݿ���Ϊ
  @ ������ı���
  @ </p>
  @
  @ <p>
  @ �����༭�����Ϊ�ա�
  @ ����ṩ��������Ϣ������ֶλ����½�����ҳ������ʾ�����롣
  @ ���û��������Ϣ������ֶ��������ڱ༭����ҳ������ʾ���޸ģ�
  @ ������������½�����ҳ���С�
  @ </p>
  for(i=0; i<5; i++){
    const char *zOld;
    char *zAllowed;
    const char *zDesc;
    char zEnumName[30];
    bprintf(zEnumName,sizeof(zEnumName),"extra%d_name",i+1);
    zOld = db_config(zEnumName,"");
    zEnumName[6] = 0;
    zAllowed = enum_to_string(zEnumName);
    bprintf(zEnumName,sizeof(zEnumName),"extra%d_desc",i+1);
    zDesc = db_config(zEnumName,"");
    @ <hr>
    @ <h3>���ݿ���Ŀ "extra%d(i+1)":</h3>
    @ <form action="%s(g.zPath)" method="POST">
    @ <input type="hidden" name="idx" value="%d(i+1)">
    @ ��ʾ��:
    @ <input type="text" name="n" value="%h(zOld)"><br>
    @ ����ֵ�б�: (<i>���� ���� ��ɫ</i> - ����ʣ����ı�)<br>
    @ <textarea cols=60 rows=15 name="x">%h(zAllowed)</textarea><br>
    @ ������Ϣ: (HTML - ���ս����½�����ҳ���к���)<br>
    @ <textarea cols=60 rows=5 name="d">%h(zDesc)</textarea><br>
    @ <input type="submit" value="�ύ">
    @ </form>
  }
  common_footer();
}

/*
** WEBPAGE: /setup_chng
*/
void setup_chng_page(void){
  const char *zNotify, *zOldNotify;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** The "notify" query parameter is the name of a program or script that
  ** is run whenever a ticket is created or modified.  Modify the notify
  ** value if it has changed.  Only setup can do this.
  */
  zOldNotify = db_config("notify","");
  zNotify = P("notify");
  if( zNotify && strcmp(zOldNotify,zNotify)!=0 ){
    db_execute(
      "REPLACE INTO config(name,value) VALUES('notify','%q');",
      zNotify
    );
    zOldNotify = zNotify;
    db_config(0,0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminNotification");
  common_header("�������񵥱��֪ͨ");
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>����һ���ⲿ�����һ�����񵥱��������޸�ʱ
  @ ���Զ����á� �ڴ��� /bin/sh ǰ������ķ��Ż�
  @ �滻����Ӧ���ַ���:
  @
  @ <table border=1 cellspacing=0 cellpadding=5 align="right" width="45%%">
  @ <tr><td bgcolor="#e0c0c0">
  @ <big><b>��Ҫ�İ�ȫ��ʾ</b></big>
  @
#ifdef CVSTRAC_WINDOWS
  @ <p>�뱣֤���е��滻���Ŷ�ʹ��˫���Ű���������
  @ (�� <tt>"%%d"</tt>) �����û����ܻ�ʹ����������
  @ ���ⲿ����������ϵͳ�����С�</p>
  @
  @ <p>�ı����滻ǰ���ȥ���еĵ����źͷ�б�ˣ�
  @ ��������滻����������˫���Ű���ʱ�����ᱻ
  @ ��ǵ���һ�������������</p>
#else
  @ <p>�뱣֤���е��滻���Ŷ�ʹ�õ����Ű���������
  @ (�� <tt>'%%d'</tt>) �����û����ܻ�ʹ����������
  @ ���ⲿ����������ϵͳ�����С�</p>
  @
  @ <p>�ı����滻ǰ���ȥ���еĵ����źͷ�б�ˣ�
  @ ��������滻���������õ����Ű���ʱ�����ᱻ
  @ ��ǵ���һ�������������</p>
#endif
  @
  @ <p>�ȫ�ķ����ǣ�ֻʹ��һ�� <b>%%n</b> �滻���ţ�
  @ Ȼ����һ�� Tcl �� Perl �ű������ݿ���ֱ�Ӷ�ȡ���������ֶ����ݡ�</p>
  @ </td></tr></table>
  @
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td width="40"><b>%%a</b></td>
  @     <td>�����񵥷�������û���</td></tr>
  @ <tr><td><b>%%A</b></td><td>��������˵��ʼ���ַ</td></tr>
  @ <tr><td><b>%%c</b></td><td>�������˵���ϵ��ʽ</td></tr>
  @ <tr><td><b>%%d</b></td><td>������Ϣ</td></tr>
  @ <tr><td><b>%%D</b></td><td>HTML ��ʽ��������Ϣ</td></tr>
  @ <tr><td><b>%%n</b></td><td>���񵥱��</td></tr>
  @ <tr><td><b>%%p</b></td><td>��Ŀ����</td></tr>
  @ <tr><td><b>%%r</b></td><td>��ע��Ϣ</td></tr>
  @ <tr><td><b>%%R</b></td><td>HTML ��ʽ�ı�ע��Ϣ</td></tr>
  @ <tr><td><b>%%s</b></td><td>���񵥵�״̬</td></tr>
  @ <tr><td><b>%%t</b></td><td>���񵥵ı���</td></tr>
  @ <tr><td><b>%%u</b></td>
  @     <td>�޸ĸ����񵥵��û���</td></tr>
  @ <tr><td><b>%%w</b></td><td>���񵥵Ĵ������û���</td></tr>
  @ <tr><td><b>%%y</b></td><td>���񵥵�����</td></tr>
  @ <tr><td><b>%%f</b></td><td>��һ�α���� TKTCHNG ��¼ ID��������¼�¼��Ϊ 0��</td></tr>
  @ <tr><td><b>%%l</b></td><td>���һ�α���� TKTCHNG ��¼ ID��������¼�¼��Ϊ 0��</td></tr>
  @ <tr><td><b>%%h</b></td><td>�����������������¸�������Ϊ������ţ�����Ϊ 0��</td></tr>
  @ <tr><td><b>%%1</b></td><td>��һ���û��Զ����ֶ�</td></tr>
  @ <tr><td><b>%%2</b></td><td>�ڶ����û��Զ����ֶ�</td></tr>
  @ <tr><td><b>%%3</b></td><td>�������û��Զ����ֶ�</td></tr>
  @ <tr><td><b>%%4</b></td><td>���ĸ��û��Զ����ֶ�</td></tr>
  @ <tr><td><b>%%5</b></td><td>������û��Զ����ֶ�</td></tr>
  @ <tr><td><b>%%%%</b></td><td>ԭ������ַ� "<b>%%</b>"</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ <input type="text" name="notify" size="70" value="%h(zOldNotify)">
  @ <input type="submit" value="�ύ">
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_diff
*/
void setup_diff_page(void){
  const char *zDiff, *zOldDiff;
  const char *zList, *zOldList;
  const char *zFilter, *zOldFilter;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** The "diff" query parameter is the name of a program or script that
  ** is run whenever a ticket is created or modified.  Modify the filediff
  ** value if it has changed.  Only setup can do this.
  */
  zOldDiff = db_config("filediff","");
  zDiff = P("diff");
  if( zDiff && strcmp(zOldDiff,zDiff)!=0 ){
    if( zDiff[0] ){
      db_execute(
        "REPLACE INTO config(name,value) VALUES('filediff','%q');",
        zDiff
      );
    }else{
      db_execute("DELETE FROM config WHERE name='filediff'");
    }
    zOldDiff = zDiff;
    db_config(0,0);
  }

  /*
  ** The "list" query parameter is the name of a program or script that
  ** is run whenever a ticket is created or modified.  Modify the filelist
  ** value if it has changed.  Only setup can do this.
  */
  zOldList = db_config("filelist","");
  zList = P("list");
  if( zList && strcmp(zOldList,zList)!=0 ){
    if( zList[0] ){
      db_execute(
        "REPLACE INTO config(name,value) VALUES('filelist','%q');",
        zList
      );
    }else{
      db_execute("DELETE FROM config WHERE name='filelist'");
    }
    zOldList = zList;
    db_config(0,0);
  }

  /*
  ** The "filter" query parameter is the name of a program or script that any
  ** files get filtered through for HTML markup.
  */
  zOldFilter = db_config("filefilter","");
  zFilter = P("filter");
  if( zFilter && strcmp(zOldFilter,zFilter)!=0 ){
    if( zFilter[0] ){
      db_execute(
        "REPLACE INTO config(name,value) VALUES('filefilter','%q');",
        zFilter
      );
    }else{
      db_execute("DELETE FROM config WHERE name='filefilter'");
    }
    zOldFilter = zFilter;
    db_config(0,0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminFilter");
  common_header("����Դ����Ƚϳ���");
  @ <form action="%s(g.zPath)" method="POST">
  @ <h2>�ļ��Ƚ�</h2>
  @ <p>����һ���ⲿ����������ͬһ���ļ���������ͬ�汾���бȽϣ�
  @ �����ʽ�����Ǵ��ı��� HTML ��ʽ��
  @ ���ʹ�� HTML�����һ���ǿհ��ַ�Ҫ����
  @ �ַ� "<"���������Ϊ�������Ϊ���ı���ʽ��</p>
  @
  @ <table border=1 cellspacing=0 cellpadding=5 align="right" width="33%%">
  @ <tr><td bgcolor="#e0c0c0">
  @ <big><b>��Ҫ�İ�ȫ��ʾ</b></big>
  @
  @ <p>�뱣֤���е��滻���Ŷ�ʹ�õ����Ű���������
  @ (�� <tt>'%%F'</tt> �� <tt>'%%V2'</tt>)
  @ ��������û��ύһЩ���ļ�
  @ ��ʹ�÷ǳ�����ļ�����������������ϵͳ��ִ������
  @ ���ⲿ���</p>
  @
  @ <p>CVSTrac �������ԱȽ�һ�������а��������Ż�б�˵�
  @ �ļ���
  @ ��������滻���������õ����Ű���ʱ�����ᱻ
  @ ��ǵ���һ�������������</p>
  @ </td></tr></table>
  @
  @ <p>�����滻���Ž���ִ�г���ǰ����:</p>
  @
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td width="40" valign="top"><b>%%F</b></td>
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @     <td>��Ҫ�Ƚϵ� RCS �ļ���������һ������
    @         "<b>,v</b>" ��׺������·�����ļ�����</td></tr>
  }else{
    @     <td>��Ҫ���бȽϵ��ļ�����</td>
  }
  @ </tr>
  @ <tr><td><b>%%V1</b></td><td>��Ҫ�Ƚϵĵ�һ���汾</td></tr>
  @ <tr><td><b>%%V2</b></td><td>��Ҫ�Ƚϵĵڶ����汾</td></tr>
  @ <tr><td><b>%%RP</b></td><td>�ֿ��·��</td></tr>
  @ <tr><td><b>%%%%</b></td><td>ԭ������ַ� "<b>%%</b>"</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ <input type="text" name="diff" size="70" value="%h(zOldDiff)">
  @ <input type="submit" value="�ύ">
  @
  @ <p>������գ���ʹ����������:</p>
  @
  @ <blockquote><pre>
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @ rcsdiff -q -r'%%V1' -r'%%V2' -u '%%F'
  }else{
    @ svnlook diff -r '%%V2' '%%RP'
  }
  @ </pre></blockquote>
  @ </form>
  @ <hr>

  @ <form action="%s(g.zPath)" method="POST">
  @ <h2>�ļ��б�</h2>
  @ <p>����һ���ⲿ��������<i>�����ڱȽϷ�ʽ</i>
  @ ��ʾһ���ļ�ָ���汾������
  @ (����ʾ�ļ��ĵ�һ���汾)�������ʽ�����Ǵ��ı��� HTML ��ʽ��
  @ ���ʹ�� HTML�����һ���ǿհ��ַ�Ҫ����
  @ �ַ� "<"���������Ϊ�������Ϊ���ı���ʽ��</p>
  @
  @ <p>��������������ʾһ����������뵽
  @ �ֿ��е��ļ����ݡ�</p>
  @
  @ <p>�����滻���Ž���ִ�г���ǰ����:</p>
  @
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td width="40" valign="top"><b>%%F</b></td>
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @     <td>��Ҫ�Ƚϵ� RCS �ļ���������һ������
    @         "<b>,v</b>" ��׺������·�����ļ�����</td>
  }else{
    @     <td>��Ҫ���бȽϵ��ļ�����</td>
  }
  @ </tr>
  @ <tr><td><b>%%V</b></td><td>Ҫ��ʾ���ݵİ汾��</td></tr>
  @ <tr><td><b>%%RP</b></td><td>�ֿ��·��</td></tr>
  @ <tr><td><b>%%%%</b></td><td>ԭ������ַ� "<b>%%</b>"</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ <input type="text" name="list" size="70" value="%h(zOldList)">
  @ <input type="submit" value="�ύ">
  @
  @ <p>������գ���ʹ����������:</p>
  @
  @ <blockquote><pre>
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @ co -q -p'%%V' '%%F' | diff -c /dev/null -
  }else{
    @ svnlook cat -r '%%V' '%%RP' '%%F'
  }
  @ </pre></blockquote>
  @ </form>
  @ <hr>

  @ <form action="%s(g.zPath)" method="POST">
  @ <h2>�ļ�������</h2>
  @ <p>����һ���ⲿ�����������ļ��ĵ����汾�������ݹ��ˡ�
  @ ������������ӱ�׼������ȡ���ļ����ݣ�
  @ �����ʽ�����Ǵ��ı��� HTML ��ʽ��
  @ ���ʹ�� HTML�����һ���ǿհ��ַ�Ҫ����
  @ �ַ� "<"���������Ϊ�������Ϊ���ı���ʽ��</p>
  @
  @ <p>������������ʾ�ļ������ݡ�</p>
  @
  @ <p>�����滻���Ž���ִ�г���ǰ����:</p>
  @
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td width="40" valign="top"><b>%%F</b></td>
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @     <td>�����д�����ļ���������һ�����·�����ļ�����
    @         ��������ʾ�����ļ����ݡ�</td>
  }else{
    @     <td>�����д�����ļ�����</td>
  }
  @ </tr>
  @ <tr><td><b>%%V</b></td><td>��Ҫ��ʾ�İ汾��</td></tr>
  @ <tr><td><b>%%RP</b></td><td>�ֿ��·��</td></tr>
  @ <tr><td><b>%%%%</b></td><td>ԭ������ַ� "<b>%%</b>"</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ <input type="text" name="filter" size="70" value="%h(zOldFilter)">
  @ <input type="submit" value="�ύ">
  @
  @ <p>������գ�������ݽ�ֱ��ʹ��
  @ HTML &lt;PRE&gt; ��ǩ����Ϊ�򵥵� HTML ��ʾ��</p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_style
*/
void setup_style_page(void){
  const char *zHeader, *zFooter;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** If both "header" and "footer" query parameters are present, then
  ** change the header and footer to the values of those parameters.
  ** Only the setup user can do this.
  */
  if( P("ok") && P("header") && P("footer") ){
    db_execute(
      "REPLACE INTO config VALUES('header','%q');"
      "REPLACE INTO config VALUES('footer','%q');",
       trim_string(P("header")),
       trim_string(P("footer"))
    );
    db_config(0,0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminStyle");
  if( attachment_max()>0 ){
    common_add_action_item("attach_add?tn=0", "����");
  }
  common_header("������ʽ");
  @ <p>
  @ ����������ʾ��ÿ��ҳ���ҳü��ҳ�ŵ� HTML ���롣
  @ ������գ���ʹ��Ĭ�ϵ�ҳü��ҳ�š�
  @ ���������һ���ļ��������ַ� "/" ��ͷ���ļ�����
  @ ������ HTML �ı�������ļ���������
  @ �ڶ�������Ϊҳü��ҳ�š�</p>
  @
  @ <p>
  @ �����������ҳ����Ӹ�������Щ�������Ա����Ƶ�ҳüҳ
  @ �Ż�����ҳ�����á����磬��ʽ��JavaScript �ļ���
  @ ��վ��־��ͼ��ȶ�������Ϊ��������Щ��������ֱ��ͨ��
  @ �ļ��� (���� <i>filename.png</i>) �����ã�������Ҫ
  @ <i>attach_get/89/filename.png</i> �������������ӡ�</p>
  @
  @ <p>һ��Ĭ�ϵ� <a href="cvstrac.css">cvstrac.css</a> ��ʽ��ʼ������Ч�ġ�
  @ Ȼ������Ҳ���Ը���һ�ݸ��µİ汾�����ҳ�档
  @ ԭʼ�İ汾��ͨ��
  @ <a href="cvstrac_default.css">cvstrac_default.css</a> ȡ�á�</p>
  @
  @ <p>�����滻����ҳü��ҳ�ŵ��ı��С���Щ�滻������
  @ HTML �޹صģ�������Щ HTML ������ֱ������������
  @ ���Ǵ��ļ��ж�ȡ���ġ�</p>
  @
  @ <blockquote>
  @ <table>
  @ <tr><td width="40"><b>%%N</b></td><td>��Ŀ������</td></tr>
  @ <tr><td><b>%%T</b></td><td>��ǰҳ��ı���</td></tr>
  @ <tr><td><b>%%V</b></td><td>CVSTrac �İ汾��</td></tr>
  @ <tr><td><b>%%B</b></td><td>CVSTrac ��������</td></tr>
  @ <tr><td><b>%%D</b></td><td>��ǰ�ĵ����� (����������������)</td></tr>
  @ <tr><td><b>%%%%</b></td><td>ԭ������ַ� "<b>%%</b>"</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  zHeader = db_config("header","");
  zFooter = db_config("footer","");

  /* user wants to restore the defaults */
  if( P("def") ){
    zHeader = HEADER;
    zFooter = FOOTER;
  }

  @ ҳü:<br>
  @ <textarea cols=80 rows=8 name="header">%h(zHeader)</textarea><br>
  @ ҳ��:<br>
  @ <textarea cols=80 rows=8 name="footer">%h(zFooter)</textarea><br>
  @ <input type="submit" name="ok" value="�ύ">
  @ <input type="submit" name="def" value="Ĭ��">
  @ <input type="submit" name="can" value="ȡ��">
  @ </p>
  @ </form>

  attachment_html("0","","");

  common_footer();
}

/*
** Make a copy of file zFrom into file zTo.  If any errors occur,
** return a pointer to a string describing the error.
*/
static const char *file_copy(const char *zFrom, const char *zTo){
  FILE *pIn, *pOut;
  int n;
  long long int total = 0;
  char zBuf[10240];
  pIn = fopen(zFrom, "r");
  if( pIn==0 ){
    return mprintf(
      "�޷������ļ� - �����Զ���ʽ���ļ� \"%h\" ��", zFrom
    );
  }
  unlink(zTo);
  pOut = fopen(zTo, "w");
  if( pOut==0 ){
    fclose(pIn);
    return mprintf(
      "�޷������ļ� - ������д��ʽ���ļ� \"%h\" ��", zTo
    );
  }
  while( (n = fread(zBuf, 1, sizeof(zBuf), pIn))>0 ){
    if( fwrite(zBuf, 1, n, pOut)<n ){
      fclose(pIn);
      fclose(pOut);
      return mprintf(
        "���Ʋ�������� %lld �ֽں�ʧ�ܡ�����������", total
      );
    }
    total += n;
  }
  fclose(pIn);
  fclose(pOut);
  return 0;
}

/*
** WEBPAGE: /setup_attach
*/
void setup_attachment_page(void){
  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  if( P("sz") ){
    int sz = atoi(P("sz"))*1024;
    db_execute("REPLACE INTO config VALUES('max_attach_size',%d)", sz);
    db_config(0, 0);
    cgi_redirect("setup");
  }
 
  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminAttachment");
  common_header("���ø����ļ���󳤶�");
  @ <p>
  @ ���������븽���ļ��������󳤶ȡ���������㣬
  @ ���������ϴ�������
  @ </p>
  @
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ����������ļ�����:
  @ <input type="text" name="sz" value="%d(attachment_max()/1024)" size=5> KB��
  @ <input type="submit" value="����">
  @ </p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_throttle
*/
void setup_throttle_page(void){
  int mxHit = atoi(db_config("throttle","0"));
  int nf = atoi(db_config("nofollow_link","0"));
  int cp = atoi(db_config("enable_captcha","0"));
  int lnk = atoi(db_config("max_links_per_edit","0"));
  int mscore = atoi(db_config("keywords_max_score","0"));
  const char *zKeys = db_config("keywords","");

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }


  if( P("sz") && atoi(P("sz"))!=mxHit ){
    mxHit = atoi(P("sz"));
    db_execute("REPLACE INTO config VALUES('throttle',%d)", mxHit);
    db_config(0, 0);
  }

  if( P("nf") && atoi(P("nf"))!=nf ){
    nf = atoi(P("nf"));
    db_execute("REPLACE INTO config VALUES('nofollow_link',%d)", nf);
    db_config(0, 0);
  }
 
  if( P("cp") && atoi(P("cp"))!=cp ){
    cp = atoi(P("cp"));
    db_execute("REPLACE INTO config VALUES('enable_captcha',%d)", cp);
    db_config(0, 0);
  }
 
  if( P("lnk") && atoi(P("lnk"))!=lnk ){
    lnk = atoi(P("lnk"));
    db_execute("REPLACE INTO config VALUES('max_links_per_edit',%d)", lnk);
    db_config(0, 0);
  }

  if( P("mscore") && atoi(P("mscore"))!=mscore ){
    mscore = atoi(P("mscore"));
    db_execute("REPLACE INTO config VALUES('keywords_max_score',%d)", mscore);
    db_config(0, 0);
  }

  if( P("keys") && strcmp(zKeys,PD("keys","")) ){
    zKeys = P("keys");
    db_execute("REPLACE INTO config VALUES('keywords','%q')", zKeys);
    db_config(0, 0);
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminAbuse");
  common_header("��������");
  @ <h2>���������û�ÿСʱ��߷��ʴ�������</h2>
  @ <p>
  @ ��������ͬһIP��ַ�������û������
  @ ÿСʱ��ߵķ��ʴ������������ʾ��
  @ �����ơ�
  @ </p>
  @
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ÿСʱ��߷�����:
  @ <input type="text" name="sz" value="%d(mxHit)" size=5>
  @ <input type="submit" value="����">
  @ </p>
  @ </form>
  @
  @ <p>
  @ ������ͨ�����ݿ���һ�ŵ����ı� (�� ACCESS_LOAD) ��������
  @ ����¼������ÿ������IP��������ʱ���һ�� "����ֵ"��
  @ ����ֵÿ��һСʱ�ᰴָ�����ɼ��롣
  @ ÿ���µķ��ʻ�����һ����λ�ĸ���ֵ��
  @ ������ֵ�������趨������ʱ������ֵ���Զ�������
  @ ���ҿͻ��˽���ת�� <a href="captcha">������֤</a>
  @ ҳ�档����������ת���������κ�
  @ �û�������ֹ���ʣ�ֱ�Ӹ���ֵ�½�������ֵ
  @ ���¡�����û�ͨ����
  @ <a href="captcha">������֤</a> ���ԣ�һ�� Cookie ��־�������á�
  @ </p>
  @
  @ <p>
  @ ��ʹ��������ʱ��<a href="captcha">������֤</a>
  @ ҳ��ͬ�������û���ͼ���κθĶ����ݿ�
  @ �Ļǰ��ʾ (�紴�� <a href="tktnew">�µ�����</a>��
  @ <a href="wikiedit?p=WikiIndex">�޸� Wiki ҳ��</a> �ȵ�)�����
  @ ����������ֹ��Щ�Զ����� Wiki ��������
  @
  @ <p>
  @ ���ж� "��ֹ" ҳ(ͨ��
  @ <a href="honeypot">����</a> ҳ)�ķ����Զ�������ֵ������
  @ ���޵�������ÿһ����ҳ�϶���һ�����ص���
  @ ��ҳ�����ӡ��������������ƭ��Щ����֩��ȥ����
  @ ����ҳ��ʹ�����ǵķ��ʺܿ�ر���ֹ����
  @ </p>
  @
  @ <p>
  @ ������������ֻ�����Щû�е�¼�������û���Ч��
  @ ��¼�û�����������ط����κ�ҳ��
  @ (��������ҳ)��������Զ���ᱻ�ܾ�
  @ ���ʡ����⣬������(������������)����Щͨ����
  @ <a href="captcha">������֤</a> �������� Cookie
  @ ����ʧЧ��
  @ </p>
  @
  @ <p>һ�ݶ� <a href="info_throttle">������־</a> ��ͳ����
  @ �������õġ�</p>

  @ <hr>
  @ <h2>������֤</h2>
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ����������ѡ������û��ڱ������޸���վ���ݣ����񵥡�wiki �ȣ�
  @ ֮ǰ������ͨ��һ���򵥵� <a href="http://en.wikipedia.org/wiki/Captcha">������֤</a>
  @ ���ԡ�ͨ�����Ժ󽫻��������������
  @ Cookie ��־���������ʧ�ܴ���̫��
  @ ���ᴥ���޶����������û� IP ��ַ��
  @ ע�����Ҫ�������ѡ��������ƹ��ܱ����Ѿ�����
  @ ������ֵ����
  @ </p>
  @ <p>
  @ <label for="cp"><input type="checkbox" name="cp" id="cp"
  @    %s(cp?" checked":"") %s(mxHit?"":"disabled") value="1">
  @ Ϊ�޸����ݿ���������֤����</label>
  @ </p>
  @ <input type="submit" value="����">
  @ </form>
  @ <hr>

  @ <h2>�ⲿ����</h2>
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ����������ѡ��������ӵ��ⲿվ��ĳ����Ӷ������Ϊ
  @ "������"���⽫�ṩ����������һ����ʾ��������Щ���ӣ�
  @ �Դﵽ���� wiki ������Ŀ�ġ�������Σ���ֻ�Ǹ��ô����޵Ĺ��ܣ�wiki
  @ �����������ǲ����������㹻�Ĵ�������ʶ��������Ϊֻ�����˷�����
  @ �Լ���ʱ�䡣
  @ </p>
  @ <p>
  @ <label for="nf"><input type="checkbox" name="nf" id="nf"
  @    %s(nf?" checked":"") value="1">
  @ ����������������ٷ����ⲿ���ӡ�</label>
  @ </p>
  @ <input type="submit" value="����">
  @ </form>
  @ 
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ Wiki ����������ͨ����һ��ҳ�����������ⲿ����
  @ ��������һ���򵥵Ľ���취��ǿ���ڵ��� wiki �༭��
  @ �����ⲿ���ӵ��������
  @ ����Ϊ�㽫���ø�ѡ�
  @ </p>
  @ <p>
  @ ÿ�� Wiki �༭ʱ���������ⲿ������:
  @ <input type="text" name="lnk" value="%d(lnk)" size=5>
  @ </p>
  @ <input type="submit" value="����">
  @ </form>
  @ <hr>
  @ <h2>�ؼ��ֹ���</h2>
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ ����һ���ո�ָ��Ĺؼ����б����е� wiki �༭����
  @ �������б�������������ֵ���ƣ�
  @ �޸Ľ���ܾ��������㷨ʹ�ñ�׼��
  @ CVSTrac �ı� <strong>search()</strong> ����������ÿһ��ƥ��Ĺؼ�
  @ �ֽ���� 6 �� 10 ���㣩���ظ������б��е�һ���ؼ��ֽ�����
  @ ���ߵķ�ֵ��
  @ </p>
  @ <p>
  cgi_text("mscore", 0, 0, 0, 0, 5, 8, 1, mprintf("%d",mscore),
           "���ؼ��ַ�ֵ");
  @ </p>
  @ <h3>�ؼ��ֺ�����</h3>
  @ <p><textarea name="keys" rows="8" cols="80" class="wrapvirtual">
  @ %h(zKeys)
  @ </textarea></p>
  @ <input type="submit" value="����">
  @ </form>

  common_footer();
}

/*
** WEBPAGE: /setup_markupedit
*/
void setup_markupedit_page(void){
  const char *zMarkup = PD("m","");
  const char *zType = PD("t","0");
  const char *zFormat = PD("f","");
  const char *zDescription = PD("d","");
  int delete = atoi(PD("del","0"));

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_action_item("setup_markup", "ȡ��");
  common_add_action_item(mprintf("setup_markupedit?m=%h&del=1",zMarkup),
                         "ɾ��");
  common_add_help_item("CvstracAdminMarkup");
  common_header("���� Wiki ���");

  if( P("can") ){
    cgi_redirect("setup_markup");
    return;
  }else if( P("ok") ){
    /* delete it */
    db_execute("DELETE FROM markup WHERE markup='%q';", zMarkup);
    cgi_redirect("setup_markup");
    return;
  }else if( delete && zMarkup[0] ){
    @ <p>��ȷ��Ҫɾ����� <b>%h(zMarkup)</b>��</p>
    @
    @ <form method="POST" action="setup_markupedit">
    @ <input type="hidden" name="m" value="%h(zMarkup)">
    @ <input type="submit" name="ok" value="�ǣ�ɾ��">
    @ <input type="submit" name="can" value="��ȡ��">
    @ </form>
    common_footer();
    return;
  }

  if( P("u") ){
    if( zMarkup[0] && zType[0] && zFormat[0] ) {
      /* update database and bounce back to listing page. If the
      ** description is empty, we'll survive (and wing it).
      */
      db_execute("REPLACE INTO markup(markup,type,formatter,description) "
                 "VALUES('%q',%d,'%q','%q');",
                 zMarkup, atoi(zType), zFormat, zDescription);
    }

    cgi_redirect("setup_markup");
    return;
  }
  
  if( zMarkup[0] ){
    /* grab values from database, if available
    */
    char **az = db_query("SELECT type, formatter, description "
                         "FROM markup WHERE markup='%q';",
                         zMarkup);
    if( az && az[0] && az[1] && az[2] ){
      zType = az[0];
      zFormat = az[1];
      zDescription = az[2];
    }
  }

  @ <form action="%s(g.zPath)" method="POST">
  @ �������: <input type="text" name="m" value="%h(zMarkup)" size=12>
  cgi_optionmenu(0,"t",zType, "���","0", "��","2",
    "������","1", "�����","3",
    "�����εĳ�����","4", "�����εĳ����","5",
    NULL);
  @ <br>��ʽ:<br>
  @ <textarea name="f" rows="4" cols="60">%h(zFormat)</textarea><br>
  @ ����:<br>
  @ <textarea name="d" rows="4" cols="60">%h(zDescription)</textarea><br>
  @ <input type="hidden" name="u">
  @ <input type="submit" value="����">
  @ </form>
  @
  @ <table border=1 cellspacing=0 cellpadding=5 align="right" width="45%%">
  @ <tr><td bgcolor="#e0c0c0">
  @ <big><b>��Ҫ�İ�ȫ��ʾ</b></big>
  @
  @ <p>�����ʽ���߽�ִ���ⲿ�ű��ͳ��򣬲��ʵ�������
  @ ���ܻ�Σ���������İ�ȫ��</p>
  @
  @ <p>��ȷ��ʹ�õ��������������е��ı�
  @ (�� <tt>'%%k'</tt>)�����򣬱������ĵ��û����ܻ�
  @ �����ķ�������ִ����������</p>
  @  
  @ <p>�ı��ڱ��滻֮ǰ���Ѿ�����ȥ�����еĵ����źͷ�б�ˣ�
  @ ������滻�������ʹ�õ����Ű����Ļ���
  @ ����ʼ�ձ���ǳ�����Ϊһ�������ķ���������</p>
  @ </td></tr></table>
  @
  @ �����滻��Ӧ�����Զ�������:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td width="40"><b>%%m</b></td><td>�������</td></tr>
  @ <tr><td><b>%%k</b></td><td>��Ǽ�ֵ</td></tr>
  @ <tr><td><b>%%a</b></td><td>��ǲ���</td></tr>
  @ <tr><td><b>%%x</b></td><td>��ǲ��������Ϊ����Ϊ��ֵ</td></tr>
  @ <tr><td><b>%%b</b></td><td>��ǿ�</td></tr>
  @ <tr><td><b>%%r</b></td><td>%s(g.scm.zName) �ֿ��·��</td></tr>
  @ <tr><td><b>%%n</b></td><td>CVSTrac ���ݿ���</td></tr>
  @ <tr><td><b>%%u</b></td><td>��ǰ�û�</td></tr>
  @ <tr><td><b>%%c</b></td><td>�û�Ȩ��</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ ���⣬�ⲿ���򻹽�ӵ��������Щ
  @ ������������:<br>
  @ REQUEST_METHOD, GATEWAY_INTERFACE, REQUEST_URI, PATH_INFO,
  @ QUERY_STRING, REMOTE_ADDR, HTTP_USER_AGENT, CONTENT_LENGTH,
  @ HTTP_REFERER, HTTP_HOST, CONTENT_TYPE, HTTP_COOKIE
  @ <br>
  @
  @ <h2>˵��</h2>
  @ <ul>
  @   <li>�������Ϊ Wiki ��ʽ����ǩ����һ�����
  @   <b>echo</b> ����ʹ�� <tt>{echo: key args}</tt> ������</li>
  @   <li>�Ա�������޸ģ��������Ѵ��ڵ�ʹ���˸ñ�ǵ�
  @   Wiki ҳ��</li>
  @   <li>"���" ֻ�Ǽ򵥵��ַ����滻������
  @   CVSTrac ֱ�Ӵ���</li>
  @   <li>"��" ������ɳɶԵ� {markup} �� {endmarkup} ����ɣ�������֮
  @   ��������ı�����Ϊ���� (%a)����������Ǽ�ֵ��</li>
  @   <li>"����" ���ͨ�������ⲿ�ű��ͳ���������
  @   ���ǿ��Ը�Ϊ���ӣ���ͬ��Ҳ���ڰ�ȫ����
  @   ���һ����ҳ�����ɵ��ٶȡ������Ǵ���������ȡ�ò�����
  @   �������ӱ�׼������ȡ���ı������ݡ�
  @   �����ַ�ʽ����Ҫ�� HTML ����������׼���</li>
  @   <li>���ʱ�����˿����εı�ǣ����а�������ȫ�� HTML ��ǩ/����
  @   �������ˡ������εı���������Լ����������
  @   (��Ȼ����ЩҲֻ���ɳ��������)��</li>
  @   <li>������Ϣ������ʹ�� {markups} ��ǩö�����п��õ�
  @   ����б�ʱʹ�á�����б����������
  @   <a href="wiki?p=WikiFormatting">WikiFormatting</a> ������ҳ���У�
  @   ���ṩ���������ص��ĵ���</li>
  @ </ul>

  common_footer();
}

/*
** WEBPAGE: /setup_markup
*/
void setup_markup_page(void){
  int j;
  char **az;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_action_item("setup_markupedit", "���ӱ��");
  common_add_help_item("CvstracAdminMarkup");
  common_header("���� Wiki ���");

  az = db_query("SELECT markup, description FROM markup ORDER BY markup;");
  if( az && az[0] ){
    @ <p><big><b>���Ʊ�ǹ���</b></big></p>
    @ <dl>
    for(j=0; az[j]; j+=2){
      @ <dt><a href="setup_markupedit?m=%h(az[j])">%h(az[j])</a></dt>
      if( az[j+1] && az[j+1][0] ){
        /* this markup has a description, output it.
        */
        @ <dd>
        output_formatted(az[j+1],NULL);
        @ </dd>
      }else{
        @ <dd>(������)</dd>
      }
    }
    @ </dl>
  }

  common_footer();
}

/*
** WEBPAGE: /setup_toolsedit
*/
void setup_toolsedit_page(void){
  const char *zTool = PD("t","");
  const char *zObject = PD("o","");
  const char *zCommand = PD("c","");
  const char *zDescription = PD("d","");
  const char *zPerms = PD("p","as");
  int delete = atoi(PD("del","0"));

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_action_item("setup_tools", "ȡ��");
  common_add_action_item(mprintf("setup_toolsedit?t=%h&del=1",zTool),
                         "Delete");
  common_header("�ⲿ����");

  if( P("can") ){
    cgi_redirect("setup_tools");
    return;
  }else if( P("ok") ){
    /* delete it */
    db_execute("DELETE FROM tool WHERE name='%q';", zTool);
    cgi_redirect("setup_tools");
    return;
  }else if( delete && zTool[0] ){
    @ <p>��ȷ��Ҫɾ������ <b>%h(zTool)</b>��</p>
    @
    @ <form method="POST" action="setup_toolsedit">
    @ <input type="hidden" name="t" value="%h(zTool)">
    @ <input type="submit" name="ok" value="�ǣ�ɾ��">
    @ <input type="submit" name="can" value="��ȡ��">
    @ </form>
    common_footer();
    return;
  }

  if( P("u") ){
    if( zTool[0] && zPerms[0] && zObject[0] && zCommand[0] ) {
      /* update database and bounce back to listing page. If the
      ** description is empty, we'll survive (and wing it).
      */
      db_execute("REPLACE INTO tool(name,perms,object,command,description) "
                 "VALUES('%q','%q','%q','%q','%q');",
                 zTool, zPerms, zObject, zCommand, zDescription);
    }

    cgi_redirect("setup_tools");
  }
  
  if( zTool[0] ){
    /* grab values from database, if available
    */
    char **az = db_query("SELECT perms, object, command, description "
                         "FROM tool WHERE name='%q';",
                         zTool);
    if( az && az[0] && az[1] && az[2] && az[3] ){
      zPerms = az[0];
      zObject = az[1];
      zCommand = az[2];
      zDescription = az[3];
    }
  }

  @ <form action="%s(g.zPath)" method="POST">
  @ ��������: <input type="text" name="t" value="%h(zTool)" size=12>
  cgi_optionmenu(0,"o",zObject,
                 "�ļ�","file",
                 "Wiki","wiki",
                 "����","tkt",
                 "�ύ","chng",
                 "��̱�","ms",
                 "����", "rpt",
                 "Ŀ¼", "dir",
                 NULL);
  @ <br>��Ҫ��Ȩ��:
  @ <input type="text" name="p" size=16 value="%h(zPerms)"><br>
  @ <br>������:<br>
  @ <textarea name="c" rows="4" cols="60">%h(zCommand)</textarea><br>
  @ ����:<br>
  @ <textarea name="d" rows="4" cols="60">%h(zDescription)</textarea><br>
  @ <input type="hidden" name="u">
  @ <input type="submit" value="����">
  @ </form>
  @
  @ <table border=1 cellspacing=0 cellpadding=5 align="right" width="45%%">
  @ <tr><td bgcolor="#e0c0c0">
  @ <big><b>��Ҫ�İ�ȫ��ʾ</b></big>
  @
  @ <p>�ⲿ�ű�������Ͳ��ʵ�������
  @ ���ܻ�Σ���������İ�ȫ��</p>
  @
  @ <p>��ȷ��ʹ�õ��������������е��ı�
  @ (�� <tt>'%%k'</tt>)�����򣬱������ĵ��û����ܻ�
  @ �����ķ�������ִ����������</p>
  @  
  @ <p>�ı��ڱ��滻֮ǰ���Ѿ�����ȥ�����еĵ����źͷ�б�ˣ�
  @ ������滻�������ʹ�õ����Ű����Ļ���
  @ ����ʼ�ձ���ǳ�����Ϊһ�������ķ���������</p>
  @
  @ <p>ÿһ�����߶���һ����С��Ȩ������Ҫ�󡣲μ�
  @ <a href="userlist">�û�</a> �����ȫ����Ȩ���б�</p>
  @ </td></tr></table>
  @
  @ �����滻�������ⲿ������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%RP</b></td><td>%s(g.scm.zName) �ֿ�·��</td></tr>
  @ <tr><td><b>%%P</b></td><td>CVSTrac ��������</td></tr>
  @ <tr><td><b>%%B</b></td><td>�������� URL</td></tr>
  @ <tr><td><b>%%U</b></td><td>��ǰ�û�</td></tr>
  @ <tr><td><b>%%UC</b></td><td>�û�Ȩ��</td></tr>
  @ <tr><td><b>%%N</b></td><td>��ǰʱ���</td></tr>
  @ <tr><td><b>%%T</b></td><td>��������</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻���ļ�������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%F</b></td><td>�ļ���</td></tr>
  @ <tr><td><b>%%V1</b></td><td>��һ���汾��</td></tr>
  @ <tr><td><b>%%V2</b></td><td>�ڶ����汾�� (���� diff)</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻��Ŀ¼������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%F</b></td><td>Ŀ¼·����</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻�����񵥹�����Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%TN</b></td><td>���񵥱��</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻�� Wiki ������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%W</b></td><td>Wiki ҳ������</td></tr>
  @ <tr><td><b>%%T1</b></td><td>��һ�� wiki ҳ���ʱ���</td></tr>
  @ <tr><td><b>%%T2</b></td><td>�ڶ��� wiki ҳ���ʱ��� (���� diff)
  @            </td></tr>
  @ <tr><td><b>%%C</b></td><td>�������ݵ���ʱ�ļ�</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻���ύ������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%CN</b></td><td>�ύ��</td></tr>
  @ <tr><td><b>%%C</b></td><td>������Ϣ����ʱ�ļ�</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻����̱�������Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%MS</b></td><td>��̱����</td></tr>
  @ <tr><td><b>%%C</b></td><td>������Ϣ����ʱ�ļ�</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ �����滻�Ա��湤����Ч:
  @ <blockquote>
  @ <table cellspacing="5" cellpadding="0">
  @ <tr><td><b>%%RN</b></td><td>������</td></tr>
  @ </table>
  @ </blockquote>
  @
  @ ���⣬�ⲿ���򻹽������в��ֻ�ȫ����
  @ ������������:<br>
  @ REQUEST_METHOD, GATEWAY_INTERFACE, REQUEST_URI, PATH_INFO,
  @ QUERY_STRING, REMOTE_ADDR, HTTP_USER_AGENT, CONTENT_LENGTH,
  @ HTTP_REFERER, HTTP_HOST, CONTENT_TYPE, HTTP_COOKIE
  @ <br>
  common_footer();
}

/*
** WEBPAGE: /setup_tools
*/
void setup_tools_page(void){
  int j;
  char **az;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_add_action_item("setup_toolsedit", "���ӹ���");
  common_header("�ⲿ����");

  az = db_query("SELECT name, description FROM tool ORDER BY name;");
  if( az && az[0] ){
    @ <p><big><b>�ⲿ����</b></big></p>
    @ <dl>
    for(j=0; az[j]; j+=2){
      @ <dt><a href="setup_toolsedit?t=%h(az[j])">%h(az[j])</a></dt>
      if( az[j+1] && az[j+1][0] ){
        /* this tool has a description, output it.
        */
        @ <dd>
        output_formatted(az[j+1],NULL);
        @ </dd>
      }else{
        @ <dd>(������)</dd>
      }
    }
    @ </dl>
  }

  common_footer();
}

/*
** WEBPAGE: /setup_backup
*/
void setup_backup_page(void){
  char *zDbName = mprintf("%s.db", g.zName);
  char *zBuName = mprintf("%s.db.bu", g.zName);
  const char *zMsg = 0;

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  if( P("bkup") ){
    db_execute("BEGIN");
    zMsg = file_copy(zDbName, zBuName);
    db_execute("COMMIT");
  }else if( P("rstr") ){
    db_execute("BEGIN");
    zMsg = file_copy(zBuName, zDbName);
    db_execute("COMMIT");
  }
 
  common_add_nav_item("setup", "�����ò˵�");
  common_add_help_item("CvstracAdminBackup");
  common_header("�������ݿ�");
  if( zMsg ){
    @ <p class="error">%s(zMsg)</p>
  }
  @ <p>
  @ ʹ������İ�ť�����ݿ���а�ȫ�Զ��ر��ݼ��ָ�������
  @ ԭ���ݿ��ļ���
  @ Ϊ <b>%h(zDbName)</b>�������ļ�
  @ Ϊ <b>%h(zBuName)</b>��
  @ </p>
  @
  @ <p>
  @ �������ǰ�ȫ�ġ���������ǻḲ����һ�ε�
  @ ���ݡ���������ڻָ�ʱ�жϲ����������ƻ���
  @ �����ݿ⡣
  @ ʹ�ûָ�����ʱ���������
  @ </p>
  @
  @ <form action="%s(g.zPath)" method="POST">
  @ <p><input type="submit" name="bkup" value="����"></p>
  @ <p><input type="submit" name="rstr" value="�ָ�"></p>
  @ </form>
  common_footer();
}

/*
** WEBPAGE: /setup_timeline
*/
void setup_timeline_page(void){
  int nCookieLife;
  int nTTL;
  int nRDL;
  
  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }
  
  if( P("cl") || P("ttl") || P("rdl") ){
    if( P("cl") ){
      int nCookieLife = atoi(P("cl"));
      db_execute("REPLACE INTO config VALUES('timeline_cookie_life',%d)", nCookieLife);
    }
    if( P("ttl") ){
      int nTTL = atoi(P("ttl"));
      db_execute("REPLACE INTO config VALUES('rss_ttl',%d)", nTTL);
    }
    if( P("rdl") ){
      int nRDL = atoi(P("rdl"));
      db_execute("REPLACE INTO config VALUES('rss_detail_level',%d)", nRDL);
    }
    db_config(0, 0);
  }
  
  nCookieLife = atoi(db_config("timeline_cookie_life", "90"));
  nTTL = atoi(db_config("rss_ttl", "60"));
  nRDL = atoi(db_config("rss_detail_level", "5"));
  
  common_add_nav_item("setup", "�����ò˵�");
  common_header("ʱ���ߺ� RSS ����");
  @ <form action="%s(g.zPath)" method="POST">
  @ <p>
  @ �������û�������� Cookie ��Ҫ�����������
  @ �� Cookie �ܱ���ʱ���ߵ������Է����û��Ķ�η��ʡ�<br>
  @ �ù��ܶ������û���Ч��<br>
  @ ����Ϊ 0 ����������� Cookie��
  @ </p>
  @ <p>
  @ Cookie ������: 
  @ <input type="text" name="cl" value="%d(nCookieLife)" size=5> ��
  @ <input type="submit" value="�ύ">
  @ </p>
  @ <hr>
  @ <p>
  @ RSS feed �� TTL (Time To Live) ����֪ͨ RSS �Ķ�����������ˢ��֮ǰ
  @ ��Ҫ����೤ʱ�䡣��Ϊÿ��ˢ�¶���Ҫ��������ҳ�棬Ϊ�˱������Ĵ���
  @ ռ�ã����ֵ�������õó�һЩ��
  @ ���� 15 ��ֵ���ܲ��Ǹ��õķ�����ͨ������ʹ�� 30-60
  @ ����ֵ��
  @ </p>
  @ <p>
  @ Time To Live:
  @ <input type="text" name="ttl" value="%d(nTTL)" size=5> ����
  @ <input type="submit" value="�ύ">
  @ </p>
  @ <hr>
  @ <p>
  @ RSS Դ����ϸ�ȼ���������Դ�н������
  @ ������ϸ���ݡ�<br>
  @ ��ϸ�ȼ�Խ�ߣ�����ռ��Ҳ��Խ��
  @ </p>
  @ <p>
  @ RSS ��ϸ�ȼ�:<br>
  @ <label for="rdl0"><input type="radio" name="rdl" value="0" id="rdl0"
  @ %s(nRDL==0?" checked":"")> ����</label><br>
  @ <label for="rdl5"><input type="radio" name="rdl" value="5" id="rdl5"
  @ %s(nRDL==5?" checked":"")> �е�</label><br>
  @ <label for="rdl9"><input type="radio" name="rdl" value="9" id="rdl9"
  @ %s(nRDL==9?" checked":"")> ��</label><br>
  @ <input type="submit" value="����">
  @ </p>
  @ </form>
  common_footer();
}

#if 0  /* TO DO */
/*
** WEB-PAGE: /setup_repair
*/
void setup_repair_page(void){

  /* The user must be the setup user in order to see
  ** this screen.
  */
  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  /*
  ** Change a check-in number.
  */
  cnfrom = atoi(PD("cnfrom"),"0");
  cnto = atoi(PD("cnto"),"0");
  if( cnfrom>0 && cnto>0 && cnfrom!=cnto ){
    const char *zOld;
    zOld = db_short_query(
       "SELECT rowid FROM chng WHERE cn=%d", cnfrom
    );
    if( zOld || zOld[0] ){
      db_execute(
        "BEGIN;"
        "DELETE FROM chng WHERE cn=%d;"
        "UPDATE chng SET cn=%d WHERE cn=%d;"
        "UPDATE filechng SET cn=%d WHERE cn=%d;"
        "UPDATE xref SET cn=%d WHERE cn=%d;"
        "COMMIT;",
        cnto,
        cnto, cnfrom,
        cnto, cnfrom,
        cnto, cnfrom
      );
    }
  }

  /*
  ** Remove duplicate entries in the FILECHNG table.  Remove check-ins
  ** from the CHNG table that have no corresponding FILECHNG entries.
  */
  if( P("rmdup") ){
    db_execute(
      "BEGIN;"
      "DELETE FROM filechng WHERE rowid NOT IN ("
         "SELECT min(rowid) FROM filechng "
         "GROUP BY filename, vers||'x'"
      ");"
      "DELETE FROM chng WHERE milestone=0 AND cn NOT IN ("
         "SELECT cn FROM filechng"
      ");"
      "COMMIT;"
    );
  }

  common_add_nav_item("setup", "�����ò˵�");
  common_header("�޸����ݿ�");
  @ <p>
  @ ������ʹ�ø�ҳ�����޸���
  @ ��ȡ�ֿ������ļ�ʱ�����˴�������ݿ⡣
  @ ��������������ڴ���� %s(g.scm.zName) �ֿ��һ��ϵͳ����
  @ ������ CVSTrac �Ĵ��󡣣�������֪���������͵Ĵ���
  @ ��������������֪���µ�����ʲôʱ�򻹻���֡���
  @ </p>
  @
  @
  @ </p>
  common_footer();
}
#endif
