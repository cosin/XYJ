// cracked by vikee 2/09/2002   vikee@263.net
//se1.c
//created 4-8-97 pickle

#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "�칬ǽ��");
  set ("long", @LONG

    ������������е������쳣�����ʣ�����Ҳ��֮��ĺܺá�����
���칬�ĸ�ǽ����ۺ����ĳ�������ͨ��������칬�������½��
�������ɳ�ǽ�������������ŵ����ա�������͵�ǽ�����ԼԼ��
�ǹ���ķ��ܡ�����ңң���Կ��������š�

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"nantian",
  "east" : __DIR__"se",
]));
  set("outdoors", 1);

  setup();
}