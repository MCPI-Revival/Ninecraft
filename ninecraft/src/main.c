#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/mman.h>
#else
#include <direct.h>
#define mkdir(x, y) _mkdir(x)
#endif
#include <sys/types.h>
#include <sys/stat.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <ninecraft/patch/detours.h>
#include <ninecraft/gfx/gles_compat.h>
#include <ninecraft/version_ids.h>
#include <ninecraft/input/minecraft_keys.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/symbols.h>
#include <ninecraft/AppPlatform_linux.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/input/keyboard.h>
#include <ninecraft/input/mouse_device.h>
#include <ninecraft/input/multitouch.h>
#include <ninecraft/mods/inject.h>
#include <ninecraft/mods/mod_loader.h>
#include <ninecraft/app_platform.h>
#include <math.h>
#include <wchar.h>
#include <wctype.h>
#include <ninecraft/audio/sles.h>
#include <ninecraft/audio/audio_engine.h>
#include <zlib.h>
#include <ancmp/android_stat.h>

#include <ancmp/hooks.h>
#include <ancmp/android_dlfcn.h>
#include <ancmp/linker.h>
#include <ancmp/abi_fix.h>

#include <ninecraft/options.h>
#include <ninecraft/mods/chat_mod.h>
#include <ninecraft/ninecraft_http.h>
#include <ninecraft/ninecraft_store.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void *handle = NULL;
GLFWwindow *_window = NULL;
bool ctrl_pressed = false;

int default_mouse_mode = GLFW_CURSOR_NORMAL;

int version_id = 0;

float y_cam = 0.0;
float x_cam = 0.0;

void *ninecraft_app;
AppPlatform_linux platform;

static unsigned char *controller_states;
static float *controller_x_stick;
static float *controller_y_stick;

bool mouse_pointer_hidden = false;

int old_pos_x, old_pos_y, old_width, old_height;

void *load_library(const char *name) {
#if defined(__i386__) || defined(_M_IX86)
    char *arch = "x86";
#else
#if defined(__arm__) || defined(_M_ARM) 
    char *arch = "armeabi-v7a";
#else
    char *arch = "";
#endif
#endif
    char *fullpath = (char *)malloc(1024);
    fullpath[0] = '\0';
    getcwd(fullpath, 1024);
    strcat(fullpath, "/lib/");
    strcat(fullpath, arch);
    strcat(fullpath, "/");
    strcat(fullpath, name);

    void *handle = android_dlopen(fullpath, ANDROID_RTLD_LAZY);
    if (handle == NULL) {
        printf("failed to load library %s: %s\n", fullpath, android_dlerror());
        return NULL;
    }
    printf("lib: %s: : %p\n", fullpath, handle);
    free(fullpath);
    return handle;
}

void stub_symbols(const char **symbols, void *stub_func) {
    int i = 0;
    while (true) {
        const char *sym = symbols[i];
        if (sym == NULL) {
            break;
        }
        add_custom_hook((char *)sym, stub_func);
        ++i;
    }
}

void __android_log_print(int prio, const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("[%s] ", tag);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

void android_stub() {
    puts("warn: android call");
}

void egl_stub() {
    // puts("warn: egl call");
}

int mouseToGameKeyCode(int keyCode) {
    if (keyCode == GLFW_MOUSE_BUTTON_LEFT) {
        return MCKEY_DESTROY;
    } else if (keyCode == GLFW_MOUSE_BUTTON_RIGHT) {
        return MCKEY_USE;
    }
    return 0;
}

static void mouse_click_callback(GLFWwindow *window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (!mouse_pointer_hidden) {
        int mc_button = (button == GLFW_MOUSE_BUTTON_LEFT ? 1 : (button == GLFW_MOUSE_BUTTON_RIGHT ? 2 : 0));
        if (version_id == version_id_0_1_0) {
            ((void (*)(int, int, int, int))android_dlsym(handle, "_ZN5Mouse4feedEiiii"))((int)mc_button, (int)(action == GLFW_PRESS ? 1 : 0), (int)xpos, (int)ypos);
        } else if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(android_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0, 0);
            multitouch_feed_0_6((char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_5_0_j) {
            mouse_device_feed_0_5(android_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos);
            multitouch_feed_0_5((char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0);
        }
    } else {
        int game_keycode = mouseToGameKeyCode(button);

        if (action == GLFW_PRESS) {
            keyboard_feed(game_keycode, 1);
        } else if (action == GLFW_RELEASE) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    char key_code = 0;
    if (yoffset > 0) {
        key_code = MCKEY_MENU_PREVIOUS;
    } else if (yoffset < 0) {
        key_code = MCKEY_MENU_NEXT;
    }
    keyboard_feed(key_code, 1);
    keyboard_feed(key_code, 0);
}

static double last_mouse_x = 0;
static double last_mouse_y = 0;
static bool ignore_relative_motion = false;
static void mouse_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    if (!mouse_pointer_hidden || version_id >= version_id_0_6_0) {
        if (version_id == version_id_0_1_0) {
            ((void (*)(int, int, int, int))android_dlsym(handle, "_ZN5Mouse4feedEiiii"))(0, 0, (int)xpos, (int)ypos);
        } else if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(android_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos, (short)(!ignore_relative_motion ? (xpos - last_mouse_x) : 0), (short)(!ignore_relative_motion ? (ypos - last_mouse_y) : 0));
            ignore_relative_motion = false;
            last_mouse_x = xpos;
            last_mouse_y = ypos;
            multitouch_feed_0_6(0, 0, (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_5_0_j) {
            mouse_device_feed_0_5(android_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos);
            multitouch_feed_0_5(0, 0, (short)xpos, (short)ypos, 0);
        }
    } else {
        int cx;
        int cy;
        glfwGetWindowSize(window, &cx, &cy);
        cx /= 2;
        cy /= 2;
        if ((int)xpos != cy || (int)ypos != cy) {
            glfwSetCursorPos(window, cx, cy);
            y_cam -= ((float)ypos - (float)cy) / 1.7;
            x_cam += ((float)xpos - (float)cx) / 0.7;
        }
    }
}

int getGameKeyCode(int keycode) {
    if (keycode == GLFW_KEY_W) {
        return MCKEY_FORWARD;
    } else if (keycode == GLFW_KEY_A) {
        return MCKEY_LEFT;
    } else if (keycode == GLFW_KEY_S) {
        return MCKEY_BACK;
    } else if (keycode == GLFW_KEY_D) {
        return MCKEY_RIGHT;
    } else if (keycode == GLFW_KEY_SPACE && !is_keyboard_visible) {
        return MCKEY_JUMP;
    } else if (keycode == GLFW_KEY_E) {
        return MCKEY_INVENTORY;
    } else if (keycode == GLFW_KEY_ESCAPE) {
        return MCKEY_PAUSE;
    } else if (keycode == GLFW_KEY_C) {
        return MCKEY_CRAFTING;
    } else if (keycode == GLFW_KEY_ENTER) {
        return MCKEY_SIGN_ENTER;
    } else if (keycode == GLFW_KEY_BACKSPACE) {
        return MCKEY_SIGN_BACKSPACE;
    } else if (keycode == GLFW_KEY_LEFT_CONTROL) {
        return MCKEY_MENU_CANCEL;
    } else if (keycode == GLFW_KEY_LEFT_SHIFT) {
        return MCKEY_SNEAK;
    } else if (keycode == GLFW_KEY_Q) {
        return MCKEY_DROP;
    } else {
        return 0;
    }
}

void set_ninecraft_size_0_1_0(int width, int height) {
    float *inv_gui_scale = (float *)android_dlsym(handle, "_ZN3Gui11InvGuiScaleE");
    int *mc_width = (int *)android_dlsym(handle, "_ZN9Minecraft5widthE");
    int *mc_height = (int *)android_dlsym(handle, "_ZN9Minecraft6heightE");
    void (*screen_set_size)(void *screen, int width, int height) = (void (*)(void *screen, int width, int height))android_dlsym(handle, "_ZN6Screen7setSizeEii");

    *mc_width = width;
    *mc_height = height;
    
    if (width < 1000) {
        if (width < 800) {
            if (width < 400) {
                *inv_gui_scale = 1.0;
            } else {
                *inv_gui_scale = 0.5;
            }
        } else {
            *inv_gui_scale = 0.3333333;
        }
    } else {
        *inv_gui_scale = 0.25;
    }
    void *screen = *(void **)((char *)ninecraft_app + 0xd14);
    if (screen != NULL) {
        float new_screen_width = (float)(width) * (*inv_gui_scale);
        float new_screen_height = (float)(height) * (*inv_gui_scale);
        screen_set_size(
            screen,
            (int)(0.0 < new_screen_width) * (int)new_screen_width,
            (int)(0.0 < new_screen_height) * (int)new_screen_height);
        ((int *)screen)[6] = 0;
        ((int *)screen)[7] = 0;
        ((int *)screen)[8] = 0;
        ((int *)screen)[9] = 0;
        ((int *)screen)[10] = 0;
        ((int *)screen)[11] = 0;
        ((void (*)(void *))((*(int **)screen)[3]))(screen);
        

    }
}

static void set_ninecraft_size(int width, int height) {
    glClear(GL_DEPTH_BUFFER_BIT);
    if (version_id >= version_id_0_10_0) {
        minecraft_client_set_size(ninecraft_app, width, height, 2.f);
    } else {
        minecraft_set_size(ninecraft_app, width, height);
    }
    size_t screen_offset;
    if (version_id == version_id_0_10_5) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_5;
    } else if (version_id == version_id_0_10_4) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_4;
    } else if (version_id == version_id_0_10_3) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_3;
    } else if (version_id == version_id_0_10_2) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_2;
    } else if (version_id == version_id_0_10_1) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_1;
    } else if (version_id == version_id_0_10_0) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_10_0;
    } else if (version_id == version_id_0_9_5) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_5;
    } else if (version_id == version_id_0_9_4) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_4;
    } else if (version_id == version_id_0_9_3) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_3;
    } else if (version_id == version_id_0_9_2) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_2;
    } else if (version_id == version_id_0_9_1) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_1;
    } else if (version_id == version_id_0_9_0) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_9_0;
    } else if (version_id == version_id_0_8_1) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_8_1;
    } else if (version_id == version_id_0_8_0) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_8_0;
    } else if (version_id == version_id_0_7_6) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_6;
    } else if (version_id == version_id_0_7_5) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_5;
    } else if (version_id == version_id_0_7_4) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_4;
    } else if (version_id == version_id_0_7_3) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_3;
    } else if (version_id == version_id_0_7_2) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_2;
    } else if (version_id == version_id_0_7_1) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_1;
    } else if (version_id == version_id_0_7_0) {
        screen_offset = NINECRAFTAPP_SCREEN_OFFSET_0_7_0;
    } else {
        return;
    }
    *(float *)android_dlsym(handle, "_ZN3Gui11InvGuiScaleE") = 0.5f;
    *(float *)android_dlsym(handle, "_ZN3Gui8GuiScaleE") = 2.0f;
    void *screen = *(void **)((char *)ninecraft_app + screen_offset);
    if (screen) {
        ((void (*)(void *, int, int))android_dlsym(handle, "_ZN6Screen7setSizeEii"))(screen, width * 0.5f, height * 0.5f);
    }
}

