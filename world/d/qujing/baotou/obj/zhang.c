// cracked by vikee 2/09/2002   vikee@263.net

#include <weapon.h>

inherit F_UNIQUE; 
inherit STAFF;

void create()
{
  set_name("С������", ({"xiao xiangyao zhang", "xiangyaozhang", "zhang", "staff"}));
  set_weight(10000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("value", 2000);
    set("material", "iron");
    set("no_sell", 1);
    set("no_drop", 1);
    set("is_monitored", 1);
    set("replace_file", "/d/obj/weapon/staff/gangzhang");
    set("long", "����һ�����������ȣ���ͷΪ�����ɡ�\n");
    set("wield_msg", "$N���ֳ��һ��$n���������ϵ�һ�ա�\n");
    set("unequip_msg", "$N�����е�$n�ϵط��¡�\n");
  }
  init_staff(65);
  setup();
}

void destruct_me(object where, object me)
{
  message_vision("һ������������$n��ͻ��������ϼ�������ˣ�\n",where,me);
  destruct (me);
}

void init()
{
  object me = this_object();
  object where = environment();

  ::init();
  if (interactive(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,where,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
}
