// cracked by vikee 2/09/2002   vikee@263.net
// huadiao-jiudai.c  ����ƴ�

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("����ƴ�", ({"jiudai", "skin", "huadiao"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������װ�߼�����ƵĴ�ƴ���\n");
		set("unit", "��");
		set("value", 80);
		set("max_liquid", 5);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
		"type": "alcohol",
		"name": "�����",
		"remaining": 5,
		"drunk_apply": 10,
	]));
}
