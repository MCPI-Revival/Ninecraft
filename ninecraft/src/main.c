#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <GLFW/glfw3.h>
#include <ninecraft/patch/detours.h>
#include <ninecraft/gfx/gles_compat.h>
#include <ninecraft/version_ids.h>
#include <ninecraft/input/minecraft_keys.h>
#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/symbols.h>
#include <ninecraft/AppPlatform_linux.h>
#include <ninecraft/audio/audio_engine.h>
#include <ninecraft/hooks.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/input/keyboard.h>
#include <ninecraft/input/mouse_device.h>
#include <ninecraft/input/multitouch.h>
#include <ninecraft/mods/piapi_mod.h>
#include <ninecraft/mods/misc_mod.h>
#include <math.h>
#include <wchar.h>
#include <wctype.h>

#include <hybris/dlfcn.h>
#include <hybris/hook.h>
#include <hybris/jb/linker.h>

void *handle;
GLFWwindow *_window;

int default_mouse_mode = GLFW_CURSOR_NORMAL;

int version_id = 9;

float y_cam = 0.0;
float x_cam = 0.0;

void *ninecraft_app;

static unsigned char *controller_states;
static float *controller_x_stick;
static float *controller_y_stick;

audio_engine_t audio_engine;

bool mouse_pointer_hidden = false;

void *load_minecraftpe() {
    #ifdef __i386__
    char *arch = "x86";
    #else
    #ifdef __arm__
    char *arch = "armeabi-v7a";
    #else
    char *arch = "";
    #endif
    #endif
    char fullpath[MAXPATHLEN];
    getcwd(fullpath, MAXPATHLEN);
    strcat(fullpath, "/lib/");
    strcat(fullpath, arch);
    strcat(fullpath, "/libminecraftpe.so");
    
    void *handle = hybris_dlopen(fullpath, RTLD_LAZY);
    if (handle == NULL)
    {
        printf("failed to load library %s: %s\n", fullpath, hybris_dlerror());
        return NULL;
    }
    printf("lib: %s: : %p\n", fullpath, handle);
    return handle;
}

