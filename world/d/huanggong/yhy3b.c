// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/huanggong/yhy3b
inherit ROOM;

void create ()
{
  set ("short", "����԰");
  set ("long", @LONG

�д�����������԰����������������ɫ���η��˵��滨����
�м���������ת������ʯ��С����Ϊ��������紵������
���ⴼ�����ޱȣ����˻�Ȼ������

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yhy2b.c",
  "southwest" : __DIR__"damen",
]));
  set("outdoors", "/d/huanggong");

  setup();
}