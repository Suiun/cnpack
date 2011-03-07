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
** Routines for handling user account
*/
#define _XOPEN_SOURCE
#include <unistd.h>
#include "config.h"
#include "user.h"

/*
** WEBPAGE: /userlist
*/
void user_list(void){
  char **azResult;
  int i;

  login_check_credentials();
  if( !g.okWrite && g.isAnon ){
    login_needed();
    return;
  }
  common_standard_menu("userlist", 0);
  common_add_help_item("CvstracAdminUsers");
  common_add_action_item("useredit", "�����û�");
  common_header("�û��б�");
  @ <table cellspacing=0 cellpadding=0 border=0>
  @ <tr>
  @   <th align="right" class="nowrap">�û���</th>
  @   <th>&nbsp;&nbsp;&nbsp;�����&nbsp;&nbsp;&nbsp;</th>
  @   <th class="nowrap">��ʵ����</th>
  @ </tr>
  azResult = db_query(
    "SELECT id, name, email, capabilities FROM user ORDER BY id");
  for(i=0; azResult[i]; i+= 4){
    @ <tr>
    @ <td align="right">
    if( g.okAdmin ){
      @ <a href="useredit?id=%t(azResult[i])">
    }
    @ <span class="nowrap">%h(azResult[i])</span>
    if( g.okAdmin ){
      @ </a>
    }
    @ </td>
    @ <td align="center">%s(azResult[i+3])</td>
    if( azResult[i+2] && azResult[i+2][0] ){
      char *zE = azResult[i+2];
      @ <td align="left" class="nowrap">%h(azResult[i+1])
      @    (<a href="mailto:%h(zE)">%h(zE)</a>)</td>
    } else {
      @ <td align="left" class="nowrap">%h(azResult[i+1])</td>
    }
    @ </tr>
  }
  @ </table>
  @ <hr>
  @ <p><b>��ʾ:</b></p>
  @ <ol>
  @ <li><p>������ʱ�־����:</p>
  @ <table>
  @ <tr><td>a</td><td width="10"></td>
  @     <td>����: ������ɾ���û������񵥱����ʽ��</td></tr>
  @ <tr><td>d</td><td></td>
  @     <td>ɾ��: ɾ�������� Wiki�����񵥺͸�����</td></tr>
  @ <tr><td>i</td><td></td>
  @     <td>�ύ: ����µĴ��뵽 %h(g.scm.zName) �ֿ��С�</td></tr>
  @ <tr><td>j</td><td></td><td>�� Wiki: �鿴 Wiki ҳ�档</td></tr>
  @ <tr><td>k</td><td></td><td>д Wiki: �������޸� Wiki ҳ�档</td></tr>
  @ <tr><td>n</td><td></td><td>�½�����: �����µ����񵥡�</td></tr>
  @ <tr><td>o</td><td></td>
  @     <td>ȡ��: �� %h(g.scm.zName) �ֿ���ȡ�����롣</td></tr>
  @ <tr><td>p</td><td></td><td>����: �޸��û����롣</td></tr>
  @ <tr><td>q</td><td></td><td>��ѯ: ������༭�����ʽ��</td></tr>
  @ <tr><td>r</td><td></td><td>������: �鿴���񵥼�����ʷ��</td></tr>
  @ <tr><td>s</td><td></td><td>����: �޸� CVSTrac ���á�</td></tr>
  @ <tr><td>w</td><td></td><td>д����: �޸����񵥡�</td></tr>
  @ </table>
  @ </li>
  @
  @ <li><p>
  @ �������һ����Ϊ "<b>anonymous</b>" ���û����������˶����Է���
  @ �÷�����������Ҫ��¼���� anonymous
  @ �����û���Ȩ����ɶ��κε�¼���û���
  @ ���á�
  @ </p></li>
  @
  if( !strcmp(g.scm.zSCM,"cvs") ){
    @ <li><p>
    @ ������ʹ�� CVS V1.11 �����ϰ汾����֧��Ϊ�ֿ�ָ��
    @ �û���ֻ������Ȩ�ޡ�
    @ �ڸ���汾�� CVS �У�����ӵ��ȡ��Ȩ�޵�
    @ �û��Զ������ύȨ�ޡ�
    @ </p></li>
    @
    @ <li><p>
    @ �޸��û��������뽫ͬʱ�޸� CVS �ֿ��е� <b>CVSROOT/passwd</b>��
    @ <b>CVSROOT/readers</b> �� <b>CVSROOT/writers</b> �ļ���
    @ ǰ������Щ�ļ�Ҫ�п�дȨ�ޡ�
    @ �� <b>CVSROOT/passwd</b> �д��ڵĶ��� CVSTrac ��δ֪���û�����������
    if( g.okSetup ){
      @ ����ʹ��
      @ <a href="setup_user">�û�����</a> ҳ��� "���� CVS �û�" ��ť
      @ ������ CVS �е��û��� CVSTrac��
    }
    @ </p></li>
  }
  @ </ol>
  common_footer();
}

