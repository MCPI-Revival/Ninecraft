#include <ninecraft/mods/piapi_mod.h>
#include <ninecraft/mods/bg_mod.h>
#include <ninecraft/mods/usernames_mod.h>
#include <ninecraft/mods/wob_mod.h>

void inject_mods(int version_id) {
    piapi_mod_inject(version_id);
    bg_mod_inject(version_id);
    usernames_mod_inject(version_id);
    wob_mod_inject(version_id);
}