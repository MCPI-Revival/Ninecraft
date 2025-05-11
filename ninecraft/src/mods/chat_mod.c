#include <ninecraft/version_ids.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/mods/chat_mod.h>
#include <ninecraft/android/android_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ninecraft/AppPlatform_linux.h>
#include <ninecraft/android/android_vector.h>
#include <ancmp/android_dlfcn.h>
#include <ninecraft/text_box.h>
#include <ninecraft/input/minecraft_keys.h>

/*
    This mod allows you to chat in versions between
    0.5.0 and 0.6.1.
*/

extern void *ninecraft_app;
extern int version_id;

static text_box_t text_box;

void *get_raknet_instance() {
    if (version_id == version_id_0_5_0) {
        return *(void **)((char *)ninecraft_app + MINECRAFT_RAKNET_INSTANCE_OFFSET_0_5_0);
    }
    if (version_id == version_id_0_6_0) {
        return *(void **)((char *)ninecraft_app + MINECRAFT_RAKNET_INSTANCE_OFFSET_0_6_0);
    }
    if (version_id == version_id_0_6_1) {
        return *(void **)((char *)ninecraft_app + MINECRAFT_RAKNET_INSTANCE_OFFSET_0_6_1);
    }
    return NULL;
}

char *get_formatted_message(char *username, char *message) {
    char *formatted_message;
    size_t formatted_message_len;
    formatted_message_len = strlen(message) + strlen(username) + 4;
    formatted_message = (char *)malloc(formatted_message_len);
    if (!formatted_message) {
        return NULL;
    }
    formatted_message[0] = '\0';
    strcat(formatted_message, "<");
    strcat(formatted_message, username);
    strcat(formatted_message, "> ");
    strcat(formatted_message, message);
    formatted_message[formatted_message_len - 1] = '\0';
    return formatted_message;
}

void send_chat_message(char *message) {
    int packet_id;
    void *raknet_instance;
    void *packet;
    if (!minecraft_packets_create_packet || !raknet_instance_send_packet || !chat_packet_deconstruct) {
        return;
    }
    if (version_id == version_id_0_5_0) {
        packet_id = CHAT_PACKET_ID_0_5_0;
    } else if (version_id == version_id_0_6_0) {
        packet_id = CHAT_PACKET_ID_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        packet_id = CHAT_PACKET_ID_0_6_1;
    } else {
        return;
    }
    raknet_instance = get_raknet_instance();
    if (!raknet_instance) {
        return;
    }
    packet = minecraft_packets_create_packet(packet_id);
    if (!packet) {
        return;
    }
    android_string_equ((android_string_t *)((char *)packet + 12), message);
    raknet_instance_send_packet(raknet_instance, packet);
}

void send_message(char *message) {
    int packet_id;
    void *raknet_instance;
    void *packet;
    if (!minecraft_packets_create_packet || !raknet_rakstring_assign || !raknet_instance_send_packet || !message_packet_deconstruct) {
        return;
    }
    if (version_id == version_id_0_5_0) {
        packet_id = MESSAGE_PACKET_ID_0_5_0;
    } else if (version_id == version_id_0_6_0) {
        packet_id = MESSAGE_PACKET_ID_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        packet_id = MESSAGE_PACKET_ID_0_6_1;
    } else {
        return;
    }
    raknet_instance = get_raknet_instance();
    if (!raknet_instance) {
        return;
    }
    packet = minecraft_packets_create_packet(packet_id);
    if (!packet) {
        return;
    }
    raknet_rakstring_assign((void *)((char *)packet + 12), message);
    raknet_instance_send_packet(raknet_instance, packet);
}