static void resize_callback(GLFWwindow *window, int width, int height) {
    if (version_id == version_id_0_1_0) {
        set_ninecraft_size_0_1_0(width, height);
    } else {
        set_ninecraft_size(width, height);
    }
}

static void char_callback(GLFWwindow *window, unsigned int codepoint) {
    if (is_keyboard_visible) {
        chat_mod_append_char(codepoint);
        if (version_id >= version_id_0_6_0 && version_id <= version_id_0_7_1) {
            keyboard_feed_text_0_6_0((char)codepoint);
        } else if (version_id >= version_id_0_7_2) {
            char p_codepoint[5] = {'\0', '\0', '\0', '\0', '\0'};

            if (codepoint <= 0x7f) {
                p_codepoint[0] = (char)codepoint;
            } else if (codepoint <= 0x7fff) {
                p_codepoint[0] = (char)(0xc0 | ((codepoint >> 6) & 0x1f));
                p_codepoint[1] = (char)(0x80 | ((codepoint & 0x3f)));
            } else if (codepoint <= 0xffff) {
                p_codepoint[0] = (char)(0xe0 | ((codepoint >> 12) & 0x0f));
                p_codepoint[1] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
                p_codepoint[2] = (char)(0x80 | (codepoint & 0x3f));
            } else {
                p_codepoint[0] = (char)(0xf0 | ((codepoint >> 18) & 0x07));
                p_codepoint[1] = (char)(0x80 | ((codepoint >> 12) & 0x3f));
                p_codepoint[2] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
                p_codepoint[3] = (char)(0x80 | (codepoint & 0x3f));
            }

            android_string_t str;
            android_string_cstr(&str, p_codepoint);
            keyboard_feed_text_0_7_2(&str, false);
        }
    }
}

