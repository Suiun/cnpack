<?php

require_once ('config.php');
require_once ('db_mysql.inc');

$g_lang['DatabaseErrorDebug'] = "���ݿ����%s<br><br>\nMySQL ����%d (%s)";
$g_lang['DatabaseError'] = "��Ч�����ݷ��ʣ�";

//==============================================================================
// ȫ�ֹ�������
//==============================================================================

// �õ���ǰ����
function get_date()
{
  return date('Y-m-d');
}

// �õ���ǰʱ��
function get_time()
{
  return date('H:i:s');
}  

// �õ�����ʱ��
function get_datetime()
{
	return date("Y-m-d H:i:s");
}

// ȡ����ʱ������������$time2 - $time1����� $time2 Ϊ�գ�ʹ�õ�ǰʱ�����
function get_diff_days($time1, $time2 = '')
{
  if (is_string($time1))
    $time1 = strtotime($time1);
  if ($time2 == '')
    $time2 = time();
  elseif (is_string($time2))
    $time2 = strtotime($time2);
  return floor(($time2 - $time1) / 60 / 60 / 24);
}

// ��֤�Ǹ�ʽ��Ч�� Email ��ַ
function is_valid_email($email)
{
  $result = isset($email) && strstr($email, '@') &&
    ($email == addslashes($email)) && ($email == htmlspecialchars($email));
  return $result;
}

// ȡ�û��ύ�Ĳ���
function get_request($name, $default = '', $valid = '', $delete_ctrlchar = true)
{
  $result = $_REQUEST[$name];
  if (empty($result) || ($valid != '') && ($result != $valid))
    $result = $default;
  // ���˵�����ȫ�Ŀ����ַ�
  if ($delete_ctrlchar)
    $result = preg_replace("[;_'<>\"]", "", $result);
  return $result;
}

// ȡ�û��ύ����������
function get_int_request($name, $default = '', $valid = '', $delete_ctrlchar = true)
{
  return (integer) get_request($name, $default, $valid, $delete_ctrlchar);
}

// ���ش����Բ������������
function get_link($link)
{
  global $lang;
  if (ereg("([?&]{1})lang=", $link) || strstr($link, "://")) {
    // �Ѿ��������Բ����Ļ����ӵ������ط��Ĳ��޸�
  	return $link;
  } else {
    if (strstr($link, "?"))
      return $link."&lang=".$lang;
    else
      return $link."?lang=".$lang;
  }
}

// ��������з����ı�
function output($html = '')
{
  echo $html."\n";
}

// ���һ������
function output_url($url, $text = '', $head = '', $tail = '')
{
  if ($text == '')
    $text = $url;
  echo "$head<a href=\"$url\">".$text."</a>$tail";
}

// ��� JavaScript �Ի�����Ϣ
function output_alert($msg = '')
{
  echo "<script type=\"text/javascript\">\n".
       "<!--\n".
       "alert(\"".$msg."\");\n".
       "-->\n".
       "</script>\n";
}

// ��ʾ������Ϣ����
function halt($msg = '')
{
  global $g_lang;
  output("<hr>");
  output("<font size=3><b>".$g_lang['Error']."</b></font><p>");
  output($msg."<br>");
  output("<hr>");
  output('<input type="button" value="'.$g_lang['Back'].'" onclick="javascript:history.back();">');
  exit();
}

//==============================================================================
// ������ع�������
//==============================================================================

// ���������Ϣ
function debug_output($msg)
{
  global $debug;
	if (isset($debug) && $debug != 0)
		echo $msg."<br>\n";
}

// ��鴫�ݵ�ֵ���Ƿ��У��Ƿ�Ϊ�գ�
function filled_out($form_vars, $check_has_vars = 0)
{
  // ������һ��Ҫ��
  if ( 0 == count($form_vars) && $check_has_vars == 1)
    return false;

  // ���ÿ������һ��Ҫ���ڣ�����Ҫ��ֵ
  foreach ($form_vars as $key => $value)
  {
  	 debug_output("$key = $value");
     if (!isset($key) || ($value == ""))
        return false;
  }
  return true;
}