void server_side_network_handler_handle_chat_packet(void *__this, void *raknet_guid, void *chat_packet) {
    android_string_t *message_str = (android_string_t *)((char *)chat_packet + 12);
    char *message = android_string_to_str(message_str);
    void *player = server_side_network_handler_get_player(__this, raknet_guid);
    android_string_t *username_str;
    char *username;
    void *raknet_instance;
    char *formatted_message;
    android_string_t formatted_message_str;

    if (!player) {
        return;
    }
    if (version_id == version_id_0_5_0) {
        username_str = (android_string_t *)((char *)player + PLAYER_USERNAME_OFFSET_0_5_0);
    } else if (version_id == version_id_0_6_0) {
        username_str = (android_string_t *)((char *)player + PLAYER_USERNAME_OFFSET_0_6_0);
    } else if (version_id == version_id_0_6_1) {
        username_str = (android_string_t *)((char *)player + PLAYER_USERNAME_OFFSET_0_6_1);
    }
    username = android_string_to_str(username_str);
    formatted_message = get_formatted_message(username, message);
    if (!formatted_message) {
        return;
    }
    android_string_cstr(&formatted_message_str, formatted_message);
    send_message(formatted_message);
    if (!raknet_instance_is_server) {
        return;
    }
    raknet_instance = get_raknet_instance();
    if (raknet_instance) {
        if (raknet_instance_is_server(raknet_instance)) {
            if (gui_add_message) {
                if (version_id == version_id_0_5_0) {
                    gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_5_0, &formatted_message_str);
                } else if (version_id == version_id_0_6_0) {
                    gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_6_0, &formatted_message_str);
                } else if (version_id == version_id_0_6_1) {
                    gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_6_1, &formatted_message_str);
                }
            }
        }
    }
    android_string_destroy(&formatted_message_str);
    free(formatted_message);
}

FLOAT_ABI_FIX void chat_screen_render(void *__this, int mouse_x, int mouse_y, float f) {
    void *raknet_instance;

    gui_component_fill(__this, 0, 0, *((int *)__this + 2), *((int *)__this + 3), 0xa0000000);

    text_box.width = *((int *)__this + 2);
    text_box_render(&text_box, ninecraft_app, mouse_x, mouse_y);

	if (text_box.is_finished) {
        AppPlatform_linux$hideKeyboard(NULL);
        if (text_box.text && text_box.text_len != 0) {
            if (!raknet_instance_is_server) {
                return;
            }
            raknet_instance = get_raknet_instance();
            if (!raknet_instance) {
                return;
            }
            if (raknet_instance_is_server(raknet_instance)) {
                char *username = "Steve";
                char *formatted_message;
                android_string_t formatted_message_str;
                for (int i = 0; i < platform_options.length; ++i) {
                    if (strcmp(platform_options.options[i].name, "mp_username") == 0) {
                        username = platform_options.options[i].value;
                    }
                }
                formatted_message = get_formatted_message(username, text_box.text);
                android_string_cstr(&formatted_message_str, formatted_message);
                if (formatted_message) {
                    send_message(formatted_message);
                    if (gui_add_message) {
                        if (version_id == version_id_0_5_0) {
                            gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_5_0, &formatted_message_str);
                        } else if (version_id == version_id_0_6_0) {
                            gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_6_0, &formatted_message_str);
                        } else if (version_id == version_id_0_6_1) {
                            gui_add_message((char *)ninecraft_app + MINECRAFT_GUI_OFFSET_0_6_1, &formatted_message_str);
                        }
                    }
                    android_string_destroy(&formatted_message_str);
                    free(formatted_message);
                }
            } else {
		        send_chat_message(text_box.text);
            }
        }
        if (text_box.text) {
            free(text_box.text);
        }
        text_box.text = NULL;
        text_box.text_len = 0;
        text_box.is_finished = false;
        minecraft_set_screen(ninecraft_app, NULL);
	}
}

void chat_screen_mouse_clicked(void *__this, int x, int y, int state) {
    if (text_box_is_hovered(&text_box, x, y)) {
        text_box_set_focused(&text_box, true);
        AppPlatform_linux$showKeyboard(NULL);
    } else {
        text_box_set_focused(&text_box, false);
        AppPlatform_linux$hideKeyboard(NULL);
    }
    
}

void chat_screen_mouse_released(void *__this, int x, int y, int state) {
    
}

void chat_screen_key_pressed(void *__this, int code) {
    text_box_keyboard_key_pressed(&text_box, code);
}

void chat_screen_keyboard_new_char(void *__this, char c) {
    text_box_keyboard_new_char(&text_box, c);
}

bool chat_screen_handle_back_event(void *__this, bool back) {
    AppPlatform_linux$hideKeyboard(NULL);
    text_box_set_focused(&text_box, false);
    return false;
}

void chat_mod_append_char(char c) {
    if (version_id == version_id_0_5_0) {
        text_box_keyboard_new_char(&text_box, c);
    }
}