void *chat_screen_create() {
    void **chat_screen_vtable = (void **)android_dlsym(handle, "_ZTV10ChatScreen");
    void *chat_screen;
    if (!chat_screen_vtable || !screen_construct) {
        return NULL;
    }
    chat_screen = malloc(0x48);
    if (!chat_screen) {
        return NULL;
    }
    screen_construct(chat_screen);
    *(void **)chat_screen = &chat_screen_vtable[2];
    return chat_screen;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F11) {
        if (action == GLFW_PRESS) {
            if (glfwGetWindowMonitor(_window) == NULL) {
                glfwGetWindowPos(_window, &old_pos_x, &old_pos_y);
                glfwGetWindowSize(_window, &old_width, &old_height);
                const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                glfwSetWindowMonitor(_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
            } else {
                glfwSetWindowMonitor(_window, NULL, old_pos_x, old_pos_y, old_width, old_height, 0);
            }
        }
    } else {
        if (key == GLFW_KEY_LEFT_CONTROL) {
            if (action == GLFW_PRESS) {
                ctrl_pressed = true;
            } else if (action == GLFW_RELEASE) {
                ctrl_pressed = false;
            }
        }
        int game_keycode = getGameKeyCode(key);
        if (key == GLFW_KEY_Q && action == GLFW_PRESS && mouse_pointer_hidden && version_id >= version_id_0_5_0 && version_id <= version_id_0_11_0) {
            size_t player_offset, inventory_offset;
            if (version_id == version_id_0_5_0) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_5_0;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_5_0;
            } else if (version_id == version_id_0_5_0_j) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_5_0_J;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_5_0_J;
            } else if (version_id == version_id_0_6_0) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_6_0;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_6_0;
            } else if (version_id == version_id_0_6_1) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_6_1;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_6_1;
            } else if (version_id == version_id_0_7_0) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_0;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_0;
            } else if (version_id == version_id_0_7_1) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_1;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_1;
            } else if (version_id == version_id_0_7_2) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_2;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_2;
            } else if (version_id == version_id_0_7_3) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_3;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_3;
            } else if (version_id == version_id_0_7_4) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_4;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_4;
            } else if (version_id == version_id_0_7_5) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_5;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_5;
            } else if (version_id == version_id_0_7_6) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_7_6;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_7_6;
            } else if (version_id == version_id_0_8_0) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_0;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_8_0;
            } else if (version_id == version_id_0_8_1) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_8_1;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_8_1;
            } else if (version_id == version_id_0_9_0) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_0;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_0;
            } else if (version_id == version_id_0_9_1) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_1;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_1;
            } else if (version_id == version_id_0_9_2) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_2;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_2;
            } else if (version_id == version_id_0_9_3) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_3;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_3;
            } else if (version_id == version_id_0_9_4) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_4;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_4;
            } else if (version_id == version_id_0_9_5) {
                player_offset = MINECRAFT_LOCAL_PLAYER_OFFSET_0_9_5;
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_9_5;
            } else if (version_id == version_id_0_10_0) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_0;
            } else if (version_id == version_id_0_10_1) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_1;
            } else if (version_id == version_id_0_10_2) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_2;
            } else if (version_id == version_id_0_10_3) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_3;
            } else if (version_id == version_id_0_10_4) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_4;
            } else if (version_id == version_id_0_10_5) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_10_5;
            } else if (version_id == version_id_0_11_0) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_11_0;
            }
            void *player = NULL;
            if (version_id >= version_id_0_5_0 && version_id <= version_id_0_9_5) {
                player = *(void **)((char *)ninecraft_app + player_offset);
            } else if (version_id >= version_id_0_10_0 && version_id <= version_id_0_11_0) {
                player = minecraft_client_get_local_player(ninecraft_app);
            }
            if (player) {
                bool is_creative = ((bool (*)(void *))android_dlsym(handle, "_ZN9Minecraft14isCreativeModeEv"))(ninecraft_app);
                if (!is_creative) {
                    void *player_inventory = *(void **)((char *)player + inventory_offset);
                    void *item_instance = NULL;
                    if (version_id >= version_id_0_11_0) {
                        item_instance = ((void *(*)(void *))android_dlsym(handle, "_ZNK9Inventory15getSelectedItemEv"))(player_inventory);
                    } else {
                        item_instance = ((void *(*)(void *))android_dlsym(handle, "_ZN9Inventory11getSelectedEv"))(player_inventory);
                    }
                    if (item_instance) {
                        bool is_empty = ((bool (*)(void *))android_dlsym(handle, "_ZNK12ItemInstance6isNullEv"))(item_instance);
                        if (!is_empty) {
                            void *item_instance_copy = ((void *(*)(void *, void *))android_dlsym(handle, "_ZN12ItemInstance5cloneEPKS_"))(item_instance, NULL);
                            if (!ctrl_pressed) {
                                *(int8_t *)item_instance_copy = 1;
                                *(int8_t *)item_instance -= 1;
                            }
                            if (*(int8_t *)item_instance < 1 || ctrl_pressed) {
                                android_vector_t *slots = NULL;
                                if (version_id >= version_id_0_11_0) { 
                                    slots = (android_vector_t *)((char *)player_inventory + 16);
                                } else {
                                    slots = ((android_vector_t *(*)(void *))android_dlsym(handle, "_ZN16FillingContainer11getSlotListERi"))(player_inventory);
                                }
                                size_t slot = 0;
                                for (; slot < android_vector_size(slots, sizeof(void *)); ++slot) {
                                    if (*(void **)android_vector_at(slots, slot, sizeof(void *)) == item_instance) {
                                        break;
                                    }
                                }
                                ((void (*)(void *, int))android_dlsym(handle, "_ZN16FillingContainer7releaseEi"))(player_inventory, slot);
                                ((void (*)(void *, int))android_dlsym(handle, "_ZN16FillingContainer22compressLinkedSlotListEi"))(player_inventory, slot);
                            }

                            if (version_id >= version_id_0_5_0 && version_id <= version_id_0_7_1) {
                                ((void (*)(void *, void *, bool))android_dlsym(handle, "_ZN11LocalPlayer4dropEP12ItemInstanceb"))(player, item_instance_copy, false);
                            } else if (version_id >= version_id_0_7_2 && version_id <= version_id_0_11_0) {
                                ((void (*)(void *, void *, bool))android_dlsym(handle, "_ZN11LocalPlayer4dropEPK12ItemInstanceb"))(player, item_instance_copy, false);
                            }
                        }
                    }
                }
            }         
        } else if (mouse_pointer_hidden && key == GLFW_KEY_LEFT_SHIFT && version_id <= version_id_0_4_0_j) {
            if (controller_states) {
                if (action == GLFW_PRESS) {
                    controller_states[0] = 1;
                } else if (action == GLFW_RELEASE) {
                    controller_states[0] = 0;
                }
            }
        } else if (mouse_pointer_hidden && key == GLFW_KEY_T) {
            if (action == GLFW_PRESS) {
                if (version_id >= version_id_0_7_0 && version_id <= version_id_0_11_0) {
                    size_t minecraft_screenchooser_offset;
                    if (version_id == version_id_0_7_0) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_0;
                    } else if (version_id == version_id_0_7_1) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_1;
                    } else if (version_id == version_id_0_7_2) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_2;
                    } else if (version_id == version_id_0_7_3) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_3;
                    } else if (version_id == version_id_0_7_4) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_4;
                    } else if (version_id == version_id_0_7_5) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_5;
                    } else if (version_id == version_id_0_7_6) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_7_6;
                    } else if (version_id == version_id_0_8_0) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_8_0;
                    } else if (version_id == version_id_0_8_1) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_8_1;
                    } else if (version_id == version_id_0_9_0) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_0;
                    } else if (version_id == version_id_0_9_1) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_1;
                    } else if (version_id == version_id_0_9_2) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_2;
                    } else if (version_id == version_id_0_9_3) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_3;
                    } else if (version_id == version_id_0_9_4) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_4;
                    } else if (version_id == version_id_0_9_5) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_9_5;
                    } else if (version_id == version_id_0_10_0) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_0;
                    } else if (version_id == version_id_0_10_1) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_1;
                    } else if (version_id == version_id_0_10_2) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_2;
                    } else if (version_id == version_id_0_10_3) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_3;
                    } else if (version_id == version_id_0_10_4) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_4;
                    } else if (version_id == version_id_0_10_5) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_10_5;
                    } else if (version_id == version_id_0_11_0) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_11_0;
                    }
                    void *minecraft_screenchooser = NULL;
                    if (version_id >= version_id_0_10_0) {
                        minecraft_screenchooser = *(void **)((char *)ninecraft_app + minecraft_screenchooser_offset);
                    } else {
                        minecraft_screenchooser = (void *)((char *)ninecraft_app + minecraft_screenchooser_offset);
                    }
                    if (version_id >= version_id_0_9_0) {
                        ((void (*)(void *, int))android_dlsym(handle, "_ZN13ScreenChooser9setScreenE8ScreenId"))(minecraft_screenchooser, 5);
                    } else {
                        ((void (*)(void *, int))android_dlsym(handle, "_ZN13ScreenChooser9setScreenE8ScreenId"))(minecraft_screenchooser, 7);
                    }
                } else if (version_id >= version_id_0_1_0 && version_id <= version_id_0_6_1) {
                    void *chat_screen = chat_screen_create();
                    if (chat_screen) {
                        minecraft_set_screen(ninecraft_app, chat_screen);
                    }
                }
            }
        } else if (version_id >= version_id_0_1_1 && key == GLFW_KEY_ESCAPE) {
            if (action == GLFW_PRESS) {
                if (version_id >= version_id_0_10_0) {
                    minecraft_client_handle_back(ninecraft_app, false);
                } else {
                    ninecraft_app_handle_back(ninecraft_app, false);
                }
            }
        } else if (action == GLFW_PRESS && game_keycode) {
            keyboard_feed(game_keycode, 1);
        } else if (action == GLFW_RELEASE && game_keycode) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

void window_close_callback(GLFWwindow *window) {
    audio_engine_destroy();
    exit(0);
}

void grab_mouse() {
    puts("grab_mouse");
    mouse_pointer_hidden = true;
    ignore_relative_motion = true;
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    mod_loader_execute_on_minecraft_grab_mouse(ninecraft_app, version_id);
}

void release_mouse() {
    puts("release_mouse");
    mouse_pointer_hidden = false;
    glfwSetInputMode(_window, GLFW_CURSOR, default_mouse_mode);
    //glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    double cursor_x;
    double cursor_y;
    glfwGetCursorPos(_window, &cursor_x, &cursor_y);
    mouse_pos_callback(_window, cursor_x, cursor_y);
    mod_loader_execute_on_minecraft_release_mouse(ninecraft_app, version_id);
}