void stub_symbols(const char **symbols, void *stub_func) {
    int i = 0;
    while (true)
    {
        const char *sym = symbols[i];
        if (sym == NULL)
        {
            break;
        }
        hybris_hook(sym, stub_func);
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
    //puts("warn: egl call");
}

void sles_stub() {
    puts("warn: sles call");
}

void sound_engine_stub() {
    // puts("warn: sound engine");
}

int mouseToGameKeyCode(int keyCode) {
    if (keyCode == GLFW_MOUSE_BUTTON_LEFT) {
        return MCKEY_BREAK;
    } else if (keyCode == GLFW_MOUSE_BUTTON_RIGHT) {
        return MCKEY_PLACE;
    }
}

static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (!mouse_pointer_hidden) {
        int mc_button = (button == GLFW_MOUSE_BUTTON_LEFT ? 1 : (button == GLFW_MOUSE_BUTTON_RIGHT ? 2 : 0));
        if (version_id == version_id_0_6) {
            mouse_device_feed_0_6(hybris_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0, 0);
            multitouch_feed_0_6((char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0);
        } else if (version_id == version_id_0_5) {
            mouse_device_feed_0_5(hybris_dlsym(handle, "_ZN5Mouse9_instanceE"), (char) mc_button, (char) (action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos);
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

static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    char key_code = 0;
    if (yoffset > 0) {
        key_code = MCKEY_HOTBAR_PREVIOUS;
    } else if (yoffset < 0) {
        key_code = MCKEY_HOTBAR_NEXT;
    }
    keyboard_feed(key_code, 1);
    keyboard_feed(key_code, 0);
}

static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!mouse_pointer_hidden) {
        if (version_id == version_id_0_6) {
            mouse_device_feed_0_6(hybris_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos, 0, 0);
            multitouch_feed_0_6(0, 0, (short)xpos, (short)ypos, 0);
        } else if (version_id == version_id_0_5) {
            mouse_device_feed_0_5(hybris_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos);
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
            y_cam -= ((float) ypos - (float)cy) / 6.0;
            x_cam += ((float)xpos - (float)cx) / 3.0;
        }
    }
}

int getGameKeyCode(int keycode) {
    if (keycode == GLFW_KEY_W) {
        return MCKEY_FORWARD;
    } else if (keycode == GLFW_KEY_A) {
        return MCKEY_STEP_LEFT;
    } else if (keycode == GLFW_KEY_S) {
        return MCKEY_BACKWARDS;
    } else if (keycode == GLFW_KEY_D) {
        return MCKEY_STEP_RIGHT;
    } else if (keycode == GLFW_KEY_SPACE) {
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
    } else {
        return 0;
    }
}

static void resize_callback(GLFWwindow* window, int width, int height) {
    ((void (*)(void *, int, int))hybris_dlsym(handle, "_ZN9Minecraft7setSizeEii"))(ninecraft_app, width, height);
}

static void char_callback(GLFWwindow* window, unsigned int codepoint) {
    if (version_id == version_id_0_6) {
        ((void (*)(char))hybris_dlsym(handle, "_ZN8Keyboard8feedTextEc"))((char)codepoint);
    }
}

int old_pos_x, old_pos_y, old_width, old_height;

typedef struct {
    int count;
    int id;
    int meta;
} item_instance_t;

int get_selected_slot(void *inventory) {
    int slot = *(int *)(inventory + INVENTORY_SELECTED_SLOT_OFFSET);
    int count = *(int *)(inventory + FILLINGCONTAINER_LINKED_SLOTS_COUNT_OFFSET);
    if (slot < count) {
        int32_t *slots = *(int **)(inventory + FILLINGCONTAINER_LINKED_SLOTS_OFFSET);
        slot = slots[slot];
    }
    return slot;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F11) {
        if (action == GLFW_PRESS) {
            if (glfwGetWindowMonitor(_window) == NULL) {
                glfwGetWindowPos(_window, &old_pos_x, &old_pos_y);
                glfwGetWindowSize(_window, &old_width, &old_height);
                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                glfwSetWindowMonitor(_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
            } else {
                glfwSetWindowMonitor(_window, NULL, old_pos_x, old_pos_y, old_width, old_height, 0);
            }
        }
    } else if (key == GLFW_KEY_Q) {
        if (action == GLFW_PRESS) {
            void *player = *(void **)(ninecraft_app + MINECRAFT_PLAYER_OFFSET);
            void *inv = *(void **)(player + PLAYER_INVENTORY_OFFSET);
            int slot = get_selected_slot(inv);
            if (glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
                //((void (*)(int, int, char, char))hybris_dlsym(handle, "_ZN16FillingContainer8dropSlotEibb"))(inv, slot, 0, 0);
            } else {
            }
            //audio_engine_play(&audio_engine, handle, "random.pop2", 0, 0, 0, 0.3, 1, 1);
        }
    } else {
        int game_keycode = getGameKeyCode(key);
        if (mouse_pointer_hidden && key == GLFW_KEY_LEFT_SHIFT) {
            if (action == GLFW_PRESS) {
                controller_states[0] = 1;
            } else if (action == GLFW_RELEASE) {
                controller_states[0] = 0;
            }
        } else if (action == GLFW_PRESS && game_keycode) {
            keyboard_feed(game_keycode, 1);
        } else if (action == GLFW_RELEASE && game_keycode) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

void window_close_callback(GLFWwindow* window) {
    audio_engine_destroy_audio_device(&audio_engine);
    exit(0);
}

void grab_mouse() {
    puts("grab_mouse");
    mouse_pointer_hidden = true;
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void release_mouse() {
    puts("release_mouse");
    mouse_pointer_hidden = false;
    glfwSetInputMode(_window, GLFW_CURSOR, default_mouse_mode);
}

void sound_engine_playui(void *sound_engine, android_string_t *sound_name, float volume, float pitch) {
    audio_engine_play(&audio_engine, handle, sound_name->_M_start_of_storage, 0, 0, 0, volume, pitch, true);
}

void sound_engine_play(void *sound_engine, android_string_t *sound_name, float x, float y, float z, float volume, float pitch) {
    audio_engine_play(&audio_engine, handle, sound_name->_M_start_of_storage, x, y, z, volume, pitch, false);
}

void sound_engine_update(void *sound_engine, unsigned char *mob, float listener_angle) {
    float x = 0;
    float y = 0;
    float z = 0;
    float yaw = 0;
    if (mob != NULL) {
        x = *(float *)(mob + 4);
        y = *(float *)(mob + 8);
        z = *(float *)(mob + 12);
        yaw = *(float *)(mob + 64);
    }
    unsigned char *options = (unsigned char *)(ninecraft_app + MINECRAFT_OPTIONS_OFFSET);
    audio_engine_update(&audio_engine, *(int *)(options + 4) ? 1 : 0, x, y, z, yaw);
}

android_string_t get_game_version() {
    android_string_t out;
    android_string_cstr(&out, "Ninecraft 1.1.0");
    return out;
}

void gles_hook() {
    hybris_hook("glAlphaFunc", (void *) gl_alpha_func);
    hybris_hook("glBindBuffer", (void *) gl_bind_buffer);
    hybris_hook("glBindTexture", (void *) gl_bind_texture);
    hybris_hook("glBlendFunc", (void *) gl_blend_func);
    hybris_hook("glBufferData", (void *) gl_buffer_data);
    hybris_hook("glClear", (void *) gl_clear);
    hybris_hook("glClearColor", (void *) gl_clear_color);
    hybris_hook("glColor4f", (void *) gl_color_4_f);
    hybris_hook("glColorMask", (void *) gl_color_mask);
    hybris_hook("glColorPointer", (void *) gl_color_pointer);
    hybris_hook("glCullFace", (void *) gl_cull_face);
    hybris_hook("glDeleteBuffers", (void *) gl_delete_buffers);
    hybris_hook("glDeleteTextures", (void *) gl_delete_textures);
    hybris_hook("glDepthFunc", (void *) gl_depth_func);
    hybris_hook("glDepthMask", (void *) gl_depth_mask);
    hybris_hook("glDepthRangef", (void *) gl_depth_range_f);
    hybris_hook("glDisable", (void *) gl_disable);
    hybris_hook("glDisableClientState", (void *) gl_disable_client_state);
    hybris_hook("glDrawArrays", (void *) gl_draw_arrays);
    hybris_hook("glEnable", (void *) gl_enable);
    hybris_hook("glEnableClientState", (void *) gl_enable_client_state);
    hybris_hook("glFogf", (void *) gl_fog_f);
    hybris_hook("glFogfv", (void *) gl_fog_f_v);
    hybris_hook("glFogx", (void *) gl_fog_x);
    hybris_hook("glGenTextures", (void *) gl_gen_textures);
    hybris_hook("glGetFloatv", (void *) gl_get_float_v);
    hybris_hook("glGetString", (void *) gl_get_string);
    hybris_hook("glHint", (void *) gl_hint);
    hybris_hook("glLineWidth", (void *) gl_line_width);
    hybris_hook("glLoadIdentity", (void *) gl_load_identity);
    hybris_hook("glMatrixMode", (void *) gl_matrix_mode);
    hybris_hook("glMultMatrixf", (void *) gl_mult_matrix_f);
    hybris_hook("glNormal3f", (void *) gl_normal_3_f);
    hybris_hook("glOrthof", (void *) gl_ortho_f);
    hybris_hook("glPolygonOffset", (void *) gl_polygon_offset);
    hybris_hook("glPopMatrix", (void *) gl_pop_matrix);
    hybris_hook("glPushMatrix", (void *) gl_push_matrix);
    hybris_hook("glReadPixels", (void *) gl_read_pixels);
    hybris_hook("glRotatef", (void *) gl_rotate_f);
    hybris_hook("glScalef", (void *) gl_scale_f);
    hybris_hook("glScissor", (void *) gl_scissor);
    hybris_hook("glShadeModel", (void *) gl_shade_model);
    hybris_hook("glTexCoordPointer", (void *) gl_tex_coord_pointer);
    hybris_hook("glTexImage2D", (void *) gl_tex_image_2_d);
    hybris_hook("glTexParameteri", (void *) gl_tex_parameter_i);
    hybris_hook("glTexSubImage2D", (void *) gl_tex_sub_image_2_d);
    hybris_hook("glTranslatef", (void *) gl_translate_f);
    hybris_hook("glVertexPointer", (void *) gl_vertex_pointer);
    hybris_hook("glViewport", (void *) gl_viewport);
}

void math_hook() {
    hybris_hook("atan2f", atan2f);
    hybris_hook("atanf", atanf);
    hybris_hook("ceilf", ceilf);
    hybris_hook("cosf", cosf);
    hybris_hook("floorf", floorf);
    hybris_hook("fmodf", fmodf);
    hybris_hook("logf", logf);
    hybris_hook("powf", powf);
    hybris_hook("sinf", sinf);
    hybris_hook("sqrtf", sqrtf);
}

#ifdef __i386__
int android_dl_iterate_phdr(int (*cb)(struct dl_phdr_info *info, size_t size, void *data),void *data);
#endif

#ifdef __arm__

long unsigned int *android_dl_unwind_find_exidx(long unsigned int *pc, int *pcount);

extern int __cxa_atexit(void (*)(void*), void*, void*);

int __aeabi_atexit_android(void *arg, void (*func) (void *), void *d) {
  return __cxa_atexit(func, arg, d);
}

#endif

int __cxa_pure_virtual() {}

void missing_hook() {
    #ifdef __i386__
    hybris_hook("dl_iterate_phdr", android_dl_iterate_phdr);
    #endif
    hybris_hook("wcscmp", wcscmp);
    hybris_hook("wcsncpy", wcsncpy);
    hybris_hook("iswalpha", iswalpha);
    hybris_hook("iswcntrl", iswcntrl);
    hybris_hook("iswdigit", iswdigit);
    hybris_hook("iswlower", iswlower);
    hybris_hook("iswprint", iswprint);
    hybris_hook("iswpunct", iswpunct);
    hybris_hook("iswupper", iswupper);
    hybris_hook("iswxdigit", iswxdigit);
    hybris_hook("__cxa_pure_virtual", __cxa_pure_virtual);
    #ifdef __arm__
    hybris_hook("__aeabi_atexit", __aeabi_atexit_android);
    hybris_hook("__gnu_Unwind_Find_exidx", android_dl_unwind_find_exidx);
    #endif
}

void remove_call(void *func) {
    *(short *)(func - 1) = 0x4770;
}

int main(int argc, char **argv)
{
    struct stat st = {0};
    if (stat("storage", &st) == -1) {
        mkdir("storage", 0700);
        if (stat("storage/internal", &st) == -1) {
            mkdir("storage/internal", 0700);
        }
        if (stat("storage/external", &st) == -1) {
            mkdir("storage/external", 0700);
        }
    }

    if (!glfwInit()) {
        // Initialization failed
        puts("init failed");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    _window = glfwCreateWindow(720, 480, "Ninecraft", NULL, NULL);
    if (!_window) {
        puts("cant create");
    }

    glfwSetKeyCallback(_window, key_callback);
    glfwSetCharCallback(_window, char_callback);
    glfwSetMouseButtonCallback(_window, mouse_click_callback);
    glfwSetScrollCallback(_window, mouse_scroll_callback);
    glfwSetCursorPosCallback(_window, mouse_pos_callback);
    glfwSetWindowSizeCallback(_window, resize_callback);
    glfwSetWindowCloseCallback(_window, window_close_callback);

    glfwMakeContextCurrent(_window);

    math_hook();
    gles_hook();
    missing_hook();
    hybris_hook("__android_log_print", (void *)__android_log_print);
    stub_symbols(android_symbols, (void *)android_stub);
    stub_symbols(egl_symbols, (void *)egl_stub);
    stub_symbols(sles_symbols, (void *)sles_stub);
    
    handle = load_minecraftpe();

    android_alloc_setup_hooks(handle);
    android_string_setup_hooks(handle);

    android_string_t in;
    android_string_cstr(&in, "");

    android_string_t game_version = ((android_string_t (*)(android_string_t *))hybris_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs"))(&in);

    if (strcmp(game_version._M_start_of_storage, "v0.6.1 alpha") == 0) {
        version_id = version_id_0_6;
    } else if (strcmp(game_version._M_start_of_storage, "v0.6.0 alpha") == 0) {
        version_id = version_id_0_6;
    } else if (strcmp(game_version._M_start_of_storage, "v0.5.0 alpha") == 0) {
        version_id = version_id_0_5;
    } else {
        puts("Unsupported Version!");
        abort();
    }

    printf("Ninecraft is running Minecraft %s\n", game_version._M_start_of_storage);

    multitouch_setup_hooks(handle);
    keyboard_setup_hooks(handle);
    minecraft_setup_hooks(handle);
    piapi_mod_inject(version_id);
    misc_mod_inject(version_id);

    audio_engine_create_audio_device(&audio_engine);
    controller_states = (unsigned char *)hybris_dlsym(handle, "_ZN10Controller15isTouchedValuesE");
    controller_x_stick = (float *)hybris_dlsym(handle, "_ZN10Controller12stickValuesXE");
    controller_y_stick = (float *)hybris_dlsym(handle, "_ZN10Controller12stickValuesYE");

    if (version_id == version_id_0_6) {
        default_mouse_mode = GLFW_CURSOR_HIDDEN;
    }

    glfwSetInputMode(_window, GLFW_CURSOR, default_mouse_mode);
    
    #ifdef __i386__
    DETOUR(hybris_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs"), (void *)get_game_version, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngineC1Ef"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine4initEP9MinecraftP7Options"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine14_getVolumeMultEfff"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine7destroyEv"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine6enableEb"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine4playERKSsfffff"), (void *)sound_engine_play, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine6playUIERKSsff"), (void *)sound_engine_playui, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine6updateEP3Mobf"), (void *)sound_engine_update, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngine13updateOptionsEv"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngineD1Ev"), (void *)sound_engine_stub, true);
    DETOUR(hybris_dlsym(handle, "_ZN11SoundEngineD2Ev"), (void *)sound_engine_stub, true);
    #endif

    #ifdef __arm__
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngineC1Ef"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine4initEP9MinecraftP7Options"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine14_getVolumeMultEfff"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine7destroyEv"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine6enableEb"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine4playERKSsfffff"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine6playUIERKSsff"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine6updateEP3Mobf"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngine13updateOptionsEv"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngineD1Ev"));
    remove_call(hybris_dlsym(handle, "_ZN11SoundEngineD2Ev"));
    #endif

    ninecraft_app = malloc(0xe6c);

    printf("app: %p\n", ninecraft_app);

    printf("%s\n", glGetString(GL_VERSION));

    NinecraftApp$construct ninecraft_app_construct = (NinecraftApp$construct)hybris_dlsym(handle, "_ZN12NinecraftAppC2Ev");
    printf("nine construct %p\n", ninecraft_app_construct);
    ninecraft_app_construct(ninecraft_app);

    android_string_equ((android_string_t *)(ninecraft_app + 3544), "./storage/internal/");
    android_string_equ((android_string_t *)(ninecraft_app + 3568), "./storage/external/");

    AppPlatform_linux platform;
    AppPlatform_linux$AppPlatform_linux(&platform, handle, version_id);
    *(void **)(ninecraft_app + 0x14) = &platform;
    printf("%p\n", &platform);
    NinecraftApp$init ninecraft_app_init = (NinecraftApp$init)hybris_dlsym(handle, "_ZN12NinecraftApp4initEv");
    ninecraft_app_init(ninecraft_app);

    ((void (*)(void *, int, int))hybris_dlsym(handle, "_ZN9Minecraft7setSizeEii"))(ninecraft_app, 720, 480);

    while (true) {
        if (*(bool *)(ninecraft_app+0xd98) == true) {
            if (!mouse_pointer_hidden) {
                grab_mouse();
            }
        } else {
            if (mouse_pointer_hidden) {
                release_mouse();
            }
        }
        if (mouse_pointer_hidden) {
            controller_states[1] = 1;
            controller_y_stick[1] = (float)(y_cam - 180.0) * 0.0055555557;
            controller_x_stick[1] = ((float)((x_cam - 483.0)) * 0.0020703934);
        }
        ((void (*)(void *))hybris_dlsym(handle, "_ZN12NinecraftApp6updateEv"))(ninecraft_app);
        
        if (!mouse_pointer_hidden) {
            if (version_id == version_id_0_6) {
                float inv_gui_scale = *((float *)hybris_dlsym(handle, "_ZN3Gui11InvGuiScaleE"));
                double xpos, ypos;
                glfwGetCursorPos(_window, &xpos, &ypos);
                short cx = (short)(xpos * inv_gui_scale);
                short cy = (short)(ypos * inv_gui_scale);
                ((void (*)(float, float, void *))hybris_dlsym(handle, "_Z12renderCursorffP9Minecraft"))(cx, cy, ninecraft_app);
            }
        }
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    return 0;
}
