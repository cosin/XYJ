// cracked by vikee 2/09/2002   vikee@263.net
// by snowcat 11/6/1997
inherit ROOM;

void create()
{
  set ("short", "朱紫街");
  set ("long", @LONG

朱紫国的中心大道，由附近山上运来的条石铺成，可通行来往马车。
往北是朱紫国的城中心鼓楼，东南有一飘着旌旗的兵营，再往南可见
朱紫国皇宫。

LONG);

  set("exits", ([ 
    "south" : __DIR__"zhuzi5",
    "north" : __DIR__"gulou",
  ]));
  set("objects", ([
    __DIR__"npc/people" : 2,
  ]));
  set("outdoors", __DIR__"");
  setup();
}
