// cracked by vikee 2/09/2002   vikee@263.net
// created by snowcat 12/2/1997

inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

���������һ����������Ӵ�����һֱ�̵������������
�ط��žƹ��ӣ��־���͵��ĵ��ӣ���������һЩ����Ƥ�ǡ�
��λ�ƿ���ҡͷ���Եز��ž�ȭ��

LONG);

  set("exits", ([
        "west"    : __DIR__"jiedao3",
      ]));
  set("objects", ([
        __DIR__"npc/zhou"    : 1,
      ]));
  setup();
}
