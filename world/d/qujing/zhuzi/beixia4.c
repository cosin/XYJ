// cracked by vikee 2/09/2002   vikee@263.net
// by snowcat 11/6/1997
inherit ROOM;

void create()
{
  set ("short", "��ϼ��");
  set ("long", @LONG

��ϼ���ǳǱ�һ��������Ĵ��������������ഫ�����Ϲ�������
���γǱ�ҹ��ϼ���������Ȼ��ʥ���ﻳ̥����̫�ӣ��ʽ��˽���
��Ϊ��ϼ����ʾ���顣�����Ƿ������ֵĽֿڡ�

LONG);

  set("exits", ([ 
    "west" : __DIR__"jiekou",
    "east" : __DIR__"beixia5",
  ]));
  set("outdoors", __DIR__"");
  setup();
}