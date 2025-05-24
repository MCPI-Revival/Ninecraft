#include <ninecraft/minecraft.h>
#include <ancmp/android_dlfcn.h>
#include <stddef.h>
#include <ninecraft/version_ids.h>

minecraft_level_generated_t minecraft_level_generated = NULL;
minecraft_tick_t minecraft_tick = NULL;
minecraft_is_level_generated_t minecraft_is_level_generated = NULL;
command_server_deconstruct_t command_server_deconstruct = NULL;
command_server_construct_t command_server_construct = NULL;
command_server_init_t command_server_init = NULL;
start_menu_screen_construct_t start_menu_screen_construct = NULL;
player_renderer_render_name_t player_renderer_render_name = NULL;
textures_load_and_bind_texture_t textures_load_and_bind_texture = NULL;
gui_component_blit_t gui_component_blit = NULL;
screen_render_dirt_background_t screen_render_dirt_background = NULL;
ninecraft_app_construct_t ninecraft_app_construct = NULL;
ninecraft_app_construct_2_t ninecraft_app_construct_2 = NULL;
ninecraft_app_init_t ninecraft_app_init = NULL;
app_init_t app_init = NULL;
minecraft_set_size_t minecraft_set_size = NULL;
ninecraft_app_update_t ninecraft_app_update = NULL;
ninecraft_app_handle_back_t ninecraft_app_handle_back = NULL;
minecraft_client_set_size_t minecraft_client_set_size = NULL;
minecraft_client_handle_back_t minecraft_client_handle_back = NULL;
minecraft_update_t minecraft_update = NULL;
minecraft_client_construct_t minecraft_client_construct = NULL;
minecraft_client_init_t minecraft_client_init = NULL;
app_platform_construct_t app_platform_construct = NULL;
screen_construct_t screen_construct = NULL;
minecraft_set_screen_t minecraft_set_screen = NULL;
raknet_instance_send_packet_t raknet_instance_send_packet = NULL;
raknet_rakstring_assign_t raknet_rakstring_assign = NULL;
minecraft_packets_create_packet_t minecraft_packets_create_packet = NULL;
server_side_network_handler_get_player_t server_side_network_handler_get_player = NULL;
server_side_network_handler_redistribute_packet_t server_side_network_handler_redistribute_packet = NULL;
chat_packet_deconstruct_t chat_packet_deconstruct = NULL;
message_packet_deconstruct_t message_packet_deconstruct = NULL;
raknet_instance_is_server_t raknet_instance_is_server = NULL;
gui_add_message_t gui_add_message = NULL;
options_set_key_t options_set_key = NULL;
minecraft_client_get_options_t minecraft_client_get_options = NULL;
minecraft_client_get_local_player_t minecraft_client_get_local_player = NULL;
gui_component_fill_t gui_component_fill = NULL;

void gui_component_draw_rect(void *gui_component, int x1, int y1, int x2, int y2, int color, int thickness) {
    if (gui_component_fill) {
        gui_component_fill(gui_component, x1, y1, x2, y1 + thickness, color);
        gui_component_fill(gui_component, x1, y2 - thickness, x2, y2, color);
        gui_component_fill(gui_component, x1, y1, x1 + thickness, y2, color);
        gui_component_fill(gui_component, x2 - thickness, y1, x2, y2, color);
    }
}