// dump_array ��������������
// $array     Ҫ������������
// to represent the array as a set
function dump_array($array)
{
  if(is_array($array))
  {
    $size = count($array);
    $string = "";
    if($size)
    {
      $count = 0;
      $string .= "{ ";
      // add each element's key and value to the string
      foreach($array as $var => $value)
      {
        $string .= "$var = '$value'";
        if($count++ < ($size-1))
        {
          $string .= ", ";
        }
      }
      $string .= " }";
    }
    return $string;
  }
  else
  {
    // ����������飬�򷵻ر���
    return $array;
  }
}

function dump_sys_vars()
{
  global $HTTP_GET_VARS;
  global $HTTP_POST_VARS;
  global $HTTP_POST_FILES;
  global $HTTP_SESSION_VARS;
  global $HTTP_COOKIE_VARS;

  return "\n<!-- BEGIN VARIABLE DUMP -->\n\n".
         "<!-- BEGIN GET VARS -->\n".
         
         "<!-- ".dump_array($HTTP_GET_VARS)." -->\n".
         "<!-- BEGIN POST VARS -->\n".
         
         "<!-- ".dump_array($HTTP_POST_VARS)." -->\n".
         "<!-- BEGIN POST FILES -->\n".
         
         "<!-- ".dump_array($HTTP_POST_FILES)." -->\n".
         "<!-- BEGIN SESSION VARS -->\n".
         
         "<!-- ".dump_array($HTTP_SESSION_VARS)." -->\n".
         "<!-- BEGIN COOKIE VARS -->\n".
         
         "<!-- ".dump_array($HTTP_COOKIE_VARS)." -->\n".
         "\n<!-- END VARIABLE DUMP -->\n";
}

// output_vars ��ʾ���õ��������
function output_vars()
{
  echo dump_sys_vars();
}

// user_error_handler �Զ����������
// $errno 	������
// $errstr  ������Ϣ
function user_error_handler ($errno, $errstr)
{
  echo "<table bgcolor = '#cccccc'><tr><td>
        <P><B>ERROR:</B> $errstr
        <P>Please try again, or contact us and tell us that
        the error occurred in line ".__LINE__." of file '".__FILE__."'";
  if ($errno == E_USER_ERROR||$errno == E_ERROR)
  {
    echo "<P>This error was fatal, program ending";
    echo "</td></tr></table><br>";
    exit;
  }
  echo "</td></tr></table><br>";
}

// ���������
function rndkey($lng){
 $char_list = array();
 $char_list[] = "1234567890";
 $char_list[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 $char_list[] = "abcdefghijklmnopqrstuvwxyz";
 $char_list[] = "!@^()_:+\-";
 $char_length = count($char_list);
 $rnd_Key = "";
 for($i=1; $i<=$lng; $i++){
  $rnd_Str  = $char_list[rand(1,$char_length) - 1];
  $rnd_Key .= substr($rnd_Str, rand(0,strlen($rnd_Str)-1), 1);
 }
 return($rnd_Key);
}

// �û����ݿ���
class db extends DB_Sql 
{
  function db($query = "")
  {
    global $g_sys_vars;
    global $debug;
    $this->Debug = $debug;
    $this->Host = $g_sys_vars['dbhost'];
    $this->Database = $g_sys_vars['dbname'];
    $this->User = $g_sys_vars['dbuser'];
    $this->Password = $g_sys_vars['dbpasswd'];
    
    $this->DB_Sql($query);
  }
  
  function halt($msg)
  {
    global $g_lang;
    if ($this->Debug)
      halt(printf($g_lang['DatabaseErrorDebug'], $msg, $this->Errno, $this->Error));
    else 
      halt($g_lang['DatabaseError']);
  }
}

?>