/*
** WEBPAGE: /useredit
*/
void user_edit(void){
  char **azResult;
  const char *zId, *zName, *zEMail, *zCap;
  char *oaa, *oas, *oar, *oaw, *oan, *oai, *oaj, *oao, *oap ;
  char *oak, *oad, *oaq;
  int doWrite;
  int higherUser = 0;  /* True if user being edited is SETUP and the */
                       /* user doing the editing is ADMIN.  Disallow editing */
#ifdef CVSTRAC_WINDOWS
  char *odl;           /* Domain login - used by "use Windows password" feature */
#endif

  /* Must have ADMIN privleges to access this page
  */
  login_check_credentials();
  if( !g.okAdmin ){ login_needed(); return; }

  /* Check to see if an ADMIN user is trying to edit a SETUP account.
  ** Don't allow that.
  */
  zId = P("id");
  if( zId && !g.okSetup ){
    char *zOldCaps;
    zOldCaps = db_short_query(
       "SELECT capabilities FROM user WHERE id='%q'",zId);
    higherUser = zOldCaps && strchr(zOldCaps,'s');
  }

  if( !higherUser ){
    if( P("delete") ){
      common_add_action_item("userlist", "ȡ��");
      common_header("��ȷ��Ҫɾ����");
      @ <form action="useredit" method="POST">
      @ <p>����Ҫ�����ݿ���ɾ���û� <strong>%h(zId)</strong>��
      @ ����һ�����ɻָ��Ĳ�����</p>
      @
      @ <input type="hidden" name="id" value="%t(zId)">
      @ <input type="hidden" name="nm" value="">
      @ <input type="hidden" name="em" value="">
      @ <input type="hidden" name="pw" value="">
      @ <input type="submit" name="delete2" value="ɾ�����û�">
      @ <input type="submit" name="can" value="ȡ��">
      @ </form>
      common_footer();
      return;
    }else if( P("can") ){
      cgi_redirect("userlist");
      return;
    }
  }

  /* If we have all the necessary information, write the new or
  ** modified user record.  After writing the user record, redirect
  ** to the page that displays a list of users.
  */
  doWrite = zId && zId[0] && cgi_all("nm","em","pw") && !higherUser;
  if( doWrite ){
    const char *zOldPw;
    char zCap[20];
    int i = 0;
#ifdef CVSTRAC_WINDOWS
    int dl = P("dl")!=0;
#endif
    int aa = P("aa")!=0;
    int ad = P("ad")!=0;
    int ai = P("ai")!=0;
    int aj = P("aj")!=0;
    int ak = P("ak")!=0;
    int an = P("an")!=0;
    int ao = P("ao")!=0;
    int ap = P("ap")!=0;
    int aq = P("aq")!=0;
    int ar = P("ar")!=0;
    int as = g.okSetup && P("as")!=0;
    int aw = P("aw")!=0;
    zOldPw = db_short_query("SELECT passwd FROM user WHERE id='%q'", zId);
    if( as ) aa = 1;
#ifdef CVSTRAC_WINDOWS
    /* If the admin is using external password auth
    ** don't let password change automatically
    */
    if( !dl && aa ) ai = aw = ap = 1;
    else
#endif
    if( aa ) ai = aw = 1;
    if( aw ) an = ar = 1;
    if( ai ) ao = 1;
    if( ak ) aj = 1;
    if( aa ){ zCap[i++] = 'a'; }
    if( ad ){ zCap[i++] = 'd'; }
    if( ai ){ zCap[i++] = 'i'; }
    if( aj ){ zCap[i++] = 'j'; }
    if( ak ){ zCap[i++] = 'k'; }
    if( an ){ zCap[i++] = 'n'; }
    if( ao ){ zCap[i++] = 'o'; }
    if( ap ){ zCap[i++] = 'p'; }
    if( aq ){ zCap[i++] = 'q'; }
    if( ar ){ zCap[i++] = 'r'; }
    if( as ){ zCap[i++] = 's'; }
    if( aw ){ zCap[i++] = 'w'; }

    zCap[i] = 0;
    db_execute("DELETE FROM user WHERE id='%q'", zId);
    if( !P("delete2") ){
      const char *zPw = P("pw");
      char zBuf[3];
      if( zOldPw==0 ){
        char zSeed[100];
        const char *z;
        bprintf(zSeed,sizeof(zSeed),"%d%.20s",getpid(),zId);
        z = crypt(zSeed, "aa");
        zBuf[0] = z[2];
        zBuf[1] = z[3];
        zBuf[2] = 0;
        zOldPw = zBuf;
      }
      db_execute(
         "INSERT INTO user(id,name,email,passwd,capabilities) "
         "VALUES('%q','%q','%q','%q','%s')",
         zId, P("nm"), P("em"), OS_VAL(0, dl) ? "*" : zPw[0] ? crypt(zPw, zOldPw) : zOldPw, zCap
      );
    }else{
      /* User was default assigned user id. Remove the default. */
      db_execute( "DELETE FROM config WHERE "
          "  name='assignto' AND value='%q'", zId);
    }

    /*
    ** The SCM subsystem may be able to replicate the user db somewhere...
    */
    if( g.scm.pxUserWrite ) g.scm.pxUserWrite(P("delete2")!=0 ? zId : 0);

    cgi_redirect("userlist");
    return;
  }

  /* Load the existing information about the user, if any
  */
  zName = "";
  zEMail = "";
  zCap = "";
  oaa = oad = oai = oaj = oak = oan = oao = oap = oaq = oar = oas = oaw = "";
#ifdef CVSTRAC_WINDOWS
  odl = "";
#endif
  if( zId ){
#ifdef CVSTRAC_WINDOWS
    /* "use Windows password" shall be checked when password is set to "*" */
    const char *zOldPw = db_short_query("SELECT passwd FROM user WHERE id='%q'", zId);
    if(zOldPw != 0 && zOldPw[0] == '*' && zOldPw[1] == 0) odl = " checked";
#endif
    azResult = db_query(
      "SELECT name, email, capabilities FROM user WHERE id='%q'", zId
    );
    if( azResult && azResult[0] ){
      zName = azResult[0];
      zEMail = azResult[1];
      zCap = azResult[2];
      if( strchr(zCap, 'a') ) oaa = " checked";
      if( strchr(zCap, 'd') ) oad = " checked";
      if( strchr(zCap, 'i') ) oai = " checked";
      if( strchr(zCap, 'j') ) oaj = " checked";
      if( strchr(zCap, 'k') ) oak = " checked";
      if( strchr(zCap, 'n') ) oan = " checked";
      if( strchr(zCap, 'o') ) oao = " checked";
      if( strchr(zCap, 'p') ) oap = " checked";
      if( strchr(zCap, 'q') ) oaq = " checked";
      if( strchr(zCap, 'r') ) oar = " checked";
      if( strchr(zCap, 's') ) oas = " checked";
      if( strchr(zCap, 'w') ) oaw = " checked";
    }else{
      zId = 0;
    }
  }

  /* Begin generating the page
  */
  common_standard_menu(0,0);
  common_add_help_item("CvstracAdminUsers");
  common_add_action_item("userlist", "ȡ��");
  common_add_action_item(mprintf("useredit?delete=1&id=%t",zId), "ɾ��");
  if( zId ){
    common_header("�༭�û� %s", zId);
  }else{
    common_header("�������û�");
  }
  @ <form action="%s(g.zPath)" method="POST">
  @ <table align="left" style="margin: 10px;">
  @ <tr>
  @   <td align="right" class="nowrap">�û���:</td>
  if( zId ){
    @   <td>%h(zId) <input type="hidden" name="id" value="%h(zId)"></td>
  }else{
    @   <td><input type="text" name="id" size=10></td>
  }
  @ </tr>
  @ <tr>
  @   <td align="right" class="nowrap">ȫ��:</td>
  @   <td><input type="text" name="nm" value="%h(zName)"></td>
  @ </tr>
  @ <tr>
  @   <td align="right" class="nowrap">�ʼ���ַ:</td>
  @   <td><input type="text" name="em" value="%h(zEMail)"></td>
  @ </tr>
  @ <tr>
  @   <td align="right" valign="top">�û�Ȩ��:</td>
  @   <td>
  @     <input type="checkbox" name="aa" id="aa"%s(oaa)><label for="aa">����</label><br>
  @     <input type="checkbox" name="ad" id="ad"%s(oad)><label for="ad">ɾ��</label><br>
  @     <input type="checkbox" name="ai" id="ai"%s(oai)><label for="ai">�ύ</label><br>
  @     <input type="checkbox" name="aj" id="aj"%s(oaj)><label for="aj">�� Wiki</label><br>
  @     <input type="checkbox" name="ak" id="ak"%s(oak)><label for="ak">д Wiki</label><br>
  @     <input type="checkbox" name="an" id="an"%s(oan)><label for="an">������</label><br>
  @     <input type="checkbox" name="ao" id="ao"%s(oao)><label for="ao">ȡ��</label><br>
  @     <input type="checkbox" name="ap" id="ap"%s(oap)><label for="ap">����</label><br>
  @     <input type="checkbox" name="aq" id="aq"%s(oaq)><label for="aq">��ѯ</label><br>
  @     <input type="checkbox" name="ar" id="ar"%s(oar)><label for="ar">������</label><br>
  if( g.okSetup ){
    @     <input type="checkbox" name="as" id="as"%s(oas)><label for="as">����</label><br>
  }
  @     <input type="checkbox" name="aw" id="aw"%s(oaw)><label for="aw">д����</label>
  @   </td>
  @ </tr>
  @ <tr>
  @   <td align="right">����:</td>
  @   <td><input type="password" name="pw" value=""></td>
  @ </tr>
#ifdef CVSTRAC_WINDOWS
  @ <tr>
  @   <td></td>
  @   <td><input type="checkbox" name="dl" id="dl"%s(odl)><label for="dl">ʹ�� Windows ����</label><br></td>
  @ </tr>
#endif
  if( !higherUser ){
    @ <tr>
    @   <td>&nbsp;</td>
    @   <td><input type="submit" name="submit" value="Ӧ���޸�">
    @       &nbsp;&nbsp;&nbsp;
    @       <input type="submit" name="delete" value="ɾ���û�"></td>
    @ </tr>
  }
  @ </table>
  @ <table border="0"><tr><td>
  @ <p><b>˵��:</b></p>
  @ <ol>
  if( higherUser ){
    @ <li><p>
    @ �û� %h(zId) ӵ������Ȩ�޶���ֻ�й���Ȩ�ޣ�
    @ �������������޸��û� %h(zId)��
    @ </p></li>
    @
  }
  if( g.scm.pxUserWrite!=0
        && !strcmp("yes",db_config("write_cvs_passwd","yes")) ){
    @ <li><p>
    @ ���ָ���� <b>CVS ȡ��</b> Ȩ�ޣ�
    @ ��˴����������
    @ ��д�뵽 <b>CVSROOT/passwd</b>
    @ �ļ��в�����Ϊ�÷������ϸ��û�
    @ �� CVS �������롣
    @
    @ <li><p>
    @ <b>CVS �ύ</b> Ȩ����ζ���û�����д�뵽
    @ <b>CVSROOT/writers</b> �ļ��в�ʹ���û�����д
    @ CVS �ֿ⡣
    @ </p></li>
    @
  }else{
    @ <li><p>
    @ ���ָ���� <b>ȡ��</b> Ȩ�ޣ��û����ܹ����
    @ %s(g.scm.zName) �ֿ⡣
    @ </p></li>
    @
    @ <li><p>
    @ <b>�ύ</b> Ȩ�޽������û��༭�ύ
    @ ��Ϣ��
    @ </p></li>
    @
  }
  @ <li><p>
  @ <b>������</b> �� <b>д����</b> Ȩ�������û���д
  @ ���񵥡�<b>�½�����</b> Ȩ����ζ���û�������
  @ �����µ����񵥡�
  @ </p></li>
  @
  @ <li><p>
  @ <b>ɾ��</b> Ȩ�������û�ӵ��ɾ���������û�
  @ ���ӵ� Wiki�����񵥺͸�����
  @ �������������������
  @ </p></li>
  @
  @ <li><p>
  @ <b>��ѯ</b> Ȩ�������û�ͨ��������༭ʹ���ض� SQL
  @ ���ı����ʽ���û������������еı����ʽ������Ҫ
  @ ��ѯȨ�ޡ�
  @ </p></li>
  @
  @ <li><p>
  @ һ�� <b>����</b> �û��ܹ�����������û��������µı����ʽ��
  @ �Լ��޸�ϵͳĬ��ֵ������ֻ�� <b>����</b>
  @ �û������޸ĸó������ӵ���
  @ %h(g.scm.zName) �ֿ⡣
  @ </p></li>
  @
#ifdef CVSTRAC_WINDOWS
  @ <li><p>
  @ <b>ʹ�� Windows ����</b> ѡ���ܹ��� CVSTrac ���û������� Windows
  @ �� (�����) �û����ɡ�
  @ <p>�����û��ɱ�������������Ȩ�ޣ����� CVSTrac �û���������Ըĵú�
  @ Windows �µ�ͬ���û���ͬ��
  @ </p></li>
  @
#endif
  if( zId==0 || strcmp(zId,"anonymous")==0 ){
    @ <li><p>
    @ ����Ҫ��¼���û� "<b>anonymous</b>"�����û���Ȩ�޶�����
    @ �����ã�������Ҫʹ���û����������¼��
    @ Ҫ���� anonymous �������ʣ���ȷ��ϵͳ��û��
    @ ��Ϊ <b>anonymous</b> ���û���
    @ </p></li>
    @
    @ <li><p>
    @ ָ���� "<b>anonymous</b>" �û�����������
    @ %h(g.scm.zName) �������ʡ��Ƽ�ʹ��
    @ "anonymous" ����Ϊ�����������롣
    @ </p></li>
  }
  @ </ol>
  @ </td></tr></table>
  @ </form>
  common_footer();
}

/*
** Remove the newline from the end of a string.
*/
void remove_newline(char *z){
  while( *z && *z!='\n' && *z!='\r' ){ z++; }
  if( *z ){ *z = 0; }
}
