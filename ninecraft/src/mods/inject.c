#include <ninecraft/mods/inject.h>
#include <ninecraft/mods/usernames_mod.h>
#include <ninecraft/mods/wob_mod.h>
#include <ninecraft/mods/mouse_input_mod.h>
#include <ninecraft/mods/chat_mod.h>
#include <ninecraft/mods/header_buttons_fix_mod.h>
#include <ninecraft/mods/inputs_fix_mod.h>

void inject_mods(void *handle, int version_id) {
    usernames_mod_inject(version_id);
    wob_mod_inject(version_id);
    mouse_input_mod_inject(handle, version_id);
    chat_mod_inject(handle);
    header_buttons_fix_mod_inject(handle, version_id);
    inputs_fix_mod_inject(handle, version_id);
}
