#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/patch/detours.h>
#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/mods/mouse_input_mod.h>
#include <ninecraft/ninecraft_defs.h>

/*
    This mod makes mouse control work more reliably.
*/

typedef short (*mouse_get_dx_t)();
static mouse_get_dx_t mouse_get_dx;
static mouse_get_dx_t mouse_get_dy;

struct turn_delta {
    float x;
    float y;
};
NINECRAFT_FLOAT_FUNC struct turn_delta controller_turn_input_get_turn_delta(void *turn_input) {
    struct turn_delta ret;
    ret.x = mouse_get_dx() * 0.3;
    ret.y = mouse_get_dy() * 0.3;
    return ret;
}

void mouse_input_mod_inject(void *handle, int version_id) {
    if (version_id >= version_id_0_6_0) {
        mouse_get_dx = (mouse_get_dx_t)internal_dlsym(handle, "_ZN5Mouse5getDXEv");
        mouse_get_dy = (mouse_get_dx_t)internal_dlsym(handle, "_ZN5Mouse5getDYEv");
        DETOUR((void *)internal_dlsym(handle, "_ZN19ControllerTurnInput12getTurnDeltaEv"), controller_turn_input_get_turn_delta, true);
    }
}
