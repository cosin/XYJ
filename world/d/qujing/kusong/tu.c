// cracked by vikee 2/09/2002   vikee@263.net
inherit ROOM;

void create ()
{
  set ("short", "���춴");
  set ("long", @LONG

һ���������С�ң����������ض����õġ�
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"huoyun", 
]));
  set("objects", ([ /* sizeof() == 1*/
  __DIR__"obj/che" : 1,
]));



  setup();
}
