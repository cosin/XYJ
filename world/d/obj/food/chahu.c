// cracked by vikee 2/09/2002   vikee@263.net
#include <weapon.h>

inherit HAMMER;
inherit F_LIQUID;

void create()
{
  set_name("����", ({"teapot"}));
  set_weight(2000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "һ��������\n");
    set("unit", "��");
    set("value", 50);
    set("max_liquid", 7);
    set("wield_msg", "$Nץ��һ��$n���������е�������\n");
    set("material", "bone");
  }
  
  set("liquid", ([
		  "type": "water",
		  "name": "����������",
		  "remaining": 8,
		  ]) );
  init_hammer(1);
  setup();

}
