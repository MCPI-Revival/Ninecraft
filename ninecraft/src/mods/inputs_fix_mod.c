#include <ninecraft/mods/inputs_fix_mod.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ninecraft/input/minecraft_keys.h>
#include <ninecraft/version_ids.h>
#include <ancmp/android_dlfcn.h>

/*
    This mod fixes input related issues
    for mcpe 0.5.0-0.10.5
*/

static void *_handle = NULL;

typedef struct {
    void **vtable;
    float h_pos;
    float v_pos;
    bool unknown0;
    bool is_jumping;
    bool is_sneaking;
    bool is_flying_up;
    bool is_flying_down;
    bool unknown5;
    bool forward_pressed;
    bool back_pressed;
    bool left_pressed;
    bool right_pressed;
    bool jump_pressed;
    bool sneak_pressed;
    bool crafting_pressed;
    bool unknown13;
    bool unknown14;
    bool unknown15;
    void *options;
} keyboard_input_t;

void xperia_play_input_tick(keyboard_input_t *__this, void *player) {
    ((void (*)(keyboard_input_t *, void *))android_dlsym(_handle, "_ZN13KeyboardInput4tickEP6Player"))(__this, player);
    if (__this->jump_pressed) {
        __this->is_flying_up = true;
    } else {
        __this->is_flying_up = false;
    }
    if (__this->sneak_pressed) {
        __this->is_flying_down = true;
    } else {
        __this->is_flying_down = false;
    }
}

void inputs_fix_mod_inject(void *handle, int version_id) {
    _handle = handle;
    if (version_id >= version_id_0_5_0 && version_id <= version_id_0_8_1) {
        ((void **)android_dlsym(handle, "_ZTV15XperiaPlayInput"))[4] = xperia_play_input_tick;
    } else if (version_id >= version_id_0_9_0 && version_id <= version_id_0_10_5) {
        ((void **)android_dlsym(handle, "_ZTV19ControllerMoveInput"))[4] = xperia_play_input_tick;
    }
}