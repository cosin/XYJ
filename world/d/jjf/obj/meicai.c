// cracked by vikee 2/09/2002   vikee@263.net
// created 5-15-97 pickle

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("÷�˿���", ({"meicai kourou", "kourou", "rou"}));
  set_weight(200);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "һ���������÷�˿��⡣\n");
    set("unit", "��");
    set("value", 0);
    set("food_remaining", 5);
    set("food_supply", 40);
  }
}
