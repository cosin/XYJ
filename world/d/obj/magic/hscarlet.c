// cracked by vikee 2/09/2002   vikee@263.net
// created by snowcat
// 5/22/1997

#include <weapon.h>
#include <armor.h>
#include "hair.h"

inherit NECK;

void create()
{
  set_name("�ɫ��ë", ({ "scarlet hair", "scarlethair", "hair" }) );
  set_weight(100);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "һ��糺�ɫ�ĺ�ë�������������������transform����\n");
    set("unit", "��");
    set("value",10000);
    set("material","hair");
    set("armor_prop/armor",1);
  }
  set("no_drop",1);
  set("no_get",1);
  set("no_sell",1);
  setup();
}

string name_suffix()
{
  return "����";
}

string new_unit()
{
  return "��";
}

int init ()  
{   
  add_action ("do_transform", "transform");
  add_action ("do_wear", "wear");
  return 1;
}

int do_wear (string arg)
{
  object me = this_player();
  object ob = this_object();

  if (!arg || present (arg,environment(ob))!=ob)
    return 0; // to invoke standard function
  if (!ob->query("has_transformed")) {
    tell_object (me,"���Ƚ������������Ҫ��������\n");
    return 1;
  }
  return 0; // to invoke standard function
}
