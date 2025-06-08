#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/wob_mod.h>
#include <ninecraft/patch/patch_address.h>

/*
    This mod makes the options button wide in
    the main menu.
*/

void wob_mod_inject(int version_id) {
    if (!start_menu_screen_construct) {
        return;
    }
    if (version_id == version_id_0_6_1 || version_id == version_id_0_6_0) {
#if defined(__i386__) || defined(_M_IX86)
        patch_address((char *)start_menu_screen_construct + 268, "\xa0", 1, PATCH_ADDRESS_PROT_XR);
#endif
#if defined(__arm__) || defined(_M_ARM)
        patch_address((char *)start_menu_screen_construct + 129, "\xa0", 1, PATCH_ADDRESS_PROT_XR);
#endif
    } else if (version_id == version_id_0_5_0) {
#if defined(__i386__) || defined(_M_IX86)
        patch_address((char *)start_menu_screen_construct + 316, "\xa0", 1, PATCH_ADDRESS_PROT_XR);
#endif
#if defined(__arm__) || defined(_M_ARM)
        patch_address((char *)start_menu_screen_construct + 177, "\xa0", 1, PATCH_ADDRESS_PROT_XR);
#endif
    }
}