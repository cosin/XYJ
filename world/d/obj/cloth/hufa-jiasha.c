// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"护法袈裟"NOR, ({ "jia sha", "cloth" }) );
        set("long","一件金光灿灿的护法袈裟。");
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 2000);
                set("material", "cloth");
                set("armor_prop/armor", 20);
        }
        setup();
}