void gles_hook() {
    add_custom_hook("glAlphaFunc", (void *)gl_alpha_func);
    add_custom_hook("glBindBuffer", (void *)gl_bind_buffer);
    add_custom_hook("glBindTexture", (void *)gl_bind_texture);
    add_custom_hook("glBlendFunc", (void *)gl_blend_func);
    add_custom_hook("glBufferData", (void *)gl_buffer_data);
    add_custom_hook("glClear", (void *)gl_clear);
    add_custom_hook("glClearColor", (void *)gl_clear_color);
    add_custom_hook("glColor4f", (void *)gl_color_4_f);
    add_custom_hook("glColorMask", (void *)gl_color_mask);
    add_custom_hook("glColorPointer", (void *)gl_color_pointer);
    add_custom_hook("glCullFace", (void *)gl_cull_face);
    add_custom_hook("glDeleteBuffers", (void *)gl_delete_buffers);
    add_custom_hook("glDeleteTextures", (void *)gl_delete_textures);
    add_custom_hook("glDepthFunc", (void *)gl_depth_func);
    add_custom_hook("glDepthMask", (void *)gl_depth_mask);
    add_custom_hook("glDepthRangef", (void *)gl_depth_range_f);
    add_custom_hook("glDisable", (void *)gl_disable);
    add_custom_hook("glDisableClientState", (void *)gl_disable_client_state);
    add_custom_hook("glDrawArrays", (void *)gl_draw_arrays);
    add_custom_hook("glEnable", (void *)gl_enable);
    add_custom_hook("glEnableClientState", (void *)gl_enable_client_state);
    add_custom_hook("glFogf", (void *)gl_fog_f);
    add_custom_hook("glFogfv", (void *)gl_fog_f_v);
    add_custom_hook("glFogx", (void *)gl_fog_x);
    add_custom_hook("glGenTextures", (void *)gl_gen_textures);
    add_custom_hook("glGetFloatv", (void *)gl_get_float_v);
    add_custom_hook("glGetString", (void *)gl_get_string);
    add_custom_hook("glHint", (void *)gl_hint);
    add_custom_hook("glLineWidth", (void *)gl_line_width);
    add_custom_hook("glLoadIdentity", (void *)gl_load_identity);
    add_custom_hook("glMatrixMode", (void *)gl_matrix_mode);
    add_custom_hook("glMultMatrixf", (void *)gl_mult_matrix_f);
    add_custom_hook("glNormal3f", (void *)gl_normal_3_f);
    add_custom_hook("glOrthof", (void *)gl_ortho_f);
    add_custom_hook("glPolygonOffset", (void *)gl_polygon_offset);
    add_custom_hook("glPopMatrix", (void *)gl_pop_matrix);
    add_custom_hook("glPushMatrix", (void *)gl_push_matrix);
    add_custom_hook("glReadPixels", (void *)gl_read_pixels);
    add_custom_hook("glRotatef", (void *)gl_rotate_f);
    add_custom_hook("glScalef", (void *)gl_scale_f);
    add_custom_hook("glScissor", (void *)gl_scissor);
    add_custom_hook("glShadeModel", (void *)gl_shade_model);
    add_custom_hook("glTexCoordPointer", (void *)gl_tex_coord_pointer);
    add_custom_hook("glTexImage2D", (void *)gl_tex_image_2_d);
    add_custom_hook("glTexParameteri", (void *)gl_tex_parameter_i);
    add_custom_hook("glTexSubImage2D", (void *)gl_tex_sub_image_2_d);
    add_custom_hook("glTranslatef", (void *)gl_translate_f);
    add_custom_hook("glVertexPointer", (void *)gl_vertex_pointer);
    add_custom_hook("glViewport", (void *)gl_viewport);
    add_custom_hook("glDrawElements", (void *)gl_draw_elements);
    add_custom_hook("glGetError", (void *)gl_get_error);
    add_custom_hook("glGenBuffers", (void *)gl_gen_buffers);
    add_custom_hook("glStencilFunc", (void *)gl_stencil_func);
    add_custom_hook("glStencilMask", (void *)gl_stencil_mask);
    add_custom_hook("glLightModelf", (void *)gl_light_model_f);
    add_custom_hook("glLightfv", (void *)gl_light_f_v);
    add_custom_hook("glNormalPointer", (void *)gl_normal_pointer);
    add_custom_hook("glStencilOp", (void *)gl_stencil_op);
    add_custom_hook("glActiveTexture", (void *)gl_active_texture);
    add_custom_hook("glAttachShader", (void *)gl_attach_shader);
    add_custom_hook("glClearStencil", (void *)gl_clear_stencil);
    add_custom_hook("glCompileShader", (void *)gl_compile_shader);
    add_custom_hook("glCreateProgram", (void *)gl_create_program);
    add_custom_hook("glCreateShader", (void *)gl_create_shader);
    add_custom_hook("glDeleteProgram", (void *)gl_delete_program);
    add_custom_hook("glEnableVertexAttribArray", (void *)gl_enable_vertex_attrib_array);
    add_custom_hook("glGetActiveAttrib", (void *)gl_get_active_attrib);
    add_custom_hook("glGetActiveUniform", (void *)gl_get_active_uniform);
    add_custom_hook("glGetAttribLocation", (void *)gl_get_attrib_location);
    add_custom_hook("glGetProgramInfoLog", (void *)gl_get_program_info_log);
    add_custom_hook("glGetProgramiv", (void *)gl_get_program_i_v);
    add_custom_hook("glGetShaderInfoLog", (void *)gl_get_shader_info_log);
    add_custom_hook("glGetShaderiv", (void *)gl_get_shader_i_v);
    add_custom_hook("glGetShaderPrecisionFormat", (void *)gl_get_shader_precision_format);
    add_custom_hook("glGetUniformLocation", (void *)gl_get_uniform_location);
    add_custom_hook("glLinkProgram", (void *)gl_link_program);
    add_custom_hook("glReleaseShaderCompiler", (void *)gl_release_shader_compiler);
    add_custom_hook("glShaderSource", (void *)gl_shader_source);
    add_custom_hook("glUniform1fv", (void *)gl_uniform_1_f_v);
    add_custom_hook("glUniform1iv", (void *)gl_uniform_1_i_v);
    add_custom_hook("glUniform2fv", (void *)gl_uniform_2_f_v);
    add_custom_hook("glUniform2iv", (void *)gl_uniform_2_i_v);
    add_custom_hook("glUniform3fv", (void *)gl_uniform_3_f_v);
    add_custom_hook("glUniform3iv", (void *)gl_uniform_3_i_v);
    add_custom_hook("glUniform4fv", (void *)gl_uniform_4_f_v);
    add_custom_hook("glUniform4iv", (void *)gl_uniform_4_i_v);
    add_custom_hook("glUniformMatrix2fv", (void *)gl_uniform_matrix_2_f_v);
    add_custom_hook("glUniformMatrix3fv", (void *)gl_uniform_matrix_3_f_v);
    add_custom_hook("glUniformMatrix4fv", (void *)gl_uniform_matrix_4_f_v);
    add_custom_hook("glUseProgram", (void *)gl_use_program);
    add_custom_hook("glVertexAttribPointer", (void *)gl_vertex_attrib_pointer);
}

int __my_srget(FILE *astream) {
    puts("__srget");
    return EOF;
}

void missing_hook() {
    add_custom_hook("deflateInit_", deflateInit_);
    add_custom_hook("deflateInit2_", deflateInit2_);
    add_custom_hook("deflate", deflate);
    add_custom_hook("deflateEnd", deflateEnd);
    add_custom_hook("inflateInit_", inflateInit_);
    add_custom_hook("inflateInit2_", inflateInit2_);
    add_custom_hook("inflate", inflate);
    add_custom_hook("inflateEnd", inflateEnd);
    add_custom_hook("uncompress", uncompress);
    add_custom_hook("compress", compress);
    add_custom_hook("compressBound", compressBound);

    add_custom_hook("__srget", __my_srget);
}

unsigned char mcpi_api_initialized = 0;

void piapi_init() {
    size_t minecraft_command_server_offset = version_id_unknown;
    if (version_id == version_id_0_6_0) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_6_1;
    } else if (version_id == version_id_0_7_0) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_0;
    } else if (version_id == version_id_0_7_1) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_1;
    } else if (version_id == version_id_0_7_2) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_2;
    } else if (version_id == version_id_0_7_3) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_3;
    } else if (version_id == version_id_0_7_4) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_4;
    } else if (version_id == version_id_0_7_5) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_5;
    } else if (version_id == version_id_0_7_6) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_7_6;
    } else if (version_id == version_id_0_8_0) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_8_0;
    } else if (version_id == version_id_0_8_1) {
        minecraft_command_server_offset = MINECRAFT_COMMANDSERVER_OFFSET_0_8_1;
    }
    void *command_server = *(void **)((char *)ninecraft_app + minecraft_command_server_offset);
    if (command_server != NULL) {
        command_server_deconstruct(command_server);
        if (command_server) {
            free(command_server);
        }
    }
    command_server = malloc(0xaaa);
    command_server_construct(command_server, ninecraft_app);
    *(void **)((char *)ninecraft_app + minecraft_command_server_offset) = command_server;
    command_server_init(command_server, 4711);
}

void leveldb_zlib_compress_impl(void *__this, const char *input, unsigned int length, android_string_t *output) {
    size_t BUFSIZE = 128 * 1024;
    uint8_t *temp_buffer = malloc(BUFSIZE);

    size_t current_alloc_len = ((compressBound(length) / BUFSIZE) + 1) * BUFSIZE;
	uint8_t *buf = (uint8_t *)malloc(current_alloc_len);
    size_t off = 0;

	z_stream strm;
	strm.zalloc = 0;
	strm.zfree = 0;
	strm.next_in = (unsigned char *)(input);
	strm.avail_in = (uint32_t)length;
	strm.next_out = temp_buffer;
	strm.avail_out = BUFSIZE;
	deflateInit(&strm, 0);
	int deflate_res = Z_OK;
	while (strm.avail_in != 0)
	{
		int res = deflate(&strm, Z_NO_FLUSH);
		assert(res == Z_OK);
		if (strm.avail_out == 0)
		{
            if (off >= current_alloc_len) {
                current_alloc_len += BUFSIZE;
                buf = (uint8_t *)realloc(buf, current_alloc_len);
            }
            memcpy(&buf[off], temp_buffer, BUFSIZE);
            off += BUFSIZE;
			strm.next_out = temp_buffer;
			strm.avail_out = BUFSIZE;
		}
	}
	while (deflate_res == Z_OK)
	{
		if (strm.avail_out == 0)
		{
			if (off >= current_alloc_len) {
                current_alloc_len += BUFSIZE;
                buf = (uint8_t *)realloc(buf, current_alloc_len);
            }
            memcpy(&buf[off], temp_buffer, BUFSIZE);
            off += BUFSIZE;
			strm.next_out = temp_buffer;
			strm.avail_out = BUFSIZE;
		}
		deflate_res = deflate(&strm, Z_FINISH);
	}
	assert(deflate_res == Z_STREAM_END);
    if (off >= current_alloc_len) {
        current_alloc_len += BUFSIZE;
        buf = (uint8_t *)realloc(buf, current_alloc_len);
    }
    memcpy(&buf[off], temp_buffer, BUFSIZE - strm.avail_out);
	off += BUFSIZE - strm.avail_out;
	deflateEnd(&strm);
    free(temp_buffer);

    android_string_cstrl(output, (char *)buf, off);
    free(buf);
}