void chat_mod_inject(void *handle) {
    int server_side_network_handler_vtable_offset;
    int chat_screen_render_vtable_offset;
    int chat_screen_mouse_clicked_vtable_offset;
    int chat_screen_mouse_released_vtable_offset;
    int chat_screen_key_pressed_vtable_offset;
    int chat_screen_handle_back_event_vtable_offset;
    int chat_screen_keyboard_new_char_vtable_offset;
    void **server_side_network_handler_vtable = (void **)android_dlsym(handle, "_ZTV24ServerSideNetworkHandler");
    void **chat_screen_vtable = (void **)android_dlsym(handle, "_ZTV10ChatScreen");
    if (!server_side_network_handler_vtable || !chat_screen_vtable) {
        return;
    }
    if (version_id == version_id_0_5_0) {
        server_side_network_handler_vtable_offset = SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_5_0;
        chat_screen_render_vtable_offset = CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_5_0;
        chat_screen_mouse_clicked_vtable_offset = CHAT_SCREEN_MOUSE_CLICKED_VTABLE_OFFSET_0_5_0;
        chat_screen_mouse_released_vtable_offset = CHAT_SCREEN_MOUSE_RELEASED_VTABLE_OFFSET_0_5_0;
        chat_screen_key_pressed_vtable_offset = CHAT_SCREEN_KEY_PRESSED_VTABLE_OFFSET_0_5_0;
        chat_screen_handle_back_event_vtable_offset = CHAT_SCREEN_HANDLE_BACK_EVENT_VTABLE_OFFSET_0_5_0;
    } else if (version_id == version_id_0_6_0) {
        server_side_network_handler_vtable_offset = SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_6_0;
        chat_screen_render_vtable_offset = CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_6_0;
        chat_screen_mouse_clicked_vtable_offset = CHAT_SCREEN_MOUSE_CLICKED_VTABLE_OFFSET_0_6_0;
        chat_screen_mouse_released_vtable_offset = CHAT_SCREEN_MOUSE_RELEASED_VTABLE_OFFSET_0_6_0;
        chat_screen_key_pressed_vtable_offset = CHAT_SCREEN_KEY_PRESSED_VTABLE_OFFSET_0_6_0;
        chat_screen_keyboard_new_char_vtable_offset = CHAT_SCREEN_KEYBOARD_NEW_CHAR_VTABLE_OFFSET_0_6_0;
        chat_screen_handle_back_event_vtable_offset = CHAT_SCREEN_HANDLE_BACK_EVENT_VTABLE_OFFSET_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        server_side_network_handler_vtable_offset = SERVERSIDENETWORKHANDLER_CHAT_PACKET_VTABLE_OFFSET_0_6_1;
        chat_screen_render_vtable_offset = CHAT_SCREEN_RENDER_VTABLE_OFFSET_0_6_1;
        chat_screen_mouse_clicked_vtable_offset = CHAT_SCREEN_MOUSE_CLICKED_VTABLE_OFFSET_0_6_1;
        chat_screen_mouse_released_vtable_offset = CHAT_SCREEN_MOUSE_RELEASED_VTABLE_OFFSET_0_6_1;
        chat_screen_key_pressed_vtable_offset = CHAT_SCREEN_KEY_PRESSED_VTABLE_OFFSET_0_6_1;
        chat_screen_keyboard_new_char_vtable_offset = CHAT_SCREEN_KEYBOARD_NEW_CHAR_VTABLE_OFFSET_0_6_1;
        chat_screen_handle_back_event_vtable_offset = CHAT_SCREEN_HANDLE_BACK_EVENT_VTABLE_OFFSET_0_6_1;
    } else {
        return;
    }
    server_side_network_handler_vtable[server_side_network_handler_vtable_offset] = (void *)server_side_network_handler_handle_chat_packet;
    chat_screen_vtable[chat_screen_render_vtable_offset] = (void *)chat_screen_render;
    chat_screen_vtable[chat_screen_mouse_clicked_vtable_offset] = (void *)chat_screen_mouse_clicked;
    chat_screen_vtable[chat_screen_mouse_released_vtable_offset] = (void *)chat_screen_mouse_released;
    chat_screen_vtable[chat_screen_key_pressed_vtable_offset] = (void *)chat_screen_key_pressed;
    chat_screen_vtable[chat_screen_handle_back_event_vtable_offset] = (void *)chat_screen_handle_back_event;
    if (version_id >= version_id_0_6_0) {
        chat_screen_vtable[chat_screen_keyboard_new_char_vtable_offset] = (void *)chat_screen_keyboard_new_char;
    }

    text_box_construct(&text_box);
    text_box.placeholder = "Enter message...";
}
