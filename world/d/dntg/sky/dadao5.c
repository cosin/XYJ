// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/sky/nantianmen
 
#include <room.h>
#include <ansi.h>
inherit ROOM;

void init();
void close_gate();
int do_knock(string);
int valid_leave();
string look_gate();

void create ()
{
  set ("short", "�칬���");
  set ("long", @LONG

һ���������ֱ����չ��ȥ��ֱͨ�����š����ϲ�ʱ�߹�����
Ѳ���������ֵ��������������ݡ�

LONG);

  set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"dadao6",
  "south" : __DIR__"dadao4",

]));


   set("outdoors", 1);


  setup();
}
 