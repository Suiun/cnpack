#! /bin/sh

# �ռ����ʼ���ַ
mailto=$1
# %a �����񵥷�������û��� 
assignto=$2
# %d ������Ϣ 
desc=$3
# %n ���񵥱�� 
number=$4
# %p ��Ŀ���� 
project=$5
# %r ��ע��Ϣ 
remark=$6
# %s ���񵥵�״̬ 
status=$7
# %t ���񵥵ı��� 
title=$8
# %u �޸ĸ����񵥵��û��� 
change_user=$9

# ������
sender="cvstrac"
# ��������ʾ��
sender_name="CVSTrac֪ͨ"
# ��������
url="http://www.cnpack.org:8008/$project/tktview?tn="

email_title="[���񵥸���] $title"
email_content="$project - ���񵥸���֪ͨ\n\n���� $number: $title\n\n$desc\n\n���񵥱�ע:\n\n$remark\n\n��������:\n\n״̬: $status\n�����: $assignto\n�޸���: $change_user\n\n$url$number"

printf "From: \"$sender_name\" <$sender>\nTo: $mailto\nCc:\nSubject: $email_title\n$email_content"|/var/qmail/bin/sendmail -oi -oem "$mailto"