void *minecraft_get_options(void *minecraft, int version_id) {
    char *mc_options = NULL;
    if (version_id == version_id_0_5_0) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_5_0;
    } else if (version_id == version_id_0_5_0_j) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_5_0_J;
    } else if (version_id == version_id_0_6_0) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_6_1;
    } else if (version_id == version_id_0_7_0) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_0;
    } else if (version_id == version_id_0_7_1) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_1;
    } else if (version_id == version_id_0_7_2) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_2;
    } else if (version_id == version_id_0_7_3) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_3;
    } else if (version_id == version_id_0_7_4) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_4;
    } else if (version_id == version_id_0_7_5) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_5;
    } else if (version_id == version_id_0_7_6) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_7_6;
    } else if (version_id == version_id_0_8_0) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_8_0;
    } else if (version_id == version_id_0_8_1) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_8_1;
    } else if (version_id == version_id_0_9_0) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_0;
    } else if (version_id == version_id_0_9_1) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_1;
    } else if (version_id == version_id_0_9_2) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_2;
    } else if (version_id == version_id_0_9_3) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_3;
    } else if (version_id == version_id_0_9_4) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_4;
    } else if (version_id == version_id_0_9_5) {
        mc_options = (char *)minecraft + MINECRAFT_OPTIONS_OFFSET_0_9_5;
    } else if (version_id >= version_id_0_10_0 && version_id <= version_id_0_11_1) {
        mc_options = (char *)minecraft_client_get_options(minecraft);
    }
    return (void *)mc_options;
}

uintptr_t get_ninecraftapp_external_storage_offset(int version_id) {
    if (version_id == version_id_0_1_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_0;
    }
    if (version_id == version_id_0_1_0_touch) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_0_TOUCH;
    }
    if (version_id == version_id_0_1_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_1;
    }
    if (version_id == version_id_0_1_1_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_1_J;
    }
    if (version_id == version_id_0_1_2) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_2;
    }
    if (version_id == version_id_0_1_2_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_2_J;
    }
    if (version_id == version_id_0_1_3) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_3;
    }
    if (version_id == version_id_0_1_3_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_1_3_J;
    }
    if (version_id == version_id_0_2_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_0;
    }
    if (version_id == version_id_0_2_0_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_0_J;
    }
    if (version_id == version_id_0_2_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_1;
    }
    if (version_id == version_id_0_2_1_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_1_J;
    }
    if (version_id == version_id_0_2_2) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_2_2;
    }
    if (version_id == version_id_0_3_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_0;
    }
    if (version_id == version_id_0_3_0_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_0_J;
    }
    if (version_id == version_id_0_3_2) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_2;
    }
    if (version_id == version_id_0_3_2_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_2_J;
    }
    if (version_id == version_id_0_3_3) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_3;
    }
    if (version_id == version_id_0_3_3_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_3_3_J;
    }
    if (version_id == version_id_0_4_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_4_0;
    }
    if (version_id == version_id_0_4_0_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_4_0_J;
    }
    if (version_id == version_id_0_5_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_5_0;
    }
    if (version_id == version_id_0_5_0_j) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_5_0_J;
    }
    if (version_id == version_id_0_6_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_6_0;
    }
    if (version_id == version_id_0_6_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_6_1;
    }
    if (version_id == version_id_0_7_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_0;
    }
    if (version_id == version_id_0_7_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_1;
    }
    if (version_id == version_id_0_7_2) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_2;
    }
    if (version_id == version_id_0_7_3) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_3;
    }
    if (version_id == version_id_0_7_4) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_4;
    }
    if (version_id == version_id_0_7_5) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_5;
    }
    if (version_id == version_id_0_7_6) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_7_6;
    }
    if (version_id == version_id_0_8_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_0;
    }
    if (version_id == version_id_0_8_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_8_1;
    }
    if (version_id == version_id_0_9_0) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_0;
    }
    if (version_id == version_id_0_9_1) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_1;
    }
    if (version_id == version_id_0_9_2) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_3;
    }
    if (version_id == version_id_0_9_3) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_3;
    }
    if (version_id == version_id_0_9_4) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_4;
    }
    if (version_id == version_id_0_9_5) {
        return NINECRAFTAPP_EXTERNAL_STORAGE_OFFSET_0_9_5;
    }
    if (version_id == version_id_0_10_0) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_0;
    }
    if (version_id == version_id_0_10_1) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_1;
    }
    if (version_id == version_id_0_10_2) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_2;
    }
    if (version_id == version_id_0_10_3) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_3;
    }
    if (version_id == version_id_0_10_4) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_4;
    }
    if (version_id == version_id_0_10_5) {
        return MINECRAFTCLIENT_EXTERNAL_STORAGE_OFFSET_0_10_5;
    }
    return 0;
}

