// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/cloud/cloud1.c  east of cloud0

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�ƶ�");

	set("long", @LONG

    ��վ���ƶˣ���������ȥ��������һ���޼ʵ��ƺ���ͷ���Ǳ�������ա�
������ȥ��ֻ��һƬ������ɫ��ż����һЩϸϸ�İ��߹ᴩ���С�һֻС��
ݺ���ĵش��ƴ���̽��ͷ�����ܾ��ȵؿ����㡣

LONG
	);

	set("exits", ([
		"south" 	: __DIR__"cloud2.c",
		"west"		: __DIR__"cloud0.c",
		"northwest"	: __DIR__"cloud7.c",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
        me->add("mana", -10);

	return ::valid_leave(me, dir);
}
