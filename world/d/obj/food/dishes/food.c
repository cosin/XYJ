// cracked by vikee 2/09/2002   vikee@263.net

inherit ITEM;
inherit F_FOOD;

string *food_name= ({"������˿",
                "��������",
		"÷�˿���",
		"��������",
		"������˿",
		"���ͼ�Ƭ",
		"�峴Ϻ��",
		"�廨����",
		"��˿Ѭ��",
		"�Ǵ��Ź�",
		"������˿",
		"������Ϻ",
		"��Ƥ��Ѽ",
		"�����ض�",
		"��������",
		"������˿",
		"���ͷ�Ƭ",
		"��������",
		"���ʹ೦",
		"��������",
		"���㶬��",
		"��䶹��",
		"���Ŷ���",
		"���ʸ���",
});

string *eat_msg=({
	  "$N����������Щ$name���ŵ����г���������\n",
	  "$N����һ���$name��\n",
	  "$N���˳�$name��\n",
	  "$N����Щ$name���ŵ����С�\n",
	  "$NϸϸƷ����$name��\n",
	  });

void create()
{	string name = "������";
  	set_name(name, ({"food"}));
  	set_weight(1000);
  	if (clonep())
   		 set_default_object(__FILE__);
  	else {
    		set("long", "һ�����˴��ѵĻ����ˡ�\n");
    		set("unit", "��");
//		set("eat_msg", "$N����������Щ" + name + "���ŵ����г���������\n");
    		set("value", 250);
    		set("food_remaining", 5);
    		set("food_supply", 20);
  	}
}

void init ()
{
	if (query("name")=="������")
	{
		string name;
		name=food_name[random(sizeof(food_name))];
  		set_name(name, ({"food"}));
		set("long", "һ�����˴��ѵ�"+name+"��\n");
//		set("eat_msg", "$N����������Щ" + name + "���ŵ����г���������\n");
	}
        if(!wizardp(this_player())) {
        	set("no_get", "�ڻ�������ô���ƺ�����ðɣ�\n");
        }
        add_action("do_get", "get");
        add_action("do_eat", "eat");
	::init();
}

int do_eat (string arg)
{
  object me = this_object();
  object who = this_player();
  string name=query("name");
  int i;

  set("eat_msg", replace_string(eat_msg[random(sizeof(eat_msg))],
	  "$name",name));
  i=::do_eat(arg);
  if(i && name=="��������") {
      if(!who->query_temp("xifuhui_eatcorn")) {
       if(who->query("gender")=="Ů��" && who->query("married")) {
	  string id;
	  if(id=who->query("couple/id")) {
	      object ob;
	      if(ob=present(id, environment(me))) {
		  message_vision("���˿���$N��$n��������Ц����"+
			  "�����������ף���ϲ����ϲ��\n",who,ob);
		  who->add_temp("xifuhui_eatcorn",1);
		  // this will be used in born child later.
	      }
	  }
       }
      }
  }
  return i;
}

int do_get (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! arg)
    return 0;

  if (present(arg,environment(who))==me)
  {
    tell_object(who,"�ڻ�������ô���ƺ�����ðɣ�\n");
    return 1;
  }
  return 0;
}