uintptr_t get_ninecraftapp_internal_storage_offset(int version_id) {
    if (version_id == version_id_0_3_3) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_3_3;
    }
    if (version_id == version_id_0_3_3_j) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_3_3_J;
    }
    if (version_id == version_id_0_4_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_4_0;
    }
    if (version_id == version_id_0_4_0_j) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_4_0_J;
    }
    if (version_id == version_id_0_5_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_5_0;
    }
    if (version_id == version_id_0_5_0_j) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_5_0_J;
    }
    if (version_id == version_id_0_6_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_6_0;
    }
    if (version_id == version_id_0_6_1) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_6_1;
    }
    if (version_id == version_id_0_7_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_0;
    }
    if (version_id == version_id_0_7_1) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_1;
    }
    if (version_id == version_id_0_7_2) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_2;
    }
    if (version_id == version_id_0_7_3) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_3;
    }
    if (version_id == version_id_0_7_4) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_4;
    }
    if (version_id == version_id_0_7_5) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_5;
    }
    if (version_id == version_id_0_7_6) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_7_6;
    }
    if (version_id == version_id_0_8_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_0;
    }
    if (version_id == version_id_0_8_1) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_8_1;
    }
    if (version_id == version_id_0_9_0) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_0;
    }
    if (version_id == version_id_0_9_1) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_1;
    }
    if (version_id == version_id_0_9_2) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_3;
    }
    if (version_id == version_id_0_9_3) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_3;
    }
    if (version_id == version_id_0_9_4) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_4;
    }
    if (version_id == version_id_0_9_5) {
        return NINECRAFTAPP_INTERNAL_STORAGE_OFFSET_0_9_5;
    }
    if (version_id == version_id_0_10_0) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_0;
    }
    if (version_id == version_id_0_10_1) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_1;
    }
    if (version_id == version_id_0_10_2) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_2;
    }
    if (version_id == version_id_0_10_3) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_3;
    }
    if (version_id == version_id_0_10_4) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_4;
    }
    if (version_id == version_id_0_10_5) {
        return MINECRAFTCLIENT_INTERNAL_STORAGE_OFFSET_0_10_5;
    }
    return 0;
}

