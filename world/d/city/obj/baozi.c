// cracked by vikee 2/09/2002   vikee@263.net
// baozi.c ����

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("����", ({"baozi", "dumpling"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�������������ӡ�\n");
		set("unit", "��");
		set("value", 15);
		set("food_remaining", 3);
		set("food_supply", 20);
	}
}