// cracked by vikee 2/09/2002   vikee@263.net
// magua.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("����", ({ "magua"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("value", 500);
                set("material", "cloth");
                set("armor_prop/armor", 5);
        }
        setup();
}
