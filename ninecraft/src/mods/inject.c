#include <ninecraft/mods/piapi_mod.h>
#include <ninecraft/mods/bg_mod.h>
#include <ninecraft/mods/usernames_mod.h>
#include <ninecraft/mods/wob_mod.h>
#include <ninecraft/mods/mouse_input_mod.h>

void inject_mods(void *handle, int version_id) {
    piapi_mod_inject(version_id);
    bg_mod_inject(version_id);
    usernames_mod_inject(version_id);
    wob_mod_inject(version_id);
    mouse_input_mod_inject(handle, version_id);
}
