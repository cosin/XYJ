// cracked by vikee 2/09/2002   vikee@263.net
// create by snowcat.c 12/8/1997

inherit ROOM;

void create ()
{
  set ("short", "ʯǽ");
  set ("long", @LONG

ǽ�����棬�߸ߵ�ʯǽ�£���һ��խ��ͨ����С·һ�㣬����
�ȵý��ʵʵ��

LONG);

  set("exits", ([
        "west"   : __DIR__"shi1",
        "east"   : __DIR__"menlou",
      ]));
  set("outdoors", __DIR__);

  setup();
}


