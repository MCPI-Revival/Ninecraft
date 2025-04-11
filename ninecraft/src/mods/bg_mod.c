#include <ninecraft/mods/bg_mod.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/patch/detours.h>
#include <ninecraft/version_ids.h>

/*
    This mod allows you to use images as full backgrounds,
    instead of the default tiled texture.
*/

void bg_mod_screen_render_dirt_background_injection(void *screen, uint32_t param_1) {
    void *minecraft = *(void **)((char *)screen + 20);
    void *textures = *(void **)((char *)minecraft + 688);
    android_string_t str;
    android_string_cstr(&str, "gui/bg32.png");
    textures_load_and_bind_texture(textures, &str);
    gui_component_blit(screen, 0, 0, 0, 0, *(int *)((char *)screen + 8), *(int *)((char *)screen + 12), 0x100, 0x100);
    android_string_destroy(&str);
}


void bg_mod_inject(int version_id) {
    if (version_id == version_id_0_6_1 || version_id == version_id_0_6_0 || version_id == version_id_0_5_0) { 
        DETOUR(screen_render_dirt_background, bg_mod_screen_render_dirt_background_injection, true);
    }
}