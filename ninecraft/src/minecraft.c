#include <hybris/dlfcn.h>
#include <ninecraft/minecraft.h>
#include <stddef.h>

minecraft_level_generated_t minecraft_level_generated = NULL;
minecraft_tick_t minecraft_tick = NULL;
command_server_deconstruct_t command_server_deconstruct = NULL;
command_server_construct_t command_server_construct = NULL;
command_server_init_t command_server_init = NULL;
start_menu_screen_construct_t start_menu_screen_construct = NULL;
player_renderer_render_name_t player_renderer_render_name = NULL;
textures_load_and_bind_texture_t textures_load_and_bind_texture = NULL;
gui_component_blit_t gui_component_blit = NULL;
screen_render_dirt_background_t screen_render_dirt_background = NULL;

void minecraft_setup_hooks(void *handle) {
    minecraft_level_generated = (minecraft_level_generated_t)hybris_dlsym(handle, "_ZN9Minecraft15_levelGeneratedEv");
    minecraft_tick = (minecraft_tick_t)hybris_dlsym(handle, "_ZN9Minecraft4tickEii");
    command_server_deconstruct = (command_server_deconstruct_t)hybris_dlsym(handle, "_ZN13CommandServerD2Ev");
    command_server_construct = (command_server_construct_t)hybris_dlsym(handle, "_ZN13CommandServerC2EP9Minecraft");
    command_server_init = (command_server_init_t)hybris_dlsym(handle, "_ZN13CommandServer4initEs");
    start_menu_screen_construct = (start_menu_screen_construct_t)hybris_dlsym(handle, "_ZN15StartMenuScreenC1Ev");
    player_renderer_render_name = (player_renderer_render_name_t)hybris_dlsym(handle, "_ZN14PlayerRenderer10renderNameEP3Mobfff");
    textures_load_and_bind_texture = (textures_load_and_bind_texture_t)hybris_dlsym(handle, "_ZN8Textures18loadAndBindTextureERKSs");
    gui_component_blit = (gui_component_blit_t)hybris_dlsym(handle, "_ZN12GuiComponent4blitEiiiiiiii");
    screen_render_dirt_background = (screen_render_dirt_background_t)hybris_dlsym(handle, "_ZN6Screen20renderDirtBackgroundEi");
}