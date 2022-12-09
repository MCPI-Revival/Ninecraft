#include <ninecraft/version_ids.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/patch/detours.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/misc_mod.h>

void misc_mod_screen_render_dirt_background_injection(void *screen, uint32_t param_1) {
    void *minecraft = *(void **)(screen + 20);
    void *textures = *(void **)(minecraft + 688);
    android_string_t str;
    android_string_cstr(&str, "gui/bg32.png");
    textures_load_and_bind_texture(textures, &str);
    gui_component_blit(screen, 0, 0, 0, 0, *(int *)(screen +8 ), *(int *)(screen + 12), 0x100, 0x100);
}

void misc_mod_inject(int version_id) {
#ifdef __i386__
    // Custom menu background
    DETOUR(screen_render_dirt_background, misc_mod_screen_render_dirt_background_injection, true);
#endif
    
    if (version_id == version_id_0_6) {
#ifdef __i386__
        // Wide options button
        ((char *)start_menu_screen_construct)[268] = 0xa0;

        // Render usernames
        *(short *)(player_renderer_render_name + 50) = 0x9090;
#endif
#ifdef __thumb2__
        // Wide options button
        ((char *)start_menu_screen_construct)[129] = 0xa0;
#endif
    } else if (version_id == version_id_0_5) {
#ifdef __i386__
        // Wide options button
        ((char *)start_menu_screen_construct)[316] = 0xa0;
        
        // Render usernames
        *(short *)(player_renderer_render_name + 50) = 0x9090;
#endif
#ifdef __thumb2__
        // Wide options button
        ((char *)start_menu_screen_construct)[177] = 0xa0;
#endif
    }
}