bool leveldb_zlib_decompress(void *__this, const char *input, unsigned int length, android_string_t *output) {
    size_t CHUNK = 64 * 1024;
    uint8_t *out, *buf;
	int ret;
	size_t have;
	z_stream strm;
    size_t off = 0;
    
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = (uint32_t)length;
	strm.next_in = (Bytef*)input;
	ret = inflateInit(&strm);
	if (ret != Z_OK) {
		return false;
    }
    out = (uint8_t *)malloc(CHUNK);
    buf = NULL;

	do {
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);
			switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
                free(out);
                if (buf) {
                    free(buf);
                }
				return false;
			}
			have = CHUNK - strm.avail_out;
            if (!buf) {
                buf = (uint8_t *)malloc(have);
            } else {
                buf = (uint8_t *)realloc(buf, off + have);
            }
			memcpy(&buf[off], out, have);
            off += have;
		} while (strm.avail_out == 0);
	} while (ret != Z_STREAM_END);
	(void)inflateEnd(&strm);
    android_string_cstrl(output, (char *)buf, off);
    free(buf);
    free(out);
	return ret == Z_STREAM_END ? true : false;
}

int64_t _size(android_string_t *path) {
    puts(android_string_to_str(path));
    struct stat statbuf;
    if (!stat(android_string_to_str(path), &statbuf)) {
        return statbuf.st_size;
    }
    return 0;
}

