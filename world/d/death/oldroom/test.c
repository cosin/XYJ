// cracked by vikee 2/09/2002   vikee@263.net
inherit ROOM;

void create()
{
  set ("short", "���������");
  set ("long", @LONG

�����������ͨ�������Ψһ���ڣ�����š�������ԩ����Ͷ
̥�����ɴ˳����䡣�Ϸ���һ�����Ʒ��������Ʒ�����һ��ʲ
ôҲ��������
LONG);
  set("item_desc", ([ /* sizeof() == 1 */
  "out" : "�Ʒ�����һ��ʲôҲ��������\n",
]));

set("exits", ([ /* sizeof() == 4 */
"northwest" : __DIR__"pingyang",
]));
	set("hell", 1);
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_out", "out");
}

int do_out()
{//	string owner;
        object me, zhenshen;
	me=this_player();

	if( me->query_temp("in_hell")) {
		if( zhenshen=me->query_temp("zhenshen")) {
			me->move(environment(zhenshen));
			destruct(zhenshen);
			me->delete_temp("in_hell");
			message_vision("$N�����۾����ƺ������˹�����\n", me);
			return 1;
		}
	}
        me->move("/d/death/out");
        me->delete_temp("in_hell");
        return 1;
}
