// cracked by vikee 2/09/2002   vikee@263.net
// create by snowcat.c 12/8/1997

inherit ROOM;

void create ()
{
  set ("short", "�͵�");
  set ("long", @LONG

�͵��������Ŵ����ӣ��˰�ľ�Σ�ǽ�߻����������������ʣ�
������Ъ�š��������һ��̨���������һЩС��֮���ʳ
Ʒ���걱�ٽ֣���ʱ�пͽ�����

LONG);

  set("exits", ([
        "north"   : __DIR__"xiaojie5",
      ]));
  set("objects", ([
        __DIR__"npc/dianzhu"   : 1,
      ]));
  set("valid_startroom",1);

  setup();
}