void minecraft_setup_hooks(void *handle) {
    minecraft_level_generated = (minecraft_level_generated_t)android_dlsym(handle, "_ZN9Minecraft15_levelGeneratedEv");
    minecraft_tick = (minecraft_tick_t)android_dlsym(handle, "_ZN9Minecraft4tickEii");
    minecraft_is_level_generated = (minecraft_is_level_generated_t)android_dlsym(handle, "_ZN9Minecraft16isLevelGeneratedEv");
    command_server_deconstruct = (command_server_deconstruct_t)android_dlsym(handle, "_ZN13CommandServerD2Ev");
    command_server_construct = (command_server_construct_t)android_dlsym(handle, "_ZN13CommandServerC2EP9Minecraft");
    command_server_init = (command_server_init_t)android_dlsym(handle, "_ZN13CommandServer4initEs");
    start_menu_screen_construct = (start_menu_screen_construct_t)android_dlsym(handle, "_ZN15StartMenuScreenC1Ev");
    player_renderer_render_name = (player_renderer_render_name_t)android_dlsym(handle, "_ZN14PlayerRenderer10renderNameEP3Mobfff");
    textures_load_and_bind_texture = (textures_load_and_bind_texture_t)android_dlsym(handle, "_ZN8Textures18loadAndBindTextureERKSs");
    gui_component_blit = (gui_component_blit_t)android_dlsym(handle, "_ZN12GuiComponent4blitEiiiiiiii");
    screen_render_dirt_background = (screen_render_dirt_background_t)android_dlsym(handle, "_ZN6Screen20renderDirtBackgroundEi");
    ninecraft_app_construct = (ninecraft_app_construct_t)android_dlsym(handle, "_ZN12NinecraftAppC2Ev");
    ninecraft_app_construct_2 = (ninecraft_app_construct_2_t)android_dlsym(handle, "_ZN12NinecraftAppC2EiPPc");
    ninecraft_app_init = (ninecraft_app_init_t)android_dlsym(handle, "_ZN12NinecraftApp4initEv");
    app_init = (app_init_t)android_dlsym(handle, "_ZN3App4initER10AppContext");
    minecraft_set_size = (minecraft_set_size_t)android_dlsym(handle, "_ZN9Minecraft7setSizeEii");
    ninecraft_app_update = (ninecraft_app_update_t)android_dlsym(handle, "_ZN12NinecraftApp6updateEv");
    ninecraft_app_handle_back = (ninecraft_app_handle_back_t)android_dlsym(handle, "_ZN12NinecraftApp10handleBackEb");
    minecraft_client_set_size = (minecraft_client_set_size_t)android_dlsym(handle, "_ZN15MinecraftClient7setSizeEiif");
    minecraft_client_handle_back = (minecraft_client_handle_back_t)android_dlsym(handle, "_ZN15MinecraftClient10handleBackEb");
    minecraft_update = (minecraft_update_t)android_dlsym(handle, "_ZN9Minecraft6updateEv");
    minecraft_client_construct = (minecraft_client_construct_t)android_dlsym(handle, "_ZN15MinecraftClientC2EiPPc");
    minecraft_client_init = (minecraft_client_init_t)android_dlsym(handle, "_ZN15MinecraftClient4initEv");
    app_platform_construct = (app_platform_construct_t)android_dlsym(handle, "_ZN11AppPlatformC2Ev");
    screen_construct = (screen_construct_t)android_dlsym(handle, "_ZN6ScreenC2Ev");
    minecraft_set_screen = (minecraft_set_screen_t)android_dlsym(handle, "_ZN9Minecraft9setScreenEP6Screen");
    raknet_instance_send_packet = (raknet_instance_send_packet_t)android_dlsym(handle, "_ZN14RakNetInstance4sendEP6Packet");
    raknet_rakstring_assign = (raknet_rakstring_assign_t)android_dlsym(handle, "_ZN6RakNet9RakString6AssignEPKc");
    minecraft_packets_create_packet = (minecraft_packets_create_packet_t)android_dlsym(handle, "_ZN16MinecraftPackets12createPacketEi");
    server_side_network_handler_get_player = (server_side_network_handler_get_player_t)android_dlsym(handle, "_ZN24ServerSideNetworkHandler9getPlayerERKN6RakNet10RakNetGUIDE");
    server_side_network_handler_redistribute_packet = (server_side_network_handler_redistribute_packet_t)android_dlsym(handle, "_ZN24ServerSideNetworkHandler18redistributePacketEP6PacketRKN6RakNet10RakNetGUIDE");
    chat_packet_deconstruct = (chat_packet_deconstruct_t)android_dlsym(handle, "_ZN10ChatPacketD0Ev");
    message_packet_deconstruct = (message_packet_deconstruct_t)android_dlsym(handle, "_ZN13MessagePacketD0Ev");
    raknet_instance_is_server = (raknet_instance_is_server_t)android_dlsym(handle, "_ZN14RakNetInstance8isServerEv");
    gui_add_message = (gui_add_message_t)android_dlsym(handle, "_ZN3Gui10addMessageERKSs");
    options_set_key = (options_set_key_t)android_dlsym(handle, "_ZN7Options6setKeyEii");
    minecraft_client_get_options = (minecraft_client_get_options_t)android_dlsym(handle, "_ZN15MinecraftClient10getOptionsEv");
    minecraft_client_get_local_player = (minecraft_client_get_local_player_t)android_dlsym(handle, "_ZN15MinecraftClient14getLocalPlayerEv");
    gui_component_fill = (gui_component_fill_t)android_dlsym(handle, "_ZN12GuiComponent4fillEiiiii");
}