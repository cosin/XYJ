// cracked by vikee 2/09/2002   vikee@263.net
// 取经人-长安模块

#include "/d/qujing/qujingren/qujingren.c"


void me_init()
  {
    set("redef_accept_obj",1);
  }

int accept_object1(object who,object ob)
{
        if (who->query("id")=="tang taizong")return 1;
        return notify_fail("");
}

