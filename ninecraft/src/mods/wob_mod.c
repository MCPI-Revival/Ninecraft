#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/wob_mod.h>

/*
    This mod makes the options button wide in
    the main menu.
*/

void wob_mod_inject(int version_id) { 
    if (version_id == version_id_0_6_1 || version_id == version_id_0_6_0) {
#if defined(__i386__) || defined(_M_IX86)
        ((char *)start_menu_screen_construct)[268] = 0xa0;
#endif
#if defined(__arm__) || defined(_M_ARM) 
        ((char *)start_menu_screen_construct)[129] = 0xa0;
#endif
    } else if (version_id == version_id_0_5_0) {
#if defined(__i386__) || defined(_M_IX86)
        ((char *)start_menu_screen_construct)[316] = 0xa0;
#endif
#if defined(__arm__) || defined(_M_ARM) 
        ((char *)start_menu_screen_construct)[177] = 0xa0;
#endif
    }
}