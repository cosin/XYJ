// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/nanhai/road1
inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG

����һ��ͨ����ɽ��С·��
LONG);

  set("outdoors", "/d/nanhai");
  set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"guangchang",
  "northdown" : __DIR__"road22",
]));

  setup();
}