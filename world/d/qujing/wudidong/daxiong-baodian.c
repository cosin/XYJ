// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/qujing/wudidong/daxiong-baodian.c

inherit ROOM;

void create()
{
	set("short", "���۱���");
	set("long", @LONG

�˰��޺����Ĵ�������������������Ӧ�о��У����е㺼��������
��ζ��Ҳ����Ϊ�������������𲢲��Ǻܷ�ʢ��
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"temple",
]));
	set("no_clean_up", 0);
set("no_mieyao",1);
	set("outdoors", 0);

	setup();
	replace_program(ROOM);
}