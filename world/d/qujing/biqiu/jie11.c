// cracked by vikee 2/09/2002   vikee@263.net
// created by snowcat 11/21/1997

inherit ROOM;

void create ()
{
  set ("short", "街坊");
  set ("long", @LONG

街道自道场东面绕过，路面由青石铺就的街坊，中间是五六
尺长两尺宽的三条石，路边上是的平卵石。街道顺着地势而
筑，西边的道场里不时传来人声。

LONG);

  set("exits", ([
        "northwest"    : __DIR__"jie10",
        "southeast"    : __DIR__"jie12",
        "west"    : __DIR__"daochang",
      ]));
  set("objects", ([
        __DIR__"npc/people"    : 1,
      ]));
  set("outdoors",__DIR__"");
  setup();
}

