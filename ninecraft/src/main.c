#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
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
#include <SDL.h>
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
#include <ninecraft/android/android_keycodes.h>
#include <ninecraft/game_parameters.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void *handle = NULL;
struct SDL_Window *_window = NULL;
bool ctrl_pressed = false;
bool is_fullscreen = false;

int default_mouse_mode = SDL_ENABLE;

int version_id = 0;

void *ninecraft_app;
AppPlatform_linux platform;

static unsigned char *controller_states;
static float *controller_x_stick;
static float *controller_y_stick;

bool mouse_pointer_hidden = false;

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
    strcat(fullpath, game_parameters.game_path);
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
    if (keyCode == SDL_BUTTON_LEFT) {
        return MCKEY_DESTROY;
    } else if (keyCode == SDL_BUTTON_RIGHT) {
        return MCKEY_USE;
    }
    return 0;
}

static void mouse_click_callback(struct SDL_Window *window, int button, int action, int x, int y) {
    if (!mouse_pointer_hidden) {
        int mc_button = (button == SDL_BUTTON_LEFT ? 1 : (button == SDL_BUTTON_RIGHT ? 2 : 0));
        if (version_id == version_id_0_1_0) {
            ((void (*)(int, int, int, int))android_dlsym(handle, "_ZN5Mouse4feedEiiii"))((int)mc_button, (int)(action == SDL_PRESSED ? 1 : 0), (int)x, (int)y0);
        } else if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(android_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y, 0, 0);
            multitouch_feed_0_6((char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y, 0);
        } else if (version_id <= version_id_0_5_0_j && version_id >= version_id_0_2_1) {
            mouse_device_feed_0_2_1(android_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y);
            multitouch_feed_0_2_1((char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y, 0);
        } else if (version_id <= version_id_0_2_0_j && version_id >= version_id_0_1_0_touch) {
            mouse_device_feed_0_1(android_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y);
            multitouch_feed_0_1((char)mc_button, (char)(action == SDL_PRESSED ? 1 : 0), (short)x, (short)y, 0);
        }
    } else {
        int game_keycode = mouseToGameKeyCode(button);

        if (action == SDL_PRESSED) {
            keyboard_feed(game_keycode, 1);
        } else if (action == SDL_RELEASED) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

static void mouse_scroll_callback(struct SDL_Window *window, float xoffset, float yoffset, int direction) {
    char key_code = 0;
    float offset = (direction == SDL_MOUSEWHEEL_NORMAL) ? yoffset : xoffset;

    if (offset > 0) {
        key_code = MCKEY_MENU_PREVIOUS;
    } else if (offset < 0) {
        key_code = MCKEY_MENU_NEXT;
    }
    keyboard_feed(key_code, 1);
    keyboard_feed(key_code, 0);
}

static void mouse_pos_callback(struct SDL_Window *window, int xpos, int ypos, int xrel, int yrel) {
    if (!mouse_pointer_hidden || version_id >= version_id_0_6_0) {
        if (version_id == version_id_0_1_0) {
            ((void (*)(int, int, int, int))android_dlsym(handle, "_ZN5Mouse4feedEiiii"))(0, 0, (int)xpos, (int)ypos);
        } else if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(android_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos, (short)xrel, (short)yrel);
            multitouch_feed_0_6(0, 0, (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_5_0_j && version_id >= version_id_0_2_1) {
            mouse_device_feed_0_2_1(android_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos);
            multitouch_feed_0_2_1(0, 0, (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_2_0_j && version_id >= version_id_0_1_0_touch) {
            mouse_device_feed_0_1(android_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos);
            multitouch_feed_0_1(0, 0, (short)xpos, (short)ypos, 0);
        }
    } else {
        if (controller_states && controller_y_stick && controller_x_stick && version_id <= version_id_0_5_0_j) {
            controller_states[1] = 1;
            controller_x_stick[1] += (float)xrel * 0.003;
            controller_y_stick[1] -= (float)yrel * 0.003;
        }
    }
}

int sdl_to_android_key(int keycode) {
    if (keycode == SDLK_0) {
        return AKEYCODE_0;
    }
    if (keycode == SDLK_1) {
        return AKEYCODE_1;
    }
    if (keycode == SDLK_2) {
        return AKEYCODE_2;
    }
    if (keycode == SDLK_3) {
        return AKEYCODE_3;
    }
    if (keycode == SDLK_4) {
        return AKEYCODE_4;
    }
    if (keycode == SDLK_5) {
        return AKEYCODE_5;
    }
    if (keycode == SDLK_6) {
        return AKEYCODE_6;
    }
    if (keycode == SDLK_7) {
        return AKEYCODE_7;
    }
    if (keycode == SDLK_8) {
        return AKEYCODE_8;
    }
    if (keycode == SDLK_9) {
        return AKEYCODE_9;
    }
    if (keycode == SDLK_a) {
        return AKEYCODE_A;
    }
    if (keycode == SDLK_b) {
        return AKEYCODE_B;
    }
    if (keycode == SDLK_c) {
        return AKEYCODE_C;
    }
    if (keycode == SDLK_d) {
        return AKEYCODE_D;
    }
    if (keycode == SDLK_e) {
        return AKEYCODE_E;
    }
    if (keycode == SDLK_f) {
        return AKEYCODE_F;
    }
    if (keycode == SDLK_g) {
        return AKEYCODE_G;
    }
    if (keycode == SDLK_h) {
        return AKEYCODE_H;
    }
    if (keycode == SDLK_i) {
        return AKEYCODE_I;
    }
    if (keycode == SDLK_j) {
        return AKEYCODE_J;
    }
    if (keycode == SDLK_k) {
        return AKEYCODE_K;
    }
    if (keycode == SDLK_l) {
        return AKEYCODE_L;
    }
    if (keycode == SDLK_m) {
        return AKEYCODE_M;
    }
    if (keycode == SDLK_n) {
        return AKEYCODE_N;
    }
    if (keycode == SDLK_o) {
        return AKEYCODE_O;
    }
    if (keycode == SDLK_p) {
        return AKEYCODE_P;
    }
    if (keycode == SDLK_q) {
        return AKEYCODE_Q;
    }
    if (keycode == SDLK_r) {
        return AKEYCODE_R;
    }
    if (keycode == SDLK_s) {
        return AKEYCODE_S;
    }
    if (keycode == SDLK_t) {
        return AKEYCODE_T;
    }
    if (keycode == SDLK_u) {
        return AKEYCODE_U;
    }
    if (keycode == SDLK_v) {
        return AKEYCODE_V;
    }
    if (keycode == SDLK_w) {
        return AKEYCODE_W;
    }
    if (keycode == SDLK_x) {
        return AKEYCODE_X;
    }
    if (keycode == SDLK_y) {
        return AKEYCODE_Y;
    }
    if (keycode == SDLK_z) {
        return AKEYCODE_Z;
    }
    if (keycode == SDLK_COMMA) {
        return AKEYCODE_COMMA;
    }
    if (keycode == SDLK_PERIOD) {
        return AKEYCODE_PERIOD;
    }
    if (keycode == SDLK_LALT) {
        return AKEYCODE_ALT_LEFT;
    }
    if (keycode == SDLK_RALT) {
        return AKEYCODE_ALT_RIGHT;
    }
    if (keycode == SDLK_LSHIFT) {
        return AKEYCODE_SHIFT_LEFT;
    }
    if (keycode == SDLK_RSHIFT) {
        return AKEYCODE_SHIFT_RIGHT;
    }
    if (keycode == SDLK_TAB) {
        return AKEYCODE_TAB;
    }
    if (keycode == SDLK_SPACE) {
        return AKEYCODE_SPACE;
    }
    if (keycode == SDLK_RETURN) {
        return AKEYCODE_ENTER;
    }
    if (keycode == SDLK_BACKSPACE) {
        return AKEYCODE_DEL;
    }
    if (keycode == SDLK_DELETE) {
        return AKEYCODE_FORWARD_DEL;
    }
    if (keycode == SDLK_BACKQUOTE) {
        return AKEYCODE_GRAVE;
    }
    if (keycode == SDLK_MINUS) {
        return AKEYCODE_MINUS;
    }
    if (keycode == SDLK_EQUALS) {
        return AKEYCODE_EQUALS;
    }
    if (keycode == SDLK_LEFTBRACKET) {
        return AKEYCODE_LEFT_BRACKET;
    }
    if (keycode == SDLK_RIGHTBRACKET) {
        return AKEYCODE_RIGHT_BRACKET;
    }
    if (keycode == SDLK_BACKSLASH) {
        return AKEYCODE_BACKSLASH;
    }
    if (keycode == SDLK_SEMICOLON) {
        return AKEYCODE_SEMICOLON;
    }
    if (keycode == SDLK_QUOTE) {
        return AKEYCODE_APOSTROPHE;
    }
    if (keycode == SDLK_SLASH) {
        return AKEYCODE_SLASH;
    }
    if (keycode == SDLK_LCTRL) {
        return AKEYCODE_CTRL_LEFT;
    }
    if (keycode == SDLK_RCTRL) {
        return AKEYCODE_CTRL_RIGHT;
    }
    if (keycode == SDLK_CAPSLOCK) {
        return AKEYCODE_CAPS_LOCK;
    }
    if (keycode == SDLK_SYSREQ) {
        return AKEYCODE_SYSRQ;
    }
    if (keycode == SDLK_PAUSE) {
        return AKEYCODE_BREAK;
    }
    if (keycode == SDLK_HOME) {
        return AKEYCODE_MOVE_HOME;
    }
    if (keycode == SDLK_END) {
        return AKEYCODE_MOVE_END;
    }
    if (keycode == SDLK_INSERT) {
        return AKEYCODE_INSERT;
    }
    if (keycode == SDLK_SCROLLLOCK) {
        return AKEYCODE_SCROLL_LOCK;
    }
    if (keycode == SDLK_PAGEUP) {
        return AKEYCODE_PAGE_UP;
    }
    if (keycode == SDLK_PAGEDOWN) {
        return AKEYCODE_PAGE_DOWN;
    }
    if (keycode == SDLK_F1) {
        return AKEYCODE_F1;
    }
    if (keycode == SDLK_F2) {
        return AKEYCODE_F2;
    }
    if (keycode == SDLK_F3) {
        return AKEYCODE_F3;
    }
    if (keycode == SDLK_F4) {
        return AKEYCODE_F4;
    }
    if (keycode == SDLK_F5) {
        return AKEYCODE_F5;
    }
    if (keycode == SDLK_F6) {
        return AKEYCODE_F6;
    }
    if (keycode == SDLK_F7) {
        return AKEYCODE_F7;
    }
    if (keycode == SDLK_F8) {
        return AKEYCODE_F8;
    }
    if (keycode == SDLK_F9) {
        return AKEYCODE_F9;
    }
    if (keycode == SDLK_F10) {
        return AKEYCODE_F10;
    }
    if (keycode == SDLK_F11) {
        return AKEYCODE_F11;
    }
    if (keycode == SDLK_F12) {
        return AKEYCODE_F12;
    }
    if (keycode == SDLK_F13) {
        return AKEYCODE_F13;
    }
    if (keycode == SDLK_F14) {
        return AKEYCODE_F14;
    }
    if (keycode == SDLK_F15) {
        return AKEYCODE_F15;
    }
    if (keycode == SDLK_F16) {
        return AKEYCODE_F16;
    }
    if (keycode == SDLK_F17) {
        return AKEYCODE_F17;
    }
    if (keycode == SDLK_F18) {
        return AKEYCODE_F18;
    }
    if (keycode == SDLK_F19) {
        return AKEYCODE_F19;
    }
    if (keycode == SDLK_F20) {
        return AKEYCODE_F20;
    }
    if (keycode == SDLK_F21) {
        return AKEYCODE_F21;
    }
    if (keycode == SDLK_F22) {
        return AKEYCODE_F22;
    }
    if (keycode == SDLK_F23) {
        return AKEYCODE_F23;
    }
    if (keycode == SDLK_F24) {
        return AKEYCODE_F24;
    }
    if (keycode == SDLK_ESCAPE) {
        return AKEYCODE_ESCAPE;
    }
    if (keycode == SDLK_UP) {
        return AKEYCODE_DPAD_UP;
    }
    if (keycode == SDLK_DOWN) {
        return AKEYCODE_DPAD_DOWN;
    }
    if (keycode == SDLK_LEFT) {
        return AKEYCODE_DPAD_LEFT;
    }
    if (keycode == SDLK_RIGHT) {
        return AKEYCODE_DPAD_RIGHT;
    }
    if (keycode == SDLK_MENU) {
        return AKEYCODE_MENU;
    }
    if (keycode == SDLK_LGUI) {
        return AKEYCODE_META_LEFT;
    }
    if (keycode == SDLK_RGUI) {
        return AKEYCODE_META_RIGHT;
    }
    if (keycode == SDLK_NUMLOCKCLEAR) {
        return AKEYCODE_NUM_LOCK;
    }
    if (keycode == SDLK_KP_0) {
        return AKEYCODE_NUMPAD_0;
    }
    if (keycode == SDLK_KP_1) {
        return AKEYCODE_NUMPAD_1;
    }
    if (keycode == SDLK_KP_2) {
        return AKEYCODE_NUMPAD_2;
    }
    if (keycode == SDLK_KP_3) {
        return AKEYCODE_NUMPAD_3;
    }
    if (keycode == SDLK_KP_4) {
        return AKEYCODE_NUMPAD_4;
    }
    if (keycode == SDLK_KP_5) {
        return AKEYCODE_NUMPAD_5;
    }
    if (keycode == SDLK_KP_6) {
        return AKEYCODE_NUMPAD_6;
    }
    if (keycode == SDLK_KP_7) {
        return AKEYCODE_NUMPAD_7;
    }
    if (keycode == SDLK_KP_8) {
        return AKEYCODE_NUMPAD_8;
    }
    if (keycode == SDLK_KP_9) {
        return AKEYCODE_NUMPAD_9;
    }
    if (keycode == SDLK_KP_DIVIDE) {
        return AKEYCODE_NUMPAD_DIVIDE;
    }
    if (keycode == SDLK_KP_MULTIPLY) {
        return AKEYCODE_NUMPAD_MULTIPLY;
    }
    if (keycode == SDLK_KP_MINUS) {
        return AKEYCODE_NUMPAD_SUBTRACT;
    }
    if (keycode == SDLK_KP_PLUS) {
        return AKEYCODE_NUMPAD_ADD;
    }
    if (keycode == SDLK_KP_DECIMAL) {
        return AKEYCODE_NUMPAD_DOT;
    }
    if (keycode == SDLK_KP_ENTER) {
        return AKEYCODE_NUMPAD_ENTER;
    }
    if (keycode == SDLK_KP_EQUALS) {
        return AKEYCODE_NUMPAD_EQUALS;
    }
    return AKEYCODE_UNKNOWN;
}

int getGameKeyCode(int keycode) {
    if (keycode == SDLK_w) {
        return MCKEY_FORWARD;
    } else if (keycode == SDLK_a) {
        return MCKEY_LEFT;
    } else if (keycode == SDLK_s) {
        return MCKEY_BACK;
    } else if (keycode == SDLK_d) {
        return MCKEY_RIGHT;
    } else if (keycode == SDLK_SPACE && !is_keyboard_visible) {
        return MCKEY_JUMP;
    } else if (keycode == SDLK_e) {
        return MCKEY_INVENTORY;
    } else if (keycode == SDLK_ESCAPE) {
        return MCKEY_PAUSE;
    } else if (keycode == SDLK_c && version_id <= version_id_0_8_1) {
        return MCKEY_CRAFTING;
    } else if (keycode == SDLK_RETURN) {
        return MCKEY_SIGN_ENTER;
    } else if (keycode == SDLK_BACKSPACE) {
        return MCKEY_SIGN_BACKSPACE;
    } else if (keycode == SDLK_LCTRL) {
        return MCKEY_MENU_CANCEL;
    } else if (keycode == SDLK_LSHIFT) {
        return MCKEY_SNEAK;
    } else if (keycode == SDLK_q) {
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

float calculate_scale(int width, int height, float dpi) {
    float dpi_scale = (dpi <= 0.0f) ? 1.0f : (dpi / 96.0f);
    float width_scale = (float)width / 1920.0f;
    float height_scale = (float)height / 1080.0f;
    float combined_scale = (dpi_scale * 1.2) + ((width_scale + height_scale) * 0.8);
    combined_scale = fminf(fmaxf(roundf(combined_scale), 1.0f), 4.0f);
    return combined_scale;
}

static void set_ninecraft_size(int width, int height) {
    if (version_id >= version_id_0_10_0) {
        minecraft_client_set_size(ninecraft_app, width, height, 2.f);
    } else {
        minecraft_set_size(ninecraft_app, width, height);
    }
    size_t screen_offset;
    if (version_id == version_id_0_11_1) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_11_1;
    } else if (version_id == version_id_0_11_0) {
        screen_offset = MINECRAFTCLIENT_SCREEN_OFFSET_0_11_0;
    } else if (version_id == version_id_0_10_5) {
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
    float ddpi = 96.0f;
    SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(_window), &ddpi, NULL, NULL);
    float scale = calculate_scale(width, height, ddpi);
    *(float *)android_dlsym(handle, "_ZN3Gui11InvGuiScaleE") = 1.0f / scale;
    *(float *)android_dlsym(handle, "_ZN3Gui8GuiScaleE") = scale;
    void *screen = *(void **)((char *)ninecraft_app + screen_offset);
    if (screen) {
        ((void (*)(void *, int, int))android_dlsym(handle, "_ZN6Screen7setSizeEii"))(screen, width / scale, height / scale);
    }
}

static void resize_callback(struct SDL_Window *window, int width, int height) {
    if (version_id == version_id_0_1_0) {
        set_ninecraft_size_0_1_0(width, height);
    } else {
        set_ninecraft_size(width, height);
    }
}

static void char_callback(struct SDL_Window *window, char *codepoint) {
    if (is_keyboard_visible) {
        chat_mod_append_char(codepoint[0]);
        if (version_id >= version_id_0_6_0 && version_id <= version_id_0_7_1) {
            keyboard_feed_text_0_6_0(codepoint[0]);
        } else if (version_id >= version_id_0_7_2) {
            android_string_t str;
            android_string_cstr(&str, codepoint);
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

static void key_callback(struct SDL_Window *window, int key, int scancode, int action, int mod) {
    int android_key = sdl_to_android_key(key);
    if (action == SDL_KEYDOWN) {
        mod_loader_execute_on_key_pressed(android_key);
    } else if (action == SDL_KEYUP) {
        mod_loader_execute_on_key_released(android_key);
    }
    if (key == SDLK_F11) {
        if (action == SDL_KEYDOWN) {
            if (is_fullscreen) {
                is_fullscreen = false;
                SDL_SetWindowFullscreen(_window, 0);
            } else {
                is_fullscreen = true;
                SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
        }
    } else {
        if (key == SDLK_LCTRL) {
            if (action == SDL_KEYDOWN) {
                ctrl_pressed = true;
            } else if (action == SDL_KEYUP) {
                ctrl_pressed = false;
            }
        }
        int game_keycode = getGameKeyCode(key);
        if (key == SDLK_q && action == SDL_KEYDOWN && mouse_pointer_hidden && version_id >= version_id_0_5_0 && version_id <= version_id_0_11_1) {
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
            } else if (version_id == version_id_0_11_1) {
                inventory_offset = PLAYER_INVENTORY_OFFSET_0_11_1;
            }
            void *player = NULL;
            if (version_id >= version_id_0_5_0 && version_id <= version_id_0_9_5) {
                player = *(void **)((char *)ninecraft_app + player_offset);
            } else if (version_id >= version_id_0_10_0 && version_id <= version_id_0_11_1) {
                player = minecraft_client_get_local_player(ninecraft_app);
            }
            if (player) {
                bool is_creative = ((bool (*)(void *))android_dlsym(handle, "_ZN9Minecraft14isCreativeModeEv"))(ninecraft_app);
                if (!is_creative) {
                    void *player_inventory = *(void **)((char *)player + inventory_offset);
                    void *item_instance = NULL;
                    if (version_id >= version_id_0_11_0 && version_id <= version_id_0_11_1) {
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
                                if (version_id >= version_id_0_11_0 && version_id <= version_id_0_11_1) { 
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
                            } else if (version_id >= version_id_0_7_2 && version_id <= version_id_0_11_1) {
                                ((void (*)(void *, void *, bool))android_dlsym(handle, "_ZN11LocalPlayer4dropEPK12ItemInstanceb"))(player, item_instance_copy, false);
                            }
                        }
                    }
                }
            }         
        } else if (mouse_pointer_hidden && key == SDLK_LSHIFT && version_id <= version_id_0_4_0_j) {
            if (controller_states) {
                if (action == SDL_KEYDOWN) {
                    controller_states[0] = 1;
                } else if (action == SDL_KEYUP) {
                    controller_states[0] = 0;
                }
            }
        } else if (mouse_pointer_hidden && key == SDLK_t) {
            if (action == SDL_KEYDOWN) {
                if (version_id >= version_id_0_7_0 && version_id <= version_id_0_11_1) {
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
                    } else if (version_id == version_id_0_11_1) {
                        minecraft_screenchooser_offset = MINECRAFT_SCREENCHOOSER_OFFSET_0_11_1;
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
        } else if (version_id >= version_id_0_1_1 && key == SDLK_ESCAPE) {
            if (action == SDL_KEYDOWN) {
                if (version_id >= version_id_0_10_0) {
                    minecraft_client_handle_back(ninecraft_app, false);
                } else {
                    ninecraft_app_handle_back(ninecraft_app, false);
                }
            }
        } else if (action == SDL_KEYDOWN && game_keycode) {
            keyboard_feed(game_keycode, 1);
        } else if (action == SDL_KEYUP && game_keycode) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

void grab_mouse() {
    puts("grab_mouse");
    mouse_pointer_hidden = true;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(true);
    SDL_SetWindowGrab(_window, true);
    mod_loader_execute_on_minecraft_grab_mouse(ninecraft_app, version_id);
}

void release_mouse() {
    puts("release_mouse");
    mouse_pointer_hidden = false;
    SDL_ShowCursor(default_mouse_mode);
    SDL_SetRelativeMouseMode(false);
    SDL_SetWindowGrab(_window, false);
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
    add_custom_hook("glStencilFuncSeparate", (void *)gl_stencil_func_separate);
    add_custom_hook("glStencilOpSeparate", (void *)gl_stencil_op_separate);
    add_custom_hook("glDeleteShader", (void *)gl_delete_shader);
    add_custom_hook("glUniform1i", (void *)gl_uniform_1_i);
    add_custom_hook("glBufferSubData", (void *)gl_buffer_sub_data);
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
    void *command_server;
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
    command_server = *(void **)((char *)ninecraft_app + minecraft_command_server_offset);
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

int64_t _size(android_string_t *path) {
    struct stat statbuf;
    if (!stat(android_string_to_str(path), &statbuf)) {
        return statbuf.st_size;
    }
    return 0;
}

static bool detect_version() {
    bool found = true;
    static android_string_t in;
    void (*get_game_version_string)(android_string_t *, android_string_t *);
    void (*get_game_version_string_2)(android_string_t *);

    if (!handle) {
        return false;
    }

    android_string_cstr(&in, "v%d.%d.%d alpha");

    get_game_version_string = (void (*)(android_string_t *, android_string_t *))android_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs");
    get_game_version_string_2 = (void (*)(android_string_t *))android_dlsym(handle, "_ZN6Common20getGameVersionStringEv");
    
    if (get_game_version_string != NULL) {
        bool is_j = android_dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnCreate") != NULL;
        static android_string_t game_version;
        char *verstr;

#if defined(__i386__) || defined(_M_IX86)
        sysv_call_func(get_game_version_string, &game_version, 1, &in);
#else
        get_game_version_string(&game_version, &in);
#endif

        verstr = android_string_to_str(&game_version);

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
            found = false;
        }
    } else if (get_game_version_string_2 != NULL) {
        static android_string_t game_version;
        char *verstr;

#if defined(__i386__) || defined(_M_IX86)
        sysv_call_func(get_game_version_string_2, &game_version, 0);
#else
        get_game_version_string_2(&game_version);
#endif

        verstr = android_string_to_str(&game_version);

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
        } else if (strcmp(verstr, "v0.11.1 alpha") == 0) {
            version_id = version_id_0_11_1;
        } else {
            puts("Unsupported Version!");
            found = false;
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
            found = false;
        }
    }

    android_string_destroy(&in);

    return found;
}

int main(int argc, char **argv) {
    struct soinfo *so_liblog, *so_libgles, *so_libgles2, *so_libegl;
    struct soinfo *so_libandroid, *so_libopensles, *so_libz;
    char *storage_path, *mods_path, *ovc_path, *icon_path;
    static struct stat st = {0};
    int icon_width, icon_height;
    SDL_GLContext gl_context;
    size_t ninecraft_app_size, minecraft_isgrabbed_offset;
    bool running = true;
    SDL_Event event;
    char *minecraft_options;
    void *icon_pixels;

    storage_path = (char *)malloc(1024);
    if (!storage_path) {
        puts("out of memory");
        return 1;
    }
    storage_path[0] = '\0';
    strcat(storage_path, game_parameters.home_path);
    strcat(storage_path, "/storage/");

    mods_path = (char *)malloc(1024);
    if (!mods_path) {
        puts("out of memory");
        free(storage_path);
        return 1;
    }
    mods_path[0] = '\0';
    strcat(mods_path, game_parameters.home_path);
    strcat(mods_path, "/mods/");

    ovc_path = (char *)malloc(1024);
    if (!ovc_path) {
        puts("out of memory");
        free(storage_path);
        free(mods_path);
        return 1;
    }
    ovc_path[0] = '\0';
    strcat(ovc_path, game_parameters.home_path);
    strcat(ovc_path, "/options.txt");

    icon_path = (char *)malloc(1024);
    if (!icon_path) {
        puts("out of memory");
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        return 1;
    }
    icon_path[0] = '\0';
    strcat(icon_path, game_parameters.game_path);
    strcat(icon_path, "/res/drawable/iconx.png");

    if (stat(storage_path, &st) == -1) {
        mkdir(storage_path, 0700);
    }

    if (stat(mods_path, &st) == -1) {
        mkdir(mods_path, 0700);
    }

    ninecraft_read_options_file(&platform_options, ovc_path);
    ninecraft_set_default_options(&platform_options, ovc_path);

    android_linker_init();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        free(icon_path);
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    _window = SDL_CreateWindow(
        "Ninecraft",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        720, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!_window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        free(icon_path);
        return 1;
    }

    icon_pixels = (void *)stbi_load(icon_path, &icon_width, &icon_height, NULL, STBI_rgb_alpha);
    if (icon_pixels) {
        SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(
            icon_pixels, icon_width, icon_height, 32, icon_width * 4,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
#else
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#endif
        );
        SDL_SetWindowIcon(_window, icon);
        SDL_FreeSurface(icon);
        stbi_image_free(icon_pixels);
    }

    gl_context = SDL_GL_CreateContext(_window);
    if (!gl_context) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        free(icon_path);
        return 1;
    }

    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

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

    so_liblog = android_library_create("liblog.so");
    so_libgles = android_library_create("libGLESv1_CM.so");
    so_libgles2 = android_library_create("libGLESv2.so");
    so_libegl = android_library_create("libEGL.so");
    so_libandroid = android_library_create("libandroid.so");
    so_libopensles = android_library_create("libOpenSLES.so");
    so_libz = android_library_create("libz.so");

    handle = load_library("libminecraftpe.so");

    if (!handle) {
        puts("libminecraftpe.so not loaded");
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        free(icon_path);
        return 1;
    }
    
    android_alloc_setup_hooks(handle);

    if (!detect_version()) {
        free(storage_path);
        free(mods_path);
        free(ovc_path);
        free(icon_path);
        return 1;
    }

    multitouch_setup_hooks(handle);
    keyboard_setup_hooks(handle);
    minecraft_setup_hooks(handle);
    inject_mods(handle, version_id);
    mod_loader_load_all(handle, version_id);

    controller_states = (unsigned char *)android_dlsym(handle, "_ZN10Controller15isTouchedValuesE");
    controller_x_stick = (float *)android_dlsym(handle, "_ZN10Controller12stickValuesXE");
    controller_y_stick = (float *)android_dlsym(handle, "_ZN10Controller12stickValuesYE");

    if (version_id >= version_id_0_6_0 && version_id <= version_id_0_9_5) {
        default_mouse_mode = SDL_DISABLE;
    }

    SDL_ShowCursor(default_mouse_mode);

    if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
        printf("nine construct %p\n", ninecraft_app_construct_2);
    } else if (version_id >= version_id_0_10_0) {
        printf("nine construct %p\n", minecraft_client_construct);
    } else {
        printf("nine construct %p\n", ninecraft_app_construct);
    }

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
    } else if (version_id == version_id_0_11_1) {
        ninecraft_app_size = MINECRAFTCLIENT_SIZE_0_11_1;
    }
    ninecraft_app = malloc(ninecraft_app_size);
    if (version_id >= version_id_0_9_0 && version_id <= version_id_0_9_5) {
        ninecraft_app_construct_2(ninecraft_app, 0, NULL);
    } else if (version_id >= version_id_0_10_0) {
        minecraft_client_construct(ninecraft_app, 0, NULL);
    } else {
        ninecraft_app_construct(ninecraft_app);
    }

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
        } else if (version_id >= version_id_0_11_0 && version_id <= version_id_0_11_1) {
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
            DETOUR(android_dlsym(handle, "_ZN12AndroidStore21createGooglePlayStoreERKSsR13StoreListener"), GET_SYSV_WRAPPER(ninecraft_store_create), 1);
            DETOUR(android_dlsym(handle, "_Z5_sizeRKSs"), _size, 1); 
        }
        context->platform = plat;
#ifdef _WIN32
        call_with_custom_stack(app_init, NULL, 1024 * 1024, 2, ninecraft_app, context);
#else
        app_init(ninecraft_app, context);
#endif
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

#ifdef _WIN32
        call_with_custom_stack(ninecraft_app_init, NULL, 1024 * 1024, 1, ninecraft_app);
#else
        ninecraft_app_init(ninecraft_app);
#endif

        if (version_id >= version_id_0_1_0_touch) {
            *(uint8_t *)((char *)ninecraft_app + 4) = 1; // is_inited
        }
    }

    minecraft_options = minecraft_get_options(ninecraft_app, version_id);

    if (version_id >= version_id_0_5_0 && version_id <= version_id_0_11_1 && minecraft_options && minecraft_options != ninecraft_app) {
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

    if (version_id == version_id_0_11_1) {
        minecraft_isgrabbed_offset = MINECRAFTCLIENT_ISGRABBED_OFFSET_0_11_1;
    } else if (version_id == version_id_0_11_0) {
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
    
    while (running) {
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

#ifdef _WIN32
        if (version_id >= version_id_0_10_0) {
            call_with_custom_stack(minecraft_update, NULL, 1024 * 1024, 1, ninecraft_app);
        } else {
            call_with_custom_stack(ninecraft_app_update, NULL, 1024 * 1024, 1, ninecraft_app);
        }
#else
        if (version_id >= version_id_0_10_0) {
            minecraft_update(ninecraft_app);
        } else {
            ninecraft_app_update(ninecraft_app);
        }
#endif
        mod_loader_execute_on_minecraft_update(ninecraft_app, version_id);

        if (!mouse_pointer_hidden && version_id >= version_id_0_6_0 && version_id <= version_id_0_9_5) {
            short cx, cy;
            int xpos, ypos;
            float inv_gui_scale = *((float *)android_dlsym(handle, "_ZN3Gui11InvGuiScaleE"));
            
            SDL_GetMouseState(&xpos, &ypos);
            cx = (short)(xpos * inv_gui_scale);
            cy = (short)(ypos * inv_gui_scale);
            ((FLOAT_ABI_FIX void (*)(float, float, void *))android_dlsym(handle, "_Z12renderCursorffP9Minecraft"))(cx, cy, ninecraft_app);
        }

        audio_engine_tick();
        SDL_GL_SwapWindow(_window);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                key_callback(_window, event.key.keysym.sym, event.key.keysym.scancode, event.type, event.key.keysym.mod);
            } else if (event.type == SDL_TEXTINPUT) {
                char_callback(_window, event.text.text);
            } else if (event.type == SDL_MOUSEMOTION) {
                mouse_pos_callback(_window, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                mouse_click_callback(_window, event.button.button, event.button.state, event.button.x, event.button.y);
            } else if (event.type == SDL_MOUSEWHEEL) {
                mouse_scroll_callback(_window, event.wheel.preciseX, event.wheel.preciseY, event.wheel.direction);
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                resize_callback(_window, event.window.data1, event.window.data2);
            }
        }
    }
    audio_engine_destroy();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    free(storage_path);
    free(mods_path);
    free(ovc_path);
    return 0;
}