int main(int argc, char **argv) {
    android_linker_init();
    static struct stat st = {0};
    if (stat("storage", &st) == -1) {
        mkdir("storage", 0700);
        if (stat("storage/games", &st) == -1) {
            mkdir("storage/games", 0700);
            if (stat("storage/games/com.mojang", &st) == -1) {
                mkdir("storage/games/com.mojang", 0700);
                if (stat("storage/games/com.mojang/minecraftpe", &st) == -1) {
                    mkdir("storage/games/com.mojang/minecraftpe", 0700);
                }
            }
        }
    }
    if (stat("mods", &st) == -1) {
        mkdir("mods", 0700);
    }

    ninecraft_read_options_file(&platform_options, "options.txt");
    ninecraft_set_default_options(&platform_options, "options.txt");

    if (!glfwInit()) {
        puts("init failed");
        return 1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    _window = glfwCreateWindow(720, 480, "Ninecraft", NULL, NULL);
    if (!_window) {
        puts("Cant create window");
        return 1;
    }
    GLFWimage icon;
    icon.pixels = stbi_load("./res/drawable/iconx.png", &icon.width, &icon.height, NULL, STBI_rgb_alpha);
    glfwSetWindowIcon(_window, 1, &icon);
    stbi_image_free(icon.pixels);

    glfwSetKeyCallback(_window, key_callback);
    glfwSetCharCallback(_window, char_callback);
    glfwSetMouseButtonCallback(_window, mouse_click_callback);
    glfwSetScrollCallback(_window, mouse_scroll_callback);
    glfwSetCursorPosCallback(_window, mouse_pos_callback);
    glfwSetWindowSizeCallback(_window, resize_callback);
    glfwSetWindowCloseCallback(_window, window_close_callback);

    glfwMakeContextCurrent(_window);

    gladLoadGL(glfwGetProcAddress);

    audio_engine_init();

    gles_hook();
    missing_hook();
    add_custom_hook("__android_log_print", (void *)__android_log_print);
    stub_symbols(android_symbols, (void *)android_stub);
    stub_symbols(egl_symbols, (void *)egl_stub);

    add_custom_hook("SL_IID_VOLUME", &sles_iid_volume);
    add_custom_hook("SL_IID_ENGINE", &sles_iid_engine);
    add_custom_hook("SL_IID_BUFFERQUEUE", &sles_iid_bufferqueue);
    add_custom_hook("SL_IID_PLAY", &sles_iid_play);
    add_custom_hook("slCreateEngine", sles_create_engine);

    struct soinfo *so_liblog = android_library_create("liblog.so");
    struct soinfo *so_libgles = android_library_create("libGLESv1_CM.so");
    struct soinfo *so_libgles2 = android_library_create("libGLESv2.so");
    struct soinfo *so_libegl = android_library_create("libEGL.so");
    struct soinfo *so_libandroid = android_library_create("libandroid.so");
    struct soinfo *so_libopensles = android_library_create("libOpenSLES.so");
    struct soinfo *so_libz = android_library_create("libz.so");

    handle = load_library("libminecraftpe.so");

    if (!handle) {
        puts("libminecraftpe.so not loaded");
        return 1;
    }
    
    android_alloc_setup_hooks(handle);

    static android_string_t in;
    android_string_cstr(&in, "v%d.%d.%d alpha");
    void (*get_game_version_string)(android_string_t *, android_string_t *) = (void (*)(android_string_t *, android_string_t *))android_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs");
    void (*get_game_version_string_2)(android_string_t *) = (void (*)(android_string_t *))android_dlsym(handle, "_ZN6Common20getGameVersionStringEv");
    if (get_game_version_string != NULL) {
        static android_string_t game_version;
#if defined(__i386__) || defined(_M_IX86)
        sysv_call_func(get_game_version_string, &game_version, 1, &in);
#else
        get_game_version_string(&game_version, &in);
#endif
        char *verstr = android_string_to_str(&game_version);

        bool is_j = android_dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnCreate") != NULL;

        printf("Ninecraft is running mcpe %.6s%s\n", verstr, is_j ? "j" : "");

        if (strncmp(verstr, "v0.2.1", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_2_1_j;
            } else {
                version_id = version_id_0_2_1;
            }
        } else if (strncmp(verstr, "v0.2.2", 6) == 0) {
            version_id = version_id_0_2_2;
        } else if (strncmp(verstr, "v0.3.0", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_3_0_j;
            } else {
                version_id = version_id_0_3_0;
            }
        } else if (strncmp(verstr, "v0.3.2", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_3_2_j;
            } else {
                version_id = version_id_0_3_2;
            }
        } else if (strncmp(verstr, "v0.3.3", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_3_3_j;
            } else {
                version_id = version_id_0_3_3;
            }
        } else if (strncmp(verstr, "v0.4.0", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_4_0_j;
            } else {
                version_id = version_id_0_4_0;
            }
        } else if (strncmp(verstr, "v0.5.0", 6) == 0) {
            if (is_j) {
                version_id = version_id_0_5_0_j;
            } else {
                version_id = version_id_0_5_0;
            }
        } else if (strncmp(verstr, "v0.6.0", 6) == 0) {
            version_id = version_id_0_6_0;
        } else if (strncmp(verstr, "v0.6.1", 6) == 0) {
            version_id = version_id_0_6_1;
        } else if (strncmp(verstr, "v0.7.0", 6) == 0) {
            version_id = version_id_0_7_0;
        } else if (strncmp(verstr, "v0.7.1", 6) == 0) {
            version_id = version_id_0_7_1;
        } else if (strncmp(verstr, "v0.7.2", 6) == 0) {
            version_id = version_id_0_7_2;
        } else if (strncmp(verstr, "v0.7.3", 6) == 0) {
            version_id = version_id_0_7_3;
        } else if (strncmp(verstr, "v0.7.4", 6) == 0) {
            version_id = version_id_0_7_4;
        } else if (strncmp(verstr, "v0.7.5", 6) == 0) {
            version_id = version_id_0_7_5;
        } else if (strncmp(verstr, "v0.7.6", 6) == 0) {
            version_id = version_id_0_7_6;
        } else {
            puts("Unsupported Version!");
            return 1;
        }
    } else if (get_game_version_string_2 != NULL) {
        static android_string_t game_version;
#if defined(__i386__) || defined(_M_IX86)
        sysv_call_func(get_game_version_string_2, &game_version, 0);
#else
        get_game_version_string_2(&game_version);
#endif
        char *verstr = android_string_to_str(&game_version);
        printf("Ninecraft is running mcpe %s\n", verstr);
        if (strcmp(verstr, "v0.8.0 alpha") == 0) {
            version_id = version_id_0_8_0;
        } else if (strcmp(verstr, "v0.8.1 alpha") == 0) {
            version_id = version_id_0_8_1;
        } else if (strcmp(verstr, "v0.9.0 alpha") == 0) {
            version_id = version_id_0_9_0;
        } else if (strcmp(verstr, "v0.9.1 alpha") == 0) {
            version_id = version_id_0_9_1;
        } else if (strcmp(verstr, "v0.9.2 alpha") == 0) {
            version_id = version_id_0_9_2;
        } else if (strcmp(verstr, "v0.9.3 alpha") == 0) {
            version_id = version_id_0_9_3;
        } else if (strcmp(verstr, "v0.9.4 alpha") == 0) {
            version_id = version_id_0_9_4;
        } else if (strcmp(verstr, "v0.9.5 alpha") == 0) {
            version_id = version_id_0_9_5;
        } else if (strcmp(verstr, "v0.10.0 alpha") == 0) {
            version_id = version_id_0_10_0;
        } else if (strcmp(verstr, "v0.10.1 alpha") == 0) {
            version_id = version_id_0_10_1;
        } else if (strcmp(verstr, "v0.10.2 alpha") == 0) {
            version_id = version_id_0_10_2;
        } else if (strcmp(verstr, "v0.10.3 alpha") == 0) {
            version_id = version_id_0_10_3;
        } else if (strcmp(verstr, "v0.10.4 alpha") == 0) {
            version_id = version_id_0_10_4;
        } else if (strcmp(verstr, "v0.10.5 alpha") == 0) {
            version_id = version_id_0_10_5;
        } else if (strcmp(verstr, "v0.11.0 alpha") == 0) {
            version_id = version_id_0_11_0;
        } else {
            puts("Unsupported Version!");
            return 1;
        }
    } else {
        android_Dl_info info;
        android_dladdr(android_dlsym(handle, "_ZN12NinecraftAppC2Ev"), &info);
        if (strncmp((char *)info.dli_fbase + 0x15d3a8, "v0.2.0", 6) == 0) { // v0.2.0
            version_id = version_id_0_2_0;
        } else if (strncmp((char *)info.dli_fbase + 0x15a480, "v0.2.0", 6) == 0) { // v0.2.0-demo
            version_id = version_id_0_2_0;
        } else if (strncmp((char *)info.dli_fbase + 0x1574f8, "v0.2.0", 6) == 0) { // v0.2.0j
            version_id = version_id_0_2_0_j;
        } else if (strncmp((char *)info.dli_fbase + 0x1545d8, "v0.2.0", 6) == 0) { // v0.2.0j-demo
            version_id = version_id_0_2_0_j;
        } else if (strncmp((char *)info.dli_fbase + 0xfca6c, "v0.1.3", 6) == 0) { // v0.1.3-2
            version_id = version_id_0_1_3;
        } else if (strncmp((char *)info.dli_fbase + 0xfca2c, "v0.1.3", 6) == 0) { // v0.1.3-1
            version_id = version_id_0_1_3;
        } else if (strncmp((char *)info.dli_fbase + 0xfae24, "v0.1.3", 6) == 0) { // v0.1.3-2-demo
            version_id = version_id_0_1_3;
        } else if (strncmp((char *)info.dli_fbase + 0xfade4, "v0.1.3", 6) == 0) { // v0.1.3-1-demo
            version_id = version_id_0_1_3;
        } else if (strncmp((char *)info.dli_fbase + 0x19d910, "v0.1.3", 6) == 0) { // v0.1.3j
            version_id = version_id_0_1_3_j;
        } else if (strncmp((char *)info.dli_fbase + 0x19a320, "v0.1.3", 6) == 0) { // v0.1.3j-demo
            version_id = version_id_0_1_3_j;
        } else if (strncmp((char *)info.dli_fbase + 0xf799c, "v0.1.2", 6) == 0) { // v0.1.2
            version_id = version_id_0_1_2;
        } else if (strncmp((char *)info.dli_fbase + 0xf5dc8, "v0.1.2", 6) == 0) { // v0.1.2-demo
            version_id = version_id_0_1_2;
        } else if (strncmp((char *)info.dli_fbase + 0x1966c0, "v0.1.2", 6) == 0) { // v0.1.2j
            version_id = version_id_0_1_2_j;
        } else if (strncmp((char *)info.dli_fbase + 0x193128, "v0.1.2", 6) == 0) { // v0.1.2j-demo
            version_id = version_id_0_1_2_j;
        } else if (strncmp((char *)info.dli_fbase + 0xf6d30, "v0.1.1", 6) == 0) { // v0.1.1
            version_id = version_id_0_1_1;
        } else if (strncmp((char *)info.dli_fbase + 0xf5154, "v0.1.1", 6) == 0) { // v0.1.1-demo
            version_id = version_id_0_1_1;
        } else if (strncmp((char *)info.dli_fbase + 0x19557c, "v0.1.1", 6) == 0) { // v0.1.1j
            version_id = version_id_0_1_1_j;
        } else if (strncmp((char *)info.dli_fbase + 0x191ce4, "v0.1.1", 6) == 0) { // v0.1.1j-demo
            version_id = version_id_0_1_1_j;
        } else if (strncmp((char *)info.dli_fbase + 0x119c64, "v0.1.0", 6) == 0) { // v0.1.0-touch
            version_id = version_id_0_1_0_touch;
        } else if (strncmp((char *)info.dli_fbase + 0x131480, "v0.1.0", 6) == 0) { // v0.1.0
            version_id = version_id_0_1_0;
        } else if (strncmp((char *)info.dli_fbase + 0x12f938, "v0.1.0", 6) == 0) { // v0.1.0-demo-canada
            version_id = version_id_0_1_0;
        } else if (strncmp((char *)info.dli_fbase + 0x12f968, "v0.1.0", 6) == 0) { // v0.1.0-demo
            version_id = version_id_0_1_0;
        } else {
            puts("Unsupported Version!");
            return 1;
        }
    }
    android_string_destroy(&in);

    multitouch_setup_hooks(handle);
    keyboard_setup_hooks(handle);
    minecraft_setup_hooks(handle);
    inject_mods(handle, version_id);
    mod_loader_load_all(handle, version_id);

    if (version_id >= version_id_0_9_0) {
        void **zlib_compressor_vtable = (void **)android_dlsym(handle, "_ZTVN7leveldb14ZlibCompressorE");
        zlib_compressor_vtable[4] = leveldb_zlib_compress_impl;
        zlib_compressor_vtable[5] = leveldb_zlib_decompress;
    }

    controller_states = (unsigned char *)android_dlsym(handle, "_ZN10Controller15isTouchedValuesE");
    controller_x_stick = (float *)android_dlsym(handle, "_ZN10Controller12stickValuesXE");
    controller_y_stick = (float *)android_dlsym(handle, "_ZN10Controller12stickValuesYE");

    if (version_id >= version_id_0_6_0 && version_id <= version_id_0_9_5) {
        default_mouse_mode = GLFW_CURSOR_HIDDEN;
    }

    glfwSetInputMode(_window, GLFW_CURSOR, default_mouse_mode);

    if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
        printf("nine construct %p\n", ninecraft_app_construct_2);
    } else if (version_id >= version_id_0_10_0) {
        printf("nine construct %p\n", minecraft_client_construct);
    } else {
        printf("nine construct %p\n", ninecraft_app_construct);
    }

    size_t ninecraft_app_size;

    if (version_id == version_id_0_1_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_0;
    } else if (version_id == version_id_0_1_0_touch) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_0_TOUCH;
    } else if (version_id == version_id_0_1_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_1;
    } else if (version_id == version_id_0_1_1_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_1_J;
    } else if (version_id == version_id_0_1_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_2;
    } else if (version_id == version_id_0_1_2_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_2_J;
    } else if (version_id == version_id_0_1_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_3;
    } else if (version_id == version_id_0_1_3_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_3_J;
    } else if (version_id == version_id_0_2_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_0;
    } else if (version_id == version_id_0_2_0_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_0_J;
    } else if (version_id == version_id_0_2_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_1;
    } else if (version_id == version_id_0_2_1_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_1_J;
    } else if (version_id == version_id_0_2_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_2;
    } else if (version_id == version_id_0_3_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_0;
    } else if (version_id == version_id_0_3_0_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_0_J;
    } else if (version_id == version_id_0_3_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_2;
    } else if (version_id == version_id_0_3_2_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_2_J;
    } else if (version_id == version_id_0_3_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_3;
    } else if (version_id == version_id_0_3_3_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_3_J;
    } else if (version_id == version_id_0_4_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_4_0;
    } else if (version_id == version_id_0_4_0_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_4_0_J;
    } else if (version_id == version_id_0_5_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_5_0;
    } else if (version_id == version_id_0_5_0_j) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_5_0_J;
    } else if (version_id == version_id_0_6_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_6_0;
    } else if (version_id == version_id_0_6_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_6_1;
    } else if (version_id == version_id_0_7_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_0;
    } else if (version_id == version_id_0_7_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_1;
    } else if (version_id == version_id_0_7_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_2;
    } else if (version_id == version_id_0_7_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_3;
    } else if (version_id == version_id_0_7_4) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_4;
    } else if (version_id == version_id_0_7_5) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_5;
    } else if (version_id == version_id_0_7_6) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_6;
    } else if (version_id == version_id_0_8_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_8_0;
    } else if (version_id == version_id_0_8_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_8_1;
    } else if (version_id == version_id_0_9_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_0;
    } else if (version_id == version_id_0_9_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_1;
    } else if (version_id == version_id_0_9_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_2;
    } else if (version_id == version_id_0_9_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_3;
    } else if (version_id == version_id_0_9_4) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_4;
    } else if (version_id == version_id_0_9_5) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_9_5;
    } else if (version_id == version_id_0_10_0) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_0;
    } else if (version_id == version_id_0_10_1) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_1;
    } else if (version_id == version_id_0_10_2) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_2;
    } else if (version_id == version_id_0_10_3) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_3;
    } else if (version_id == version_id_0_10_4) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_4;
    } else if (version_id == version_id_0_10_5) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_10_5;
    } else if (version_id == version_id_0_11_0) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_11_0;
    }
    ninecraft_app = malloc(ninecraft_app_size);
    if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
        ninecraft_app_construct_2(ninecraft_app, 0, NULL);
    } else if (version_id >= version_id_0_10_0) {
        minecraft_client_construct(ninecraft_app, 0, NULL);
    } else {
        ninecraft_app_construct(ninecraft_app);
    }

    char *storage_path = (char *)malloc(1024);
    storage_path[0] = '\0';
    getcwd(storage_path, 1024);
    strcat(storage_path, "/storage/");

    if (version_id <= version_id_0_10_5) {
        uintptr_t int_off = get_ninecraftapp_internal_storage_offset(version_id);
        uintptr_t ext_off = get_ninecraftapp_external_storage_offset(version_id);
        if (int_off) {
            android_string_equ((android_string_t *)((char *)ninecraft_app + int_off), storage_path);
        }
        if (ext_off) {
            android_string_equ((android_string_t *)((char *)ninecraft_app + ext_off), storage_path);
        }
    }

    mod_loader_execute_on_minecraft_construct(ninecraft_app, version_id);

    if (version_id >= version_id_0_9_0) {
        app_platform_0_9_0_t *plat = malloc(sizeof(app_platform_0_9_0_t));
        app_context_0_9_0_t *context = (app_context_0_9_0_t *)malloc(sizeof(app_context_0_9_0_t));
        context->egl_context = NULL;
        context->egl_display = NULL;
        context->egl_surface = NULL;
        context->u0 = NULL;
        context->platform = NULL;
        context->do_render = false;

        app_platform_construct(plat);
        if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
            memcpy(&platform_vtable_0_9_0, plat->vtable, sizeof(app_platform_vtable_0_9_0_t));
            plat->vtable = (void **)&platform_vtable_0_9_0;
            platform_vtable_0_9_0.getImagePath = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath);
            platform_vtable_0_9_0.loadPNG = (void *)AppPlatform_linux$loadPNG_0_9_0;
            platform_vtable_0_9_0.loadTGA = (void *)AppPlatform_linux$loadTGA_0_9_0;
            platform_vtable_0_9_0.getDateString = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString);
            platform_vtable_0_9_0.readAssetFile = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0);
            platform_vtable_0_9_0.getScreenHeight = (void *)AppPlatform_linux$getScreenHeight;
            platform_vtable_0_9_0.getScreenWidth = (void *)AppPlatform_linux$getScreenWidth;
            platform_vtable_0_9_0.showKeyboard = (void *)AppPlatform_linux$showKeyboard;
            platform_vtable_0_9_0.hideKeyboard = (void *)AppPlatform_linux$hideKeyboard;
            platform_vtable_0_9_0.getBroadcastAddresses = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses);
            platform_vtable_0_9_0.getAvailableMemory = (void *)AppPlatform_linux$getAvailableMemory;
            platform_vtable_0_9_0.getPlatformStringVar = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar);
            platform_vtable_0_9_0.getLoginInformation = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation);
            platform_vtable_0_9_0.setLoginInformation = (void *)AppPlatform_linux$setLoginInformation;
            platform_vtable_0_9_0.supportsTouchscreen = (void *)AppPlatform_linux$supportsTouchscreen;
            platform_vtable_0_9_0.isNetworkEnabled = (void *)AppPlatform_linux$isNetworkEnabled;
            platform_vtable_0_9_0.getPixelsPerMillimeter = (void *)AppPlatform_linux$getPixelsPerMillimeter;
        } else if (version_id >= version_id_0_10_0 && version_id <= version_id_0_10_5) {
            memcpy(&platform_vtable_0_10_0, plat->vtable, sizeof(app_platform_vtable_0_10_0_t));
            plat->vtable = (void **)&platform_vtable_0_10_0;
            platform_vtable_0_10_0.getImagePath = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath);
            platform_vtable_0_10_0.loadPNG = (void *)AppPlatform_linux$loadPNG_0_9_0;
            platform_vtable_0_10_0.loadTGA = (void *)AppPlatform_linux$loadTGA_0_9_0;
            platform_vtable_0_10_0.getDateString = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString);
            platform_vtable_0_10_0.readAssetFile = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0);
            platform_vtable_0_10_0.getScreenHeight = (void *)AppPlatform_linux$getScreenHeight;
            platform_vtable_0_10_0.getScreenWidth = (void *)AppPlatform_linux$getScreenWidth;
            platform_vtable_0_10_0.showKeyboard = (void *)AppPlatform_linux$showKeyboard;
            platform_vtable_0_10_0.hideKeyboard = (void *)AppPlatform_linux$hideKeyboard;
            platform_vtable_0_10_0.getBroadcastAddresses = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses);
            platform_vtable_0_10_0.getAvailableMemory = (void *)AppPlatform_linux$getAvailableMemory;
            platform_vtable_0_10_0.getPlatformStringVar = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar);
            platform_vtable_0_10_0.getLoginInformation = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation);
            platform_vtable_0_10_0.setLoginInformation = (void *)AppPlatform_linux$setLoginInformation;
            platform_vtable_0_10_0.supportsTouchscreen = (void *)AppPlatform_linux$supportsTouchscreen;
            platform_vtable_0_10_0.isNetworkEnabled = (void *)AppPlatform_linux$isNetworkEnabled;
            platform_vtable_0_10_0.getPixelsPerMillimeter = (void *)AppPlatform_linux$getPixelsPerMillimeter;
            platform_vtable_0_10_0.swapBuffers = (void *)AppPlatform_linux$swapBuffers;
        } else if (version_id == version_id_0_11_0) {
            memcpy(&platform_vtable_0_11_0, plat->vtable, sizeof(app_platform_vtable_0_11_0_t));
            plat->vtable = (void **)&platform_vtable_0_11_0;
            platform_vtable_0_11_0.getImagePath = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getImagePath);
            platform_vtable_0_11_0.loadPNG = (void *)AppPlatform_linux$loadPNG_0_9_0;
            platform_vtable_0_11_0.loadTGA = (void *)AppPlatform_linux$loadTGA_0_9_0;
            platform_vtable_0_11_0.getDateString = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDateString);
            platform_vtable_0_11_0.readAssetFile = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$readAssetFile_0_9_0);
            platform_vtable_0_11_0.getScreenHeight = (void *)AppPlatform_linux$getScreenHeight;
            platform_vtable_0_11_0.getScreenWidth = (void *)AppPlatform_linux$getScreenWidth;
            platform_vtable_0_11_0.showKeyboard = (void *)AppPlatform_linux$showKeyboard;
            platform_vtable_0_11_0.hideKeyboard = (void *)AppPlatform_linux$hideKeyboard;
            platform_vtable_0_11_0.getBroadcastAddresses = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getBroadcastAddresses);
            platform_vtable_0_11_0.getAvailableMemory = (void *)AppPlatform_linux$getAvailableMemory;
            platform_vtable_0_11_0.getPlatformStringVar = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getPlatformStringVar);
            platform_vtable_0_11_0.getLoginInformation = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getLoginInformation);
            platform_vtable_0_11_0.setLoginInformation = (void *)AppPlatform_linux$setLoginInformation;
            platform_vtable_0_11_0.supportsTouchscreen = (void *)AppPlatform_linux$supportsTouchscreen;
            platform_vtable_0_11_0.isNetworkEnabled = (void *)AppPlatform_linux$isNetworkEnabled;
            platform_vtable_0_11_0.getPixelsPerMillimeter = (void *)AppPlatform_linux$getPixelsPerMillimeter;
            platform_vtable_0_11_0.swapBuffers = (void *)AppPlatform_linux$swapBuffers;
            platform_vtable_0_11_0.getSystemRegion = (void *)AppPlatform_linux$getSystemRegion;
            platform_vtable_0_11_0.getGraphicsVendor = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getGraphicsVendor);
            platform_vtable_0_11_0.getGraphicsRenderer = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getGraphicsRenderer);
            platform_vtable_0_11_0.getGraphicsVersion = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getGraphicsVersion);
            platform_vtable_0_11_0.getGraphicsExtensions = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getGraphicsExtensions);
            platform_vtable_0_11_0.getExternalStoragePath = (void *)AppPlatform_linux$getExternalStoragePath;
            platform_vtable_0_11_0.getInternalStoragePath = (void *)AppPlatform_linux$getInternalStoragePath;
            platform_vtable_0_11_0.getApplicationId = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getApplicationId);
            platform_vtable_0_11_0.getDeviceId = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$getDeviceId);
            platform_vtable_0_11_0.createUUID = (void *)GET_SYSV_WRAPPER(AppPlatform_linux$createUUID);
            platform_vtable_0_11_0.isFirstSnoopLaunch = (void *)AppPlatform_linux$isFirstSnoopLaunch;
            platform_vtable_0_11_0.hasHardwareInformationChanged = (void *)AppPlatform_linux$hasHardwareInformationChanged;
            platform_vtable_0_11_0.isTablet = (void *)AppPlatform_linux$isTablet;
            platform_vtable_0_11_0.pickImage = (void *)AppPlatform_linux$pickImage;

            DETOUR(android_dlsym(handle, "_ZN26HTTPRequestInternalAndroidC2ER11HTTPRequest"), ninecraft_http_construct, 1);
            DETOUR(android_dlsym(handle, "_ZN26HTTPRequestInternalAndroid4sendEv"), ninecraft_http_send, 1);
            DETOUR(android_dlsym(handle, "_ZN26HTTPRequestInternalAndroid5abortEv"), ninecraft_http_abort, 1);
            DETOUR(android_dlsym(handle, "_ZN12StoreFactory11createStoreER13StoreListener"), GET_SYSV_WRAPPER(ninecraft_store_create), 1);
            DETOUR(android_dlsym(handle, "_Z5_sizeRKSs"), _size, 1);
            
            
            
        }
        context->platform = plat;
        app_init(ninecraft_app, context);
    } else {
        AppPlatform_linux$AppPlatform_linux(&platform, handle, version_id);
        printf("%p\n", &platform);

        *(void **)((char *)ninecraft_app + 0x08) = NULL;      // egl_display
        *(void **)((char *)ninecraft_app + 0x0c) = NULL;      // egl_content
        *(void **)((char *)ninecraft_app + 0x10) = NULL;      // egl_surface
        *(void **)((char *)ninecraft_app + 0x14) = &platform; // app_platform

        if (version_id >= version_id_0_1_0_touch) {
            *(uint8_t *)((char *)ninecraft_app + 0x18) = 0; // do_render
        }

        ninecraft_app_init(ninecraft_app);

        if (version_id >= version_id_0_1_0_touch) {
            *(uint8_t *)((char *)ninecraft_app + 4) = 1; // is_inited
        }
    }

    char *minecraft_options = minecraft_get_options(ninecraft_app, version_id);

    if (version_id >= version_id_0_5_0 && version_id <= version_id_0_11_0 && minecraft_options && minecraft_options != ninecraft_app) {
        if (version_id >= version_id_0_7_0 && options_set_key) {
            options_set_key((void *)minecraft_options, MCKEY_ID_SNEAK, MCKEY_SNEAK);
        } else if (version_id >= version_id_0_5_0 && version_id <= version_id_0_6_1) {
            int options_keys_offset = 0;
            if (version_id == version_id_0_5_0) {
                options_keys_offset = OPTIONS_KEYS_OFFSET_0_5_0;
            } else if (version_id == version_id_0_5_0_j) {
                options_keys_offset = OPTIONS_KEYS_OFFSET_0_5_0_J;
            } else if (version_id == version_id_0_6_0) {
                options_keys_offset = OPTIONS_KEYS_OFFSET_0_6_0;
            } else if (version_id == version_id_0_6_1) {
                options_keys_offset = OPTIONS_KEYS_OFFSET_0_6_1;
            }
            if (options_keys_offset) {
                void **options_keys = (void **)(minecraft_options + options_keys_offset);
                *(int *)((char *)options_keys[MCKEY_ID_SNEAK] + android_string_tsize()) = MCKEY_SNEAK;
            }
        }
    }

    mod_loader_execute_on_minecraft_init(ninecraft_app, version_id);

    if (version_id >= version_id_0_1_0_touch) {
        set_ninecraft_size(720, 480);
    } else {
        set_ninecraft_size_0_1_0(720, 480);
    }

    size_t minecraft_isgrabbed_offset;
    if (version_id == version_id_0_11_0) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_11_0;
    } else if (version_id == version_id_0_10_5) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_5;
    } else if (version_id == version_id_0_10_4) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_4;
    } else if (version_id == version_id_0_10_3) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_3;
    } else if (version_id == version_id_0_10_2) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_2;
    } else if (version_id == version_id_0_10_1) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_1;
    } else if (version_id == version_id_0_10_0) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_10_0;
    } else if (version_id == version_id_0_9_5) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_5;
    } else if (version_id == version_id_0_9_4) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_4;
    } else if (version_id == version_id_0_9_3) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_3;
    } else if (version_id == version_id_0_9_2) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_2;
    } else if (version_id == version_id_0_9_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_1;
    } else if (version_id == version_id_0_9_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_9_0;
    } else if (version_id == version_id_0_8_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_8_1;
    } else if (version_id == version_id_0_8_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_8_0;
    } else if (version_id == version_id_0_7_6) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_6;
    } else if (version_id == version_id_0_7_5) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_5;
    } else if (version_id == version_id_0_7_4) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_4;
    } else if (version_id == version_id_0_7_3) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_3;
    } else if (version_id == version_id_0_7_2) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_2;
    } else if (version_id == version_id_0_7_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_1;
    } else if (version_id == version_id_0_7_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_0;
    } else if (version_id == version_id_0_6_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_6_1;
    } else if (version_id == version_id_0_6_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_6_0;
    } else if (version_id == version_id_0_5_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_5_0;
    } else if (version_id == version_id_0_5_0_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_5_0_J;
    } else if (version_id == version_id_0_4_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_4_0;
    } else if (version_id == version_id_0_4_0_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_4_0_J;
    } else if (version_id == version_id_0_3_3) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_3;
    } else if (version_id == version_id_0_3_3_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_3_J;
    } else if (version_id == version_id_0_3_2) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_2;
    } else if (version_id == version_id_0_3_2_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_2_J;
    } else if (version_id == version_id_0_3_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_0;
    } else if (version_id == version_id_0_3_0_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_0_J;
    } else if (version_id == version_id_0_2_2) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_2;
    } else if (version_id == version_id_0_2_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_1;
    } else if (version_id == version_id_0_2_1_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_1_J;
    } else if (version_id == version_id_0_2_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_0;
    } else if (version_id == version_id_0_2_0_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_0_J;
    } else if (version_id == version_id_0_1_3) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_3;
    } else if (version_id == version_id_0_1_3_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_3_J;
    } else if (version_id == version_id_0_1_2) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_2;
    } else if (version_id == version_id_0_1_2_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_2_J;
    } else if (version_id == version_id_0_1_1) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_1;
    } else if (version_id == version_id_0_1_1_j) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_1_J;
    } else if (version_id == version_id_0_1_0_touch) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_0_TOUCH;
    } else if (version_id == version_id_0_1_0) {
        minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_0;
    }
    
    while (true) {
        if (((bool *)ninecraft_app)[minecraft_isgrabbed_offset]) {
            if (!mouse_pointer_hidden) {
                grab_mouse();
            }
        } else {
            if (mouse_pointer_hidden) {
                release_mouse();
            }
        }
        if (version_id >= version_id_0_6_0 && version_id <= version_id_0_8_1) {
            if (minecraft_is_level_generated(ninecraft_app)) {
                if (!mcpi_api_initialized) {
                    puts("MCPI-API initialized");
                    piapi_init();
                    mcpi_api_initialized = 1;
                }
            } else {
                mcpi_api_initialized = 0;
            }
        }
        if (mouse_pointer_hidden) {
            if (controller_states && controller_y_stick && controller_x_stick && version_id <= version_id_0_5_0_j) {
                controller_states[1] = 1;
                controller_y_stick[1] = (float)(y_cam - 180.0) * 0.0055555557;
                controller_x_stick[1] = ((float)((x_cam - 483.0)) * 0.0020703934);
            }
        }

        if (version_id >= version_id_0_10_0) {
            minecraft_update(ninecraft_app);
        } else {
            ninecraft_app_update(ninecraft_app);
        }
        mod_loader_execute_on_minecraft_update(ninecraft_app, version_id);

        if (!mouse_pointer_hidden) {
            if (version_id >= version_id_0_6_0 && version_id <= version_id_0_9_5) {
                float inv_gui_scale = *((float *)android_dlsym(handle, "_ZN3Gui11InvGuiScaleE"));
                double xpos, ypos;
                glfwGetCursorPos(_window, &xpos, &ypos);
                short cx = (short)(xpos * inv_gui_scale);
                short cy = (short)(ypos * inv_gui_scale);
                ((FLOAT_ABI_FIX void (*)(float, float, void *))android_dlsym(handle, "_Z12renderCursorffP9Minecraft"))(cx, cy, ninecraft_app);
            }
        }
        audio_engine_tick();
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    return 0;
}
