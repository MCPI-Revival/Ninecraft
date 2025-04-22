#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/mouse_input_mod.h>
#include <ancmp/android_dlfcn.h>
#include <ancmp/abi_fix.h>

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

void controller_turn_input_get_turn_delta(struct turn_delta *ret, void *turn_input) {
    struct turn_delta delta;
    delta.x = mouse_get_dx() * 0.3;
    delta.y = mouse_get_dy() * 0.3;
    *ret = delta;
}
SYSV_WRAPPER(controller_turn_input_get_turn_delta, 2)

void mouse_input_mod_inject(void *handle, int version_id) {
    if (version_id >= version_id_0_6_0) {
        mouse_get_dx = (mouse_get_dx_t)android_dlsym(handle, "_ZN5Mouse5getDXEv");
        mouse_get_dy = (mouse_get_dx_t)android_dlsym(handle, "_ZN5Mouse5getDYEv");
        ((void **)android_dlsym(handle, "_ZTV19ControllerTurnInput"))[5] = GET_SYSV_WRAPPER(controller_turn_input_get_turn_delta);
    }
}
