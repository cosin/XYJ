// cracked by vikee 2/09/2002   vikee@263.net

//self-made fabao room, by tool.

//upgraded, weiqi...981205

#include <ansi.h>
#include <weapon.h>
#include <armor.h>
#include <login.h>

inherit ROOM;

#define MAX_FABAO	3

int  do_sm();
int  do_dispose(string arg);
int  do_upgrade(string arg);
int  do_list();
int  do_cost(string arg);

void get_type(string arg, object ob);
void get_subtype(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void get_unit(string arg, object ob);
void build_weapon(object ob);
void build_armor(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string name);
void confirm_dispose(string arg, object ob, object fabao_ob);

void init()
{
	add_action("do_sm", "make_fabao");
	add_action("do_dispose", "dispose");
	add_action("do_list", "list");
	add_action("do_cost", "cost");
	add_action("do_upgrade", "upgrade");
	add_action("do_change_name", "change_name");
	add_action("do_change_id", "change_id");
	add_action("do_change_desc", "change_desc");
	add_action("do_change_unit", "change_unit");

	/*add_action("is_valid_fabao_command", "make_fabao");
	add_action("is_valid_fabao_command", "dispose");
	add_action("is_valid_fabao_command", "list");
	add_action("is_valid_fabao_command", "cost");
	add_action("is_valid_fabao_command", "upgrade");
	add_action("is_valid_fabao_command", "change_name");
	add_action("is_valid_fabao_command", "change_id");
	add_action("is_valid_fabao_command", "change_desc");
	add_action("is_valid_fabao_command", "change_unit");*/

	seteuid(getuid());
}

int is_valid_fabao_command()
{
	notify_fail("��ʱ�������Ʒ�����\n");
	return 0;
}

void create ()
{
        set ("short", "Ů洲��촦");
        set ("long", @LONG

������һƬ�����ء�����������һ����һ�����ι�״ɫ�ʰ�쵵�
������ʯ����ѩɫӳ����������⡣����һ���ʯ�Ͽ��ż��д�
�֣�

		���ؾ���
		Ů洲���
		��ʯδ��
		�Ÿ�����

���»���������ؿ���һƪС��(words)����Զ��Ҳ������˵����
ʲô��
LONG);

	set("item_desc", ([ "words" : 
		"make_fabao     ���Ʒ���\n" +
		"dispose        ע������\n" +
		"list           �оٿ��Ʒ�������\n" +
		"upgrade        ��������\n" +
		"cost ����      �������Ƽ��������ܷ���\n" +
		"change_name    ����������\n" +
		"change_id      �������Ĵ���\n" +
		"change_desc    ������������\n" +
		"change_unit    �������ĵ�λ����\n\n", ]) );

	set("exits", 
	([ //sizeof() == 1 
		"east" : __DIR__"fabao-road2",
	]));


	set("no_fight", 1);
	set("no_magic", 1);

	setup();
}

int do_sm()
{
	object me = this_player();
	int  fabao_num;
		   
	if( me->query("daoxing") < 20000)
		return notify_fail("��ĵ���̫�ͣ��������취����\n");

	if( RANK_D->grade_fali( RANK_D->describe_fali( (int)me->query("max_mana") ) ) 
                < RANK_D->grade_fali(HIB "���Ƽ���" NOR) ) //max_mana 360+.
		return notify_fail("��ķ�����Ϊ�������޷����Ʒ�����\n");
		
	if( me->query("max_force") < 300)
		return notify_fail("���������Ϊ�������������취����\n");
	
	if( me->query("force") < (me->query("max_force")+100) )
		return notify_fail("�������������ʱ���취����\n");
	
	if( me->query("mana") < (me->query("max_mana")+100) )
		return notify_fail("���Ŀǰ����������ӯ���޷����Ʒ�����\n");
	
	fabao_num = 0;		
	if( me->query("fabao/weapon") )		fabao_num++;
	if( me->query("fabao/armor1") )		fabao_num++;
	if( me->query("fabao/armor2") )		fabao_num++;
	
	if( fabao_num >= MAX_FABAO )
		return notify_fail("�㲻�������Ʒ����ˣ����� dispose ע����Ҫ�ķ�����\n");
		
	write("��Ҫ�����෨����\n");
	if( !me->query("fabao/weapon") )
		write("w. ����\n");
	if( !me->query("fabao/armor1") || !me->query("fabao/armor2") )
		write("a. ����\n");
	write("o. ����(��ȱ)\n");

	seteuid(getuid());
	// Other kinds of fabao can be added too.. if there is somefile
	// we can use as a default object.
	write("��ѡ��(q ��ȡ��)");
	input_to( (: get_type :), me );
	
	return 1;	
}

void get_type(string arg, object ob)
{
	if( arg == "q" || arg == "Q" )
	   return;

	if( (arg != "w" || ob->query("fabao/weapon"))
	  && (arg != "a" || ( ob->query("fabao/armor1")
	  && ob->query("fabao/armor2") )) )   {
		write("��Ҫ�����෨����\n");
		if( !ob->query("fabao/weapon") )
			write("w. ����\n");
		if( !ob->query("fabao/armor1") || !ob->query("fabao/armor2") )
			write("a. ����\n");
	    write("o. ����(��ȱ)\n");
	    write("��ѡ��(q ��ȡ��)");
		input_to( (: get_type :), ob );
		return;
	}

	if( arg == "w" )    {
		ob->set_temp("fabao_type", "weapon");
		write("\n");
		write("��ѡ���������ࣺ\n");
		write("1. ��  2. ��  3. ��  4. ��  5. �  6. ǹ\n");
		write("7. ��  8. ��  9. ��  10. ��\n");
	    write("��ѡ��(q ��ȡ��)");
	}
	else if( arg == "a" )   {
		ob->set_temp("fabao_type", "armor");
		write("\n");
		write("��ѡ��������ࣺ\n");
		write("1. ��  2. Ь  3. �·�  4. ָ��  5. ����  6. ͷ��\n");
		write("7. ����  8. ��  9. ����  10. ����  11. ����\n");
	    write("��ѡ��(q ��ȡ��)");
	}
	input_to( (: get_subtype :), ob);
}

void get_subtype(string arg, object ob)
{
    int  order;
	string fabao_type = ob->query_temp("fabao_type");
   
	if( arg == "q" || arg == "Q" )    return;

    sscanf(arg, "%d", order);
    
	if( (fabao_type == "weapon" && order <= 0 && order > 10) ||
	  (fabao_type == "armor" && order <= 0 && order > 11) )  {
		if( arg == "w" )    {
			fabao_type = "weapon";
			write("\n");
			write("��ѡ���������ࣺ\n");
			write("1. ��  2. ��  3. ��  4. ��  5. �  6. ǹ\n");
			write("7. ��  8. ��  9. ��  10. ��\n");
	        write("��ѡ��(q ��ȡ��)");
		}
		else if( arg == "a" )   {
			fabao_type = "armor";	
			write("\n");
			write("��ѡ��������ࣺ\n");
			write("1. ��  2. Ь  3. �·�  4. ָ��  5. ����  6. ͷ��\n");
			write("7. ����  8. ��  9. ����  10. ����  11. ����\n");
	        write("��ѡ��(q ��ȡ��)");
		}
		ob->set_temp("fabao_type", fabao_type);
		input_to( (: get_subtype :), ob);
		return;
	}
	
	ob->set_temp("fabao_subtype",  order);

	write("\n");
	write("���趨Ӣ�� id ��");
	input_to( (: get_id :), ob ); 
}


int check_legal_id(string id)
{
	int i;
	string	*legalid;
	
	i = strlen(id);
    if( (strlen(id) < 3) || (strlen(id) > 20 ) ) {
		write("�Բ���Ӣ�� id ������ 3 �� 20 ��Ӣ����ĸ��\n");
		return 0;
    }
    while(i--)
    	if( id[i] != ' ' && (id[i]<'a' || id[i]>'z') )  {
    		write("�Բ���Ӣ�� id ֻ����Ӣ����ĸ��\n");
    		return 0;
    	}
    
    legalid = explode(read_file(BANNED_ID), "\n");
    for(i=0; i<sizeof(legalid); i++)   {
    	if( id == legalid[i] )   {
    		write("�Բ������� id ����������˵����š�\n");
    		return 0;
    	}
    }
    
    return 1;
}

int check_legal_name(string name, int max_len)
{
	int i;
	string	*legalname;		//not implemented..may add later
	
	i = strlen(name);
    if( (strlen(name) < 2) || (strlen(name) > max_len ) ) {
    	write( sprintf("�Բ��𣬷��������ֱ����� 1 �� %d �������֡�\n",
    	 max_len/2) );
		return 0;
    }
    while(i--)   {
    	if( name[i]<=' ' )   {
    		write("�Բ��𣬷��������ֲ����ÿ�����Ԫ��\n");
    		return 0;
    	}
    	if( i%2==0 && !is_chinese(name[i..<0]) )  {
    		write("�Բ��������á����ġ�������ȡ���֡�\n");
    		return 0;
    	}
    }
   
    return 1; 
}


void get_id(string arg, object ob)
{
	arg = lower_case(arg);
	if( !check_legal_id(arg) )   {
		write("���趨Ӣ�� id ��");
		input_to( (: get_id :), ob ); 
		return;
	}

	arg = replace_string(arg, " ", "_");	
	ob->set_temp("fabao_id",arg);
	
	write("\n");
	write("���趨��������(�ɼ���ɫ)");
	input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
	string  arg_old;
	
	arg += "$NOR$";
	arg_old = arg;
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");

	if( !check_legal_name(arg, 12) )  {
 	    write("���趨��������(�ɼ���ɫ)");
		input_to( (: get_name :), ob);
		return;
	}

	arg = arg_old;

        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
	
	ob->set_temp("fabao_name", arg + NOR);
	
	write("\n");
	write("������������");
	input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
	if( !check_legal_name(arg, 60) )  {
		write("������������");
		input_to( (: get_desc :), ob);
		return;
	}

	ob->set_temp("fabao_desc",  arg);
	
	write("\n");
	write("���������ʣ�(Return for default)");
	input_to( (: get_unit :), ob);
}


void get_unit(string arg, object ob)
{
	string fabao_unit, fabao_type;

    if( arg == "" )
       fabao_unit = "";
	else if( !check_legal_name(arg, 2) )  {
 	   write("���������ʣ�(Return for defult)");
	   input_to( (: get_unit :), ob);
	   return;
    }
    else
       fabao_unit = arg; 
   
	fabao_type = ob->query_temp("fabao_type");
	ob->set_temp("fabao_unit", fabao_unit);
	if( fabao_type == "weapon" )
		build_weapon(ob);	
	else if( fabao_type == "armor" )
		build_armor(ob);	
	// may have more later
}

void build_weapon(object ob)
{
	object newob;
	string weapon_dir, ob_file;
	string *id_list, *t_list;
	int rev;
	int    fabao_subtype = ob->query_temp("fabao_subtype");
	string fabao_id = ob->query_temp("fabao_id");
	string fabao_name = ob->query_temp("fabao_name");
	string fabao_desc = ob->query_temp("fabao_desc");
	string fabao_unit = ob->query_temp("fabao_unit");
	
	newob = new("/obj/fabao");
	if(!newob)
		return;
		
	seteuid(fabao_id);
	rev = export_uid(newob);
	seteuid(getuid());

	newob->set("value", 1);
	newob->set("no_get", 1);	
	newob->set("no_give", 1);	
	newob->set("no_sell", 1);	
	newob->set("no_drop", 1);	
	newob->set("no_put", 1);	
	
	weapon_dir = "/d/obj/weapon/";
	newob->set("weapon_prop/damage", 10);
	newob->set("flag", TWO_HANDED);
	newob->set("weight", 1000);
	switch( fabao_subtype )   {
		case 1:
			ob_file = weapon_dir + "axe/bigaxe";
			break;
		case 2:
			ob_file = weapon_dir + "blade/blade";
			break;
		case 3:
			ob_file = weapon_dir + "fork/gangcha";
			break;
		case 4:
			ob_file = weapon_dir + "hammer/hammer";
			break;
		case 5:
			ob_file = weapon_dir + "mace/ironmace";
			break;
		case 6:
			ob_file = weapon_dir + "spear/gangqiang";
			break;
		case 7:
			ob_file = weapon_dir + "staff/muzhang";
			break;
		case 8:
			ob_file = weapon_dir + "stick/qimeigun";
			break;
		case 9:
			ob_file = weapon_dir + "sword/changjian";
			break;
		case 10:
			ob_file = weapon_dir + "whip/pibian";
			break;
	}

	newob->set_default_object( ob_file );
	
	newob->set("long", fabao_desc);

	newob->set("fabao/max_attack_qi", 1);
	newob->set("fabao/max_attack_shen", 1);
	
	if( fabao_unit != "" )
	   newob->set("unit", fabao_unit);
	id_list = ({ fabao_id });
	t_list = explode( fabao_id, "_");
	if( sizeof(t_list) > 1 )   {
		id_list += t_list;
	}
	newob->set_name( fabao_name, id_list ); 

	// set owner of fabao
	newob->set("owner_id", getuid(ob));
	newob->set("series_no", "1");
	newob->set("default_file", ob_file);


    newob->save();	

	ob->add("force", -200);
	ob->add("mana", -200);

	ob->set("fabao/weapon",  newob->query("series_no"));
	//make a mark: attack fabao already made

	newob->setup();
	if( !newob->move(ob) )
	   newob->move(environment(ob));
	ob->save();
	
	write("�������Ƴɹ���\n");

	return;
}

void build_armor(object ob)
{
	object	newob;
	string	armor_dir, ob_file;
	string	*id_list, *t_list;
	int		rev;
	string  fabao_id = ob->query_temp("fabao_id");
	string  fabao_name = ob->query_temp("fabao_name");
	string  fabao_desc = ob->query_temp("fabao_desc");
	string  fabao_unit = ob->query_temp("fabao_unit");
	int     fabao_subtype = ob->query_temp("fabao_subtype");

	newob = new("/obj/fabao");
	if(!newob)
		return;
	
	seteuid(fabao_id);
	rev = export_uid(newob);
	seteuid(getuid());

	newob->set("value", 1);
	newob->set("no_get", 1);	
	newob->set("no_sell", 1);	
	newob->set("no_give", 1);	
	newob->set("no_drop", 1);	
	newob->set("no_put", 1);	

	armor_dir = "/d/obj/";
	newob->set("armor_prop/armor", 5);		
	newob->set("armor_prop/dodge", 0);		
	newob->set("armor_prop/spells", 0);
	newob->set("weight", 1000);
	// anything else need to be set?
	
	switch( fabao_subtype )   {
	
	// Add ob_file if you can find the same kind of file
		case 1:
			ob_file = armor_dir + "armor/tenjia";
			break;
		case 2:
			ob_file = armor_dir + "cloth/buxie";
			break;
		case 3:
			ob_file = armor_dir + "cloth/linen";
			break;
		case 4:
			ob_file = armor_dir + "cloth/ring";
			break;
		case 5:
			ob_file = armor_dir + "cloth/gloves";
			break;
		case 6:
			ob_file = armor_dir + "cloth/hat";
			break;
		case 7:
			ob_file = armor_dir + "cloth/necklace";
			break;
		case 8:
			ob_file = armor_dir + "armor/niupi";
			break;
		case 9:
			ob_file = armor_dir + "cloth/surcoat";
			break;
		case 10:
			ob_file = armor_dir + "cloth/wrists";
			break;
		case 11:
			ob_file = armor_dir + "cloth/belt";
			break;
	}
	
	newob->set_default_object( ob_file );
	
	newob->set("long", fabao_desc);

	newob->set("fabao/max_defense_qi", 1);
	newob->set("fabao/max_defense_shen", 1);
	newob->set("fabao/max_defense_shou", 1);

	if( fabao_unit != "" )
	   newob->set("unit", fabao_unit);
	id_list = ({ fabao_id });
	t_list = explode( fabao_id, "_");
	if( sizeof(t_list) > 1 )   {
		id_list += t_list;
	}
	newob->set_name( fabao_name, id_list ); 

	// set owner of fabao
	newob->set("owner_id", getuid(ob));
	if( !ob->query("fabao/armor1") )
		newob->set("series_no", "2");
	else if( !ob->query("fabao/armor2") )
		newob->set("series_no", "3");
	newob->set("default_file", ob_file);

    newob->save();	

	ob->add("force", -200);
	ob->add("mana", -200);
	
	if( !ob->query("fabao/armor1") )
		ob->set("fabao/armor1",  newob->query("series_no"));
	else if( !ob->query("fabao/armor2") )
		ob->set("fabao/armor2",  newob->query("series_no"));
	
	newob->setup();
	if( !newob->move(ob) )
	   newob->move(environment(ob));
	ob->save();

	write("�������Ƴɹ���\n");
	
	return;
}

int  do_dispose(string arg)
{
   object ob = this_player();
   object fabao_ob;
  
   if( !arg || arg == "" )
	  return notify_fail("��Ҫ����ʲô������\n");

   if( !objectp(fabao_ob=present(arg, ob)) )
      return notify_fail("������û��������������\n");
      
   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");
      
   write("��ȷ��Ҫ����÷�����(y/n)");
   input_to( (: confirm_dispose :), ob, fabao_ob); 
   return 1;
}

void confirm_dispose(string arg, object ob, object fabao_ob)
{
   mapping  fabao_list;
   string*  names;
   string fabao_name;
   int      i;

   if( arg == "y" || arg == "Y" )  {
	  fabao_list = ob->query("fabao");
	  if( !mapp(fabao_list) )		return;
	  names = keys(fabao_list);
	  for(i=0; i<sizeof(names); i++)  {
		 if( fabao_list[names[i]] == fabao_ob->query("series_no") )  {
			//seteuid(getuid(ob));
			//rm( fabao_ob->query_save_file() + __SAVE_EXTENSION__ );
			ob->delete("fabao/"+names[i]);
			fabao_name = fabao_ob->query("name");
			destruct( fabao_ob );
			write("ֻ���䣡��һ����"+fabao_name+"ը�˿�����\n");
			break;
		 }
	  }
   }

   return;
}

int  do_list()
{
	write("Ŀǰ���취�������У�\n\n");   
	write("w. �����ࣺ\n");
	write("       ��  ��  ��  ��  �  ǹ\n");
	write("       ��  ��  ��  �ޡ�\n\n");
	write("a. �����ࣺ\n");
	write("       ����  Ь  �·�  ָ��  ����  ͷ��\n");
	write("       ����  ��  ����  ����  ������\n\n");

	write("Ŀǰ�������������ࣺ\n\n");
	write("w. �����ࣺ\n");
	write("       ��Ѫ�˺���(attack_qi)��\n"); //0-25
	write("       �����˺���(attack_shen)��\n\n");//0-25
	write("a. �����ࣺ\n");
	write("       ��Ѫ������(defense_qi)��\n");//0-25
	write("       ���񱣻���(defense_shen)��\n");//0-25
	write("       ��ȡ���˷���(defense_shou)��\n\n");//0-25

	return 1;
}

int do_cost(string arg)
{
	int neili_req, fali_req, dx_req;
	int neili_cost, fali_cost, dx_cost;
	int a_qi, a_shen, d_qi, d_shen, d_shou;

	object fabao_ob, me=this_player();
   
	if( !arg || arg == "" )  
	{
		write("���취�����б����ڶ�ʮ�����ϣ�������Ϊ���������Ƽ�����������Ϊ�����������Ϸ��ɡ�\n");
		write("���������������ǿ���йأ���Ҫ��ĵ��У������������ȡ�\n");		
		return 1;
	}
  
	if( !objectp(fabao_ob=present(arg, me)) )
		return notify_fail("������û��������������\n");
      
	if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
		return notify_fail("�Ǹ����Ƿ���Ү��\n");
      
	a_qi = fabao_ob->query("fabao/max_attack_qi");
	a_shen = fabao_ob->query("fabao/max_attack_shen");
	d_qi = fabao_ob->query("fabao/max_defense_qi");
	d_shen = fabao_ob->query("fabao/max_defense_shen");
	d_shou = fabao_ob->query("fabao/max_defense_shou");

	if( fabao_ob->query("series_no") == "1" )  
	{
		write( fabao_ob->show_status() );
		
		if(a_qi >= 25 )
			write("��Ѫ�˺���������������\n\n");
		else
		{
			dx_req = (a_qi + 1)*100000;
			neili_req =  ( a_qi + 1)*200;
			dx_cost = ( a_qi + 1)*1000;
			neili_cost = (a_qi + 1)*3;
			
			write("������������Ѫ�˺���(attack_qi)������\n");
			write("Ҫ�󣺵���"+chinese_number(dx_req/1000)+"�꣬������Ϊ"+chinese_number(neili_req/100)+"�ꡣ\n");
			write("��ģ�����"+chinese_number(dx_cost/1000)+"�꣬������Ϊ"+chinese_number(neili_cost)+"��(100���൱��һ��)��\n\n");
		}

		if( a_shen >= 25 )
			write("�����˺���������������\n\n");
		else
		{
			dx_req = ( a_shen + 1)*100000;
			fali_req =  ( a_shen + 1)*200;
			dx_cost = (a_shen + 1)*1000;
			fali_cost = ( a_shen + 1)*3;
			
			write("���������������˺���(attack_shen)������\n");
			write("Ҫ�󣺵���"+chinese_number(dx_req/1000)+"�꣬������Ϊ"+RANK_D->describe_fali(fali_req)+"��\n");
			write("��ģ�����"+chinese_number(dx_cost/1000)+"�꣬������Ϊ"+chinese_number(fali_cost)+"�㡣\n\n");
		}
	}

	else
	{//fabao is defense type
		write( fabao_ob->show_status() );
		
		if( d_qi >= 25 )
			write("��Ѫ������������������\n\n");
		else
		{
			dx_req = ( d_qi + 1)*100000;
			neili_req =  ( d_qi + 1)*200;
			dx_cost = ( d_qi + 1)*1000;
			neili_cost = ( d_qi + 1)*3;
			
			write("������������Ѫ������(defense_qi)������\n");
			write("Ҫ�󣺵���"+chinese_number(dx_req/1000)+"�꣬������Ϊ"+chinese_number(neili_req/100)+"�ꡣ\n");
			write("��ģ�����"+chinese_number(dx_cost/1000)+"�꣬������Ϊ"+chinese_number(neili_cost)+"��(100���൱��һ��)��\n\n");
		}

		if( d_shen >= 25 )
			write("���񱣻���������������\n\n");
		else
		{
			dx_req = ( d_shen + 1)*100000;
			fali_req =  ( d_shen + 1)*200;
			dx_cost = ( d_shen + 1)*1000;
			fali_cost = ( d_shen + 1)*3;
			
			write("���������������˺���(defense_shen)������\n");
			write("Ҫ�󣺵���"+chinese_number(dx_req/1000)+"�꣬������Ϊ"+RANK_D->describe_fali(fali_req)+"��\n");
			write("��ģ�����"+chinese_number(dx_cost/1000)+"�꣬������Ϊ"+chinese_number(fali_cost)+"�㡣\n\n");
		}

		if( d_shou >= 25 )
			write("������ȡ��������������\n\n");
		else
		{
			dx_req = ( d_shou + 1)*100000;
			fali_req =  ( d_shou + 1)*200;
			neili_req =  ( d_shou + 1)*200;
			dx_cost = ( d_shou + 1)*1000;
			fali_cost = ( d_shou + 1)*3;
			neili_cost = ( d_shou + 1)*3;
			
			write("����������������ȡ��(defense_shou)������\n");
			write("Ҫ�󣺵���"+chinese_number(dx_req/1000)+"�꣬������Ϊ"+RANK_D->describe_fali(fali_req)+"��������Ϊ"+chinese_number(neili_req/100)+"�ꡣ\n");
			write("��ģ�����"+chinese_number(dx_cost/1000)+"�꣬������Ϊ"+chinese_number(fali_cost)+"�㣬������Ϊ"+chinese_number(neili_cost)+"��(100���൱��һ��)��\n\n");
		}
	}
   
	return 1;
}

int  do_upgrade(string arg)
{
	int neili_req, fali_req, dx_req;
	int neili_cost, fali_cost, dx_cost;
	int a_qi, a_shen, d_qi, d_shen, d_shou;
	int my_dx, my_fali, my_neili;

	string name, property;
	object fabao_ob, me=this_player();
  
	if( !arg || arg == "")   
	{
		write("���� upgrade <������> for <��������> ��������\n");
		write("�������Կ��� cost <������> ���鿴��\n");
		return 1;
	}
      
	if( sscanf(arg, "%s for %s", name, property) != 2)  
	{
		write("���� upgrade <������> for <��������> ��������\n");
		write("�������Կ��� cost <������> ���鿴��\n");
		return 1;
	}
   
	if( !objectp(fabao_ob=present(name, me)) )
		return notify_fail("������û��������������\n");
      
	if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
		return notify_fail("�Ǹ����Ƿ���Ү��\n");
     
	if( fabao_ob->query("equipped") )
		return notify_fail("�������·�������������\n");

	a_qi = fabao_ob->query("fabao/max_attack_qi");
	a_shen = fabao_ob->query("fabao/max_attack_shen");
	d_qi = fabao_ob->query("fabao/max_defense_qi");
	d_shen = fabao_ob->query("fabao/max_defense_shen");
	d_shou = fabao_ob->query("fabao/max_defense_shou");
          
	my_dx = me->query("daoxing");
	my_fali = me->query("max_mana");
	my_neili = me->query("max_force");

	if( fabao_ob->query("series_no") == "1")  
	{// weapon
		if( property == "attack_qi" )
		{
			if(a_qi >= 25 )
				return notify_fail("�����������Ѫ�˺���������������\n");

			dx_req = (a_qi + 1)*100000;
			neili_req =  ( a_qi + 1)*200;
			dx_cost = ( a_qi + 1)*1000;
			neili_cost = (a_qi + 1)*3;
			
			if( my_dx < dx_req )
				return notify_fail("����ĵ��У�Ŀǰ���������������������Ѫ�˺�����\n");
			if( my_neili < neili_req )
				return notify_fail("�����������Ϊ��Ŀǰ���������������������Ѫ�˺�����\n");
			//now, let's upgrade...
			me->add("daoxing", -dx_cost);
			//me->add("max_force", -neili_cost);
			me->add_maximum_force(-neili_cost);
			fabao_ob->set("fabao/max_attack_qi", a_qi+1);
			fabao_ob->add("weapon_prop/damage", 3);//will be 75+10 in max.
			me->save();
			fabao_ob->save();
			message_vision(HIR "$N����������ע��$n�У�ֻ��$n�ų����ϼ�⣬������ֹ��\n" NOR, me, fabao_ob);
			return 1;
		}

		else if( property == "attack_shen" )
		{
			if(a_shen >= 25 )
				return notify_fail("��������ľ����˺���������������\n");

			dx_req = (a_shen + 1)*100000;
			fali_req =  ( a_shen + 1)*200;
			dx_cost = ( a_shen + 1)*1000;
			fali_cost = (a_shen + 1)*3;
			
			if( my_dx < dx_req )
				return notify_fail("����ĵ��У�Ŀǰ������������������ľ����˺�����\n");
			if( my_fali < fali_req )
				return notify_fail("����ķ�����Ϊ��Ŀǰ������������������ľ����˺�����\n");
			//now, let's upgrade...
			me->add("daoxing", -dx_cost);
			//me->add("max_mana", -fali_cost);
			me->add_maximum_mana(-fali_cost);
			fabao_ob->set("fabao/max_attack_shen", a_shen+1);
			me->save();
			fabao_ob->save();
			message_vision(HIR "$N����������ע��$n�У�ֻ��$n�ų����ϼ�⣬������ֹ��\n" NOR, me, fabao_ob);
			return 1;
		}

		else 
		{
			return notify_fail("�������û������������ԣ����� cost <������> ���鿴��\n");
		}
	}
	
	else //armor
	{
		if( property == "defense_qi" )
		{
			if(d_qi >= 25 )
				return notify_fail("�����������Ѫ������������������\n");

			dx_req = (d_qi + 1)*100000;
			neili_req =  ( d_qi + 1)*200;
			dx_cost = ( d_qi + 1)*1000;
			neili_cost = (d_qi + 1)*3;
			
			if( my_dx < dx_req )
				return notify_fail("����ĵ��У�Ŀǰ���������������������Ѫ��������\n");
			if( my_neili < neili_req )
				return notify_fail("�����������Ϊ��Ŀǰ���������������������Ѫ��������\n");
			//now, let's upgrade...
			me->add("daoxing", -dx_cost);
			//me->add("max_force", -neili_cost);
			me->add_maximum_force(-neili_cost);
			fabao_ob->set("fabao/max_defense_qi", d_qi+1);
			me->save();
			fabao_ob->save();
			message_vision(HIR "$N����������ע��$n�У�ֻ��$n�ų����ϼ�⣬������ֹ��\n" NOR, me, fabao_ob);
			return 1;
		}

		else if( property == "defense_shen" )
		{
			if(d_shen >= 25 )
				return notify_fail("��������ľ��񱣻���������������\n");

			dx_req = (d_shen + 1)*100000;
			fali_req =  ( d_shen + 1)*200;
			dx_cost = ( d_shen + 1)*1000;
			fali_cost = (d_shen + 1)*3;
			
			if( my_dx < dx_req )
				return notify_fail("����ĵ��У�Ŀǰ������������������ľ��񱣻�����\n");
			if( my_fali < fali_req )
				return notify_fail("����ķ�����Ϊ��Ŀǰ������������������ľ��񱣻�����\n");
			//now, let's upgrade...
			me->add("daoxing", -dx_cost);
			//me->add("max_mana", -fali_cost);
			me->add_maximum_mana(-fali_cost);
			fabao_ob->set("fabao/max_defense_shen", d_shen+1);
			me->save();
			fabao_ob->save();
			message_vision(HIR "$N����������ע��$n�У�ֻ��$n�ų����ϼ�⣬������ֹ��\n" NOR, me, fabao_ob);
			return 1;
		}

		else if( property == "defense_shou" )
		{
			if(d_shou >= 25 )
				return notify_fail("��������ķ�����ȡ��������������\n");

			dx_req = (d_shou + 1)*100000;
			fali_req =  ( d_shou + 1)*200;
			dx_cost = ( d_shou + 1)*1000;
			fali_cost = (d_shou + 1)*3;
			
			if( my_dx < dx_req )
				return notify_fail("����ĵ��У�Ŀǰ������������������ķ�����ȡ����\n");
			if( my_fali < fali_req )
				return notify_fail("����ķ�����Ϊ��Ŀǰ������������������ķ�����ȡ����\n");
			//now, let's upgrade...
			me->add("daoxing", -dx_cost);
			//me->add("max_mana", -fali_cost);
			me->add_maximum_mana(-fali_cost);
			fabao_ob->set("fabao/max_defense_shou", d_shou+1);
			me->save();
			fabao_ob->save();
			message_vision(HIR "$N����������ע��$n�У�ֻ��$n�ų����ϼ�⣬������ֹ��\n" NOR, me, fabao_ob);
			return 1;
		}

		else 
		{
			return notify_fail("�������û������������ԣ����� cost <������> ���鿴��\n");
		}
	}      
}

int  do_change_name(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_name <����> <��������> ��������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_name <����> <��������> ��������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");
   
   newname += "$NOR$";      
   arg = newname;
            
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");
        
   if( !check_legal_name(arg, 12) )   {
      return 1; 
   }
  
   arg = newname;
    
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
  
   fabao_ob->set("name", arg);
   fabao_ob->save();     
   
   write("�Ķ��ɹ���\n");
   return 1;
}
      
int  do_change_id(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
   string *id_list, *t_list;
  
   if( !arg || arg == "") 
      return notify_fail("���� change_id <����> <��Ӣ����> ��������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_id <����> <��Ӣ����> ��������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_id( newname ) )		return 1;
  
   newname = replace_string(newname, " ", "_"); 
   fabao_ob->set("id", newname);

   id_list = ({ newname });
   t_list = explode( newname, "_");
   if( sizeof(t_list) > 1 )   {
	  id_list += t_list;
   }
   fabao_ob->set_name( fabao_ob->query("name"), id_list ); 
   fabao_ob->save();
	
   write("�Ķ��ɹ���\n");
   return 1;
}

      
int  do_change_desc(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_desc <����> <������> ����������������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_desc <����> <������> ����������������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_name(newname, 60 ) )		return 1;
   
   fabao_ob->set("long", newname);
   fabao_ob->save();
   
   write("�Ķ��ɹ���\n");
   return 1;
}
      
int  do_change_unit(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_unit <����> <��λ> ��ָ��������λ��\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_unit <����> <��λ> ��ָ��������λ��\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_name(newname, 2 ) )		return 1;
   
   fabao_ob->set("unit", newname);
   fabao_ob->save();
   
   write("�Ķ��ɹ���\n");
   return 1;
}