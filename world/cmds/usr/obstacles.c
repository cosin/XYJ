// cracked by vikee 2/09/2002   vikee@263.net

inherit F_CLEAN_UP;

#include <ansi.h>
#include <obstacle.h>

int telling1 (object who);
int telling2 (object who);

string name;

int main(object me, string arg)
{
	object ob;

	if( !arg ) {
		ob = me;
		name = "��";
	} else if (wizardp (me)) {
		ob = find_player(arg);
		if(!ob) ob = find_living(arg);
	
		if(!ob) ob = LOGIN_D->find_body(arg);

		if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");

		name = ob->query("name");
	} else
		return 0;

	telling1(ob);
	telling2(ob);

	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��obstacles <ĳ��>

��ʾĳ��������ȡ�澭�����ϡ� 

�����help qujing
TEXT
	);
	return 1;
}

int telling1 (object who)
{
  int size = sizeof(obstacles);
  string *names = keys(obstacles);
  string *strs = allocate (size);
  int nb = 0;
  int i;

  for (i = 0; i < size; i++)
  {
    strs[i] = "none";
  }

  for (i = 0; i < size; i++)
  {
    if (who->query("qujing/"+names[i])=="done")
    {
      strs[nb] = obstacles[names[i]];
      nb++;
    }
  }

  if (nb == 0)
  {
    write (name+"��δ������ȡ�澭��\n");
  }
  else
  {
    write (name+"������ȡ�澭�ѹ���"+chinese_number(nb)+"�أ�\n");
    who->set("qujing/number",nb);
    strs = (string *)sort_array (strs, 1);
    for (i = 0; i < nb; i++)
    {
      write ("    "+strs[i]+"\n");
    }
  }
  return 1;
}

int telling2 (object who)
{
  int size = sizeof(obstacles);
  string *names = keys(obstacles);
  string *strs = allocate (size);
  int nb = 0;
  int i;

  for (i = 0; i < size; i++)
  {
    strs[i] = "none";
  }

  for (i = 0; i < size; i++)
  {
    if (who->query("qujing/"+names[i])!="done")
    {
      strs[nb] = obstacles[names[i]];
      nb++;
    }
  }

  if (nb == 0)
  {
    write (name+"������ȡ�澭�����������е��ѹء�\n");
  }
  else
  {
    write (name+"������ȡ�澭�����"+chinese_number(nb)+"�أ�\n");
    strs = (string *)sort_array (strs, 1);
    for (i = 0; i < nb; i++)
    {
      write ("    "+strs[i]+"\n");
    }
  }
  return 1;
}
