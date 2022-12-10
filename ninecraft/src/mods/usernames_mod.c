#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/usernames_mod.h>

/*
    This mod enables usernames rendering
    in multiplayer games.
*/

void usernames_mod_inject(int version_id) { 
    if (version_id == version_id_0_6) {
#ifdef __i386__
        *(short *)(player_renderer_render_name + 50) = 0x9090;
#endif
    } else if (version_id == version_id_0_5) {
#ifdef __i386__
        *(short *)(player_renderer_render_name + 50) = 0x9090;
#endif
    }
}