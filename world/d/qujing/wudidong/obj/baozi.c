// cracked by vikee 2/09/2002   vikee@263.net
// dumpling.c

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("�����", ({ "bao zi","baozi","bao", "dumpling" }) );
  set_weight(80);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", 
"һ�������硢�����ڵĴ���ӡ�\n");
    set("unit", "��");
    set("value", 1);
    set("food_remaining", 4);
    set("food_supply", 100);
  }
}
