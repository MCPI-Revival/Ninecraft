#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/usernames_mod.h>
#include <ninecraft/patch/patch_address.h>

/*
    This mod enables usernames rendering
    in multiplayer games.
*/

void usernames_mod_inject(int version_id) {
    if (!player_renderer_render_name) {
        return;
    }
    if (version_id == version_id_0_6_1 || version_id == version_id_0_6_0) {
#if defined(__i386__) || defined(_M_IX86)
        patch_address((char *)player_renderer_render_name + 50, "\x90\x90", 2, PATCH_ADDRESS_PROT_XR);
#endif
#if defined(__arm__) || defined(_M_ARM)
        patch_address((char *)player_renderer_render_name + 23, "\x00\xbf", 2, PATCH_ADDRESS_PROT_XR);
#endif
    } else if (version_id == version_id_0_5_0) {
#if defined(__i386__) || defined(_M_IX86)
        patch_address((char *)player_renderer_render_name + 50, "\x90\x90", 2, PATCH_ADDRESS_PROT_XR);
#endif
#if defined(__arm__) || defined(_M_ARM) 
        patch_address((char *)player_renderer_render_name + 23, "\x00\xbf", 2, PATCH_ADDRESS_PROT_XR);
#endif
    }
}