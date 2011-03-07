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
** Code to generate the index page
*/
#include "config.h"
#include "index.h"

/*
** Return TRUE if the given string contains at least one non-space
** character
*/
static int not_blank(const char *z){
  while( isspace(*z) ){ z++; }
  return *z!=0;
}

/*
** WEBPAGE: /
** WEBPAGE: /index
** WEBPAGE: /index.html
** WEBPAGE: /mainmenu
*/
void index_page(void){
  int cnt = 0;
  login_check_credentials();
  common_standard_menu("index", 0);

  common_add_help_item("CvstracDocumentation");

  /* If the user has wiki read permission and a wiki page named HomePage
  ** exists and is not empty and is locked (meaning that only an
  ** administrator could have created it), then use that page as the
  ** main menu rather than the built-in main menu.
  **
  ** The built-in main menu is always reachable using the /mainmenu URL
  ** instead of "/index" or "/".
  */
  if( g.okRdWiki && g.zPath[0]!='m' ){
    char *zBody = db_short_query(
        "SELECT text FROM wiki WHERE name='HomePage' AND locked");
    if( zBody && not_blank(zBody) ){
      common_add_nav_item("mainmenu", "���˵�");
      common_header("��ҳ");
      /* menu_sidebar(); */
      output_wiki(zBody, "", "HomePage");
      common_footer();
      return;
    }
  }

  /* Render the built-in main-menu page.
  */
  common_header("���˵�");
  @ <dl id="index">
  if( g.zPath[0]=='m' ){
    @ <dt>
    @ <a href="index"><b>��ҳ</b></a>
    @ </dt>
    @ <dd>
    @ �鿴����Ŀ���� Wiki ����ҳ��
    @ </dd>
    @
    cnt++;
  }
  if( g.okNewTkt ){
    @ <dt>
    @ <a href="tktnew"><b>����</b></a>
    @ </dt>
    @ <dd>
    @ Ϊ���󱨸���ܸĽ�������һ���µ����񵥡�
    @ </dd>
    @
    cnt++;
  }
  if( g.okCheckout ){
    @ <dt>
    @ <a href="%h(default_browse_url())"><b>���</b></a>
    @ </dt>
    @ <dd>
    @ ��� %s(g.scm.zName) �ֿ�����
    @ </dd>
    @
    cnt++;
  }
  if( g.okRead ){
    @ <dt>
    @ <a href="reportlist"><b>����</b></a>
    @ </dt>
    @ <dd>
    @ �鿴�������񵥵�ժҪ����
    @ </dd>
    @
    cnt++;
  }
  if( g.okRdWiki || g.okRead || g.okCheckout ){
    @ <dt>
    @ <a href="timeline"><b>ʱ����</b></a>
    @ </dt>
    @ <dd>
    @ �鿴���� CVS �ύ�����񵥸��¼�¼��
    @ </dd>
    @ 
    cnt++;
  }
  if( g.okRdWiki ){
    @ <dt>
    @ <a href="wiki"><b>Wiki</b></a>
    @ </dt>
    @ <dd>
    @ �鿴 Wiki �ĵ�ҳ�档
    @ </dd>
    cnt++;
  }
  if( g.okRead || g.okCheckout || g.okRdWiki ){
    const char *az[5];
    int n=0;
    if( g.okRead ) az[n++] = "����";
    if( g.okCheckout ) az[n++] = "�ύ��¼";
    if( g.okRdWiki ) az[n++] = "Wiki ҳ��";
    if( g.okCheckout ) az[n++] = "�ļ���";
    @ <dt>
    @ <a href="search"><b>����</b></a>
    @ </dt>
    @ <dd>
    if( n==4 ){
      @ ͨ���ؼ����� %s(az[0])��%s(az[1])��%s(az[2]) ��/�� %s(az[3]) �н���������
    }else if( n==3 ){
      @ ͨ���ؼ����� %s(az[0])��%s(az[1]) ��/�� %s(az[2]) �н���������
    }else if( n==2 ){
      @ ͨ���ؼ����� %s(az[0]) ��/�� %s(az[1]) �н���������
    }else{
      @ ͨ���ؼ����� %s(az[0]) �н���������
    }
    @ </dd>
    @
    cnt++;
  }
  if( g.okCheckin ){
    @ <dt>
    @ <a href="msnew"><b>��̱�</b></a>
    @ </dt>
    @ <dd>
    @ ����һ���µ���Ŀ��̱���
    @ </dd>
    @ 
    cnt++;
  }
  if( g.okWrite && !g.isAnon ){
    @ <dt>
    @ <a href="userlist"><b>�û�</b></a>
    @ </dt>
    @ <dd>
    @ �������޸ĺ�ɾ���û���
    @ </dd>
    @ 
    cnt++;
  }
  if( g.okAdmin ){
    @ <dt>
    @ <a href="setup"><b>����</b></a>
    @ </dt>
    @ <dd>
    @ ����ȫ��ϵͳ������
    @ </dd>
    @ 
    cnt++;
  }
  if( g.okRdWiki ){
    @ <dt>
    @ <a href="wiki?p=CvstracDocumentation"><b>�ĵ�</b></a>
    @ </dt>
    @ <dd>
    @ �Ķ�����ʹ���ֲᡣ
    @ </dd>
    @
    cnt++;
  }
  if( g.isAnon ){
    if( cnt==0 ){
      login_needed();
      return;
    }
    @ <dt>
    @ <a href="login"><b>��¼</b></a>
    @ </dt>
    @ <dd>
    @ ��¼ϵͳ��
    @ </dd>
    @ 
  }else{
    @ <dt>
    @ <a href="logout"><b>ע��</b></a>
    @ </dt>
    @ <dd>
    @ ע�����޸����롣
    @ </dd>
    @ 
  }
  @ </dl>
  @ 
  common_footer();
}
