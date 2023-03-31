#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/timeb.h>
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
#include <ninecraft/hooks.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/input/keyboard.h>
#include <ninecraft/input/mouse_device.h>
#include <ninecraft/input/multitouch.h>
#include <ninecraft/mods/inject.h>
#include <ninecraft/mods/mod_loader.h>
#include <math.h>
#include <wchar.h>
#include <wctype.h>
#include <ninecraft/audio/sles.h>
#include <ninecraft/audio/audio_engine.h>
#include <zlib.h>

#include <ninecraft/dlfcn_stub.h>
#include <hybris/hook.h>
#include <hybris/jb/linker.h>

#include <ninecraft/math_compat.h>
#include <ninecraft/ninecraft_defs.h>
#include <hybris/dlfcn.h>

#include <stdatomic.h>
#include <linux/futex.h>
#include <sys/syscall.h>

void *handle = NULL;
GLFWwindow *_window = NULL;

int default_mouse_mode = GLFW_CURSOR_NORMAL;

int version_id = 0;

float y_cam = 0.0;
float x_cam = 0.0;

void *ninecraft_app;

static unsigned char *controller_states;
static float *controller_x_stick;
static float *controller_y_stick;

bool mouse_pointer_hidden = false;

int old_pos_x, old_pos_y, old_width, old_height;

void *load_library(const char *name) {
    #ifdef __i386__
    char *arch = "x86";
    #else
    #ifdef __thumb2__
    char *arch = "armeabi-v7a";
    #else
    char *arch = "";
    #endif
    #endif
    char fullpath[MAXPATHLEN];
    getcwd(fullpath, MAXPATHLEN);
    strcat(fullpath, "/lib/");
    strcat(fullpath, arch);
    strcat(fullpath, "/");
    strcat(fullpath, name);
    
    void *handle = internal_dlopen(fullpath, RTLD_LAZY);
    if (handle == NULL)
    {
        printf("failed to load library %s: %s\n", fullpath, internal_dlerror());
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
    // puts("warn: egl call");
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
        if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), (char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0, 0);
            multitouch_feed_0_6((char)mc_button, (char)(action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_5_0) {
            mouse_device_feed_0_5(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), (char) mc_button, (char) (action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos);
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
        if (version_id >= version_id_0_6_0) {
            mouse_device_feed_0_6(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos, 0, 0);
            multitouch_feed_0_6(0, 0, (short)xpos, (short)ypos, 0);
        } else if (version_id <= version_id_0_5_0) {
            mouse_device_feed_0_5(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), 0, 0, (short)xpos, (short)ypos);
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
    minecraft_set_size(ninecraft_app, width, height);
}

static void char_callback(GLFWwindow* window, unsigned int codepoint) {
    if (version_id >= version_id_0_6_0 && version_id <= version_id_0_7_1) {
        char c = (char)codepoint;
        android_vector_push_back(keyboard_input_text, &c, 1);
    } else if (version_id >= version_id_0_7_2) {
        char p_codepoint[2] = {(char)codepoint, '\0'};
        android_string_t str;
        android_string_cstr(&str, p_codepoint);
        ((void (*)(android_string_t *, uint8_t))internal_dlsym(handle, "_ZN8Keyboard8feedTextERKSsb"))(&str, 0);
        android_string_deallocate_block(&str);
    }
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
    } else {
        int game_keycode = getGameKeyCode(key);
        if (mouse_pointer_hidden && key == GLFW_KEY_LEFT_SHIFT) {
            if (action == GLFW_PRESS) {
                controller_states[0] = 1;
            } else if (action == GLFW_RELEASE) {
                controller_states[0] = 0;
            }
        } else if (mouse_pointer_hidden && key == GLFW_KEY_T) {
            if (version_id == version_id_0_7_0) {
                if (action == GLFW_PRESS) {
                    ((void (*)(void *, int))internal_dlsym(handle, "_ZN13ScreenChooser9setScreenE8ScreenId"))(ninecraft_app + 0x2f0, 7);
                }
            } else if (version_id >= version_id_0_7_1) {
                int w;
                glfwGetWindowSize(_window, &w, NULL);
                if (action == GLFW_PRESS) {
                    mouse_device_feed_0_6(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), 1, 1, (short)w, 0, 0, 0);
                } else if (action == GLFW_RELEASE) {
                    mouse_device_feed_0_6(internal_dlsym(handle, "_ZN5Mouse9_instanceE"), 1, 0, (short)w, 0, 0, 0);
                }
            }
        } else if (action == GLFW_PRESS && game_keycode) {
            keyboard_feed(game_keycode, 1);
        } else if (action == GLFW_RELEASE && game_keycode) {
            keyboard_feed(game_keycode, 0);
        }
    }
}

void window_close_callback(GLFWwindow* window) {
    audio_engine_destroy();
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
    hybris_hook("glDrawElements", (void *) gl_draw_elements);
    hybris_hook("glGetError", (void *) gl_get_error);
    hybris_hook("glGenBuffers", (void *) glGenBuffers);
    
}

void math_hook() {
    hybris_hook("atan2f", math_atan2f);
    hybris_hook("atanf", math_atanf);
    hybris_hook("ceilf", math_ceilf);
    hybris_hook("cosf", math_cosf);
    hybris_hook("floorf", math_floorf);
    hybris_hook("fmodf", math_fmodf);
    hybris_hook("logf", math_logf);
    hybris_hook("powf", math_powf);
    hybris_hook("sinf", math_sinf);
    hybris_hook("sqrtf", math_sqrtf);
    hybris_hook("floor", math_floor);
    hybris_hook("ceil", math_ceil);
    hybris_hook("fmod", math_fmod);
    hybris_hook("sin", math_sin);
    hybris_hook("sqrt", math_sqrt);
    hybris_hook("pow", math_pow);
    hybris_hook("atan2", math_atan2);
    hybris_hook("cos", math_cos);
    hybris_hook("atan", math_atan);
    hybris_hook("cosh", math_cosh);
    hybris_hook("tan", math_tan);
    hybris_hook("tanh", math_tanh);
    hybris_hook("asin", math_asin);
    hybris_hook("log", math_log);
    hybris_hook("sinh", math_sinh);
    hybris_hook("modf", math_modf);
    hybris_hook("acos", math_acos);
    hybris_hook("exp", math_exp);
    hybris_hook("frexp", math_frexp);
    hybris_hook("log10", math_log10);
}

#ifdef __thumb2__

extern void __aeabi_uidiv();

extern void __aeabi_atexit();

extern void __aeabi_d2ulz();

extern void __aeabi_uidivmod();

extern void __aeabi_uldivmod();

extern void __aeabi_ldivmod();

extern void __aeabi_ul2d();

extern void __aeabi_idivmod();

extern void __aeabi_idiv();

#endif

void __my_cxa_pure_virtual() {
    perror("Called none existant function");
    abort();
}

NINECRAFT_FLOAT_FUNC double io_strtod(const char *__nptr, char **__endptr) {
    return strtod(__nptr, __endptr);
}

void *cpp_operator_new(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("Failed to allocate memory");
        abort();
    }
    return ptr;
}

void cpp_operator_delete(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

extern void *__dso_handle;

#define CONSTRUCTION_NOT_YET_STARTED 0
#define CONSTRUCTION_COMPLETE 1
#define CONSTRUCTION_UNDERWAY_WITHOUT_WAITER 0x100
#define CONSTRUCTION_UNDERWAY_WITH_WAITER 0x200

typedef union {
  atomic_int state;
  int32_t aligner;
} my_guard_t;

int __my_cxa_guard_acquire(my_guard_t *gv) {
    int old_value = atomic_load_explicit(&gv->state, memory_order_relaxed);
    while (true) {
        if (old_value == CONSTRUCTION_COMPLETE) {
            atomic_thread_fence(memory_order_acquire);
            return 0;
        } else if (old_value == CONSTRUCTION_NOT_YET_STARTED) {
            if (!atomic_compare_exchange_weak_explicit(&gv->state, &old_value,
                    CONSTRUCTION_UNDERWAY_WITHOUT_WAITER,
                    memory_order_relaxed,
                    memory_order_relaxed)) {
                    continue;
            }
            atomic_thread_fence(memory_order_acquire);
            return 1;
        } else if (old_value == CONSTRUCTION_UNDERWAY_WITHOUT_WAITER) {
            if (!atomic_compare_exchange_weak_explicit(&gv->state, &old_value,
                    CONSTRUCTION_UNDERWAY_WITH_WAITER,
                    memory_order_relaxed,
                    memory_order_relaxed
                )
            ) {
                continue;
            }
        }
        syscall(SYS_futex, &gv->state, FUTEX_WAIT, CONSTRUCTION_UNDERWAY_WITH_WAITER, NULL, NULL, 0);
        old_value = atomic_load_explicit(&gv->state, memory_order_relaxed);
    }
}

void __my_cxa_guard_release(my_guard_t *gv) {
    int old_value = atomic_exchange_explicit(&gv->state, CONSTRUCTION_COMPLETE, memory_order_release);
    if (old_value == CONSTRUCTION_UNDERWAY_WITH_WAITER) {
        syscall(SYS_futex, &gv->state, FUTEX_WAKE, INT_MAX, NULL, NULL, 0);
    }
}

void missing_hook() {
    hybris_hook("__cxa_guard_release", __my_cxa_guard_release);
    hybris_hook("__cxa_guard_acquire", __my_cxa_guard_acquire);
    hybris_hook("__dso_handle", &__dso_handle);
    hybris_hook("_Znaj", cpp_operator_new);
    hybris_hook("_ZdaPv", cpp_operator_delete);
    hybris_hook("_Znwj", cpp_operator_new);
    hybris_hook("_ZdlPv", cpp_operator_delete);
    hybris_hook("strtod", io_strtod);
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

    hybris_hook("deflateInit_", deflateInit_);
    hybris_hook("deflateInit2_", deflateInit2_);
    hybris_hook("deflate", deflate);
    hybris_hook("deflateEnd", deflateEnd);
    hybris_hook("inflateInit_", inflateInit_);
    hybris_hook("inflateInit2_", inflateInit2_);
    hybris_hook("inflate", inflate);
    hybris_hook("inflateEnd", inflateEnd);
    hybris_hook("uncompress", uncompress);
    hybris_hook("compress", compress);

    hybris_hook("ftime", ftime);

    hybris_hook("__cxa_pure_virtual", __my_cxa_pure_virtual);

    #ifdef __thumb2__
    hybris_hook("__aeabi_atexit", __aeabi_atexit);
    hybris_hook("__aeabi_uidiv", __aeabi_uidiv);
    hybris_hook("__aeabi_d2ulz", __aeabi_d2ulz);
    hybris_hook("__aeabi_uidivmod", __aeabi_uidivmod);
    hybris_hook("__aeabi_uldivmod", __aeabi_uldivmod);
    hybris_hook("__aeabi_ldivmod", __aeabi_ldivmod);
    hybris_hook("__aeabi_ul2d", __aeabi_ul2d);
    hybris_hook("__aeabi_idivmod", __aeabi_idivmod);
    hybris_hook("__aeabi_idiv", __aeabi_idiv);
    #endif
}

int main(int argc, char **argv) {
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
    if (stat("mods", &st) == -1) {
        mkdir("mods", 0700);
    }

    if (!glfwInit()) {
        // Initialization failed
        puts("init failed");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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

    audio_engine_init();

    math_hook();
    gles_hook();
    missing_hook();
    hybris_hook("__android_log_print", (void *)__android_log_print);
    stub_symbols(android_symbols, (void *)android_stub);
    stub_symbols(egl_symbols, (void *)egl_stub);

    hybris_hook("SL_IID_VOLUME", &sles_iid_volume);
    hybris_hook("SL_IID_ENGINE", &sles_iid_engine);
    hybris_hook("SL_IID_BUFFERQUEUE", &sles_iid_bufferqueue);
    hybris_hook("SL_IID_PLAY", &sles_iid_play);
    hybris_hook("slCreateEngine", sles_create_engine);

    handle = load_library("libminecraftpe.so");

    android_alloc_setup_hooks(handle);
    android_string_setup_hooks(handle);
    
    android_string_t in;
    android_string_cstr(&in, "v%d.%d.%d alpha");

    android_string_t (*get_game_version_string)(android_string_t *) = (android_string_t (*)(android_string_t *))internal_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs");
    if (get_game_version_string != NULL) {
        android_string_t game_version = get_game_version_string(&in);
        char *verstr = android_string_to_str(&game_version);
        printf("Ninecraft is running mcpe %.6s\n", verstr);
        printf("%s\n", verstr);

        if (strncmp(verstr, "v0.2.1", 6) == 0) {
            version_id = version_id_0_2_1;
        } else if (strncmp(verstr, "v0.2.2", 6) == 0) {
            version_id = version_id_0_2_2;
        } else if (strncmp(verstr, "v0.3.0", 6) == 0) {
            version_id = version_id_0_3_0;
        } else if (strncmp(verstr, "v0.3.2", 6) == 0) {
            version_id = version_id_0_3_2;
        } else if (strncmp(verstr, "v0.3.3", 6) == 0) {
            version_id = version_id_0_3_3;
        } else if (strncmp(verstr, "v0.4.0", 6) == 0) {
            version_id = version_id_0_4_0;
        } else if (strncmp(verstr, "v0.5.0", 6) == 0) {
            version_id = version_id_0_5_0;
        } else if (strncmp(verstr, "v0.6.0", 6) == 0) {
            version_id = version_id_0_6_1;
        } else if (strncmp(verstr, "v0.6.1", 6) == 0) {
            version_id = version_id_0_6_1;
        } else if (strncmp(verstr, "v0.7.0", 6) == 0) {
            version_id = version_id_0_7_0;
        } else if (strncmp(verstr, "v0.7.1", 6) == 0) {
            version_id = version_id_0_7_0;
#ifdef __i386__
        } else if (strncmp(verstr, "v0.7.2", 6) == 0) {
        version_id = version_id_0_7_2;
#endif
        } else {
            puts("Unsupported Version!");
            return 1;
        }
    } else {
        Dl_info info;
        hybris_dladdr(internal_dlsym(handle, "_ZN12NinecraftAppC2Ev"), &info);
        if (strncmp(info.dli_fbase + 0x15d3a8, "v0.2.0", 6) == 0) {
            version_id = version_id_0_2_0;
        } else if (strncmp(info.dli_fbase + 0xfca6c, "v0.1.3", 6) == 0) {
            version_id = version_id_0_1_3;
        } else {
            puts("Unsupported Version!");
            return 1;
        }
    }

    multitouch_setup_hooks(handle);
    keyboard_setup_hooks(handle);
    minecraft_setup_hooks(handle);
    inject_mods(version_id);
    mod_loader_load_all();

    controller_states = (unsigned char *)internal_dlsym(handle, "_ZN10Controller15isTouchedValuesE");
    controller_x_stick = (float *)internal_dlsym(handle, "_ZN10Controller12stickValuesXE");
    controller_y_stick = (float *)internal_dlsym(handle, "_ZN10Controller12stickValuesYE");

    if (version_id >= version_id_0_6_0) {
        default_mouse_mode = GLFW_CURSOR_HIDDEN;
    }

    glfwSetInputMode(_window, GLFW_CURSOR, default_mouse_mode);

    printf("%s\n", glGetString(GL_VERSION));

    printf("nine construct %p\n", ninecraft_app_construct);
    size_t ninecraft_app_size;

    if (version_id == version_id_0_1_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_1_3;
    } else if (version_id == version_id_0_2_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_0;
    } else if (version_id == version_id_0_2_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_1;
    } else if (version_id == version_id_0_2_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_2_2;
    } else if (version_id == version_id_0_3_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_0;
    } else if (version_id == version_id_0_3_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_2;
    } else if (version_id == version_id_0_3_3) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_3_3;
    } else if (version_id == version_id_0_4_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_4_0;
    } else if (version_id == version_id_0_6_1) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_6_1;
    } else if (version_id == version_id_0_5_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_6_1;
    } else if (version_id == version_id_0_7_0) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_0;
    } else if (version_id == version_id_0_7_2) {
        ninecraft_app_size = NINECRAFTAPP_SIZE_0_7_2;
    }
    ninecraft_app = malloc(ninecraft_app_size);
    ninecraft_app_construct(ninecraft_app);

    if (version_id == version_id_0_7_0) {
#ifdef __i386__
        android_string_equ((android_string_t *)(ninecraft_app + 3616), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3640), "./storage/external/");
#else
#ifdef __thumb2__
        android_string_equ((android_string_t *)(ninecraft_app + 3620), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3644), "./storage/external/");
#endif
#endif
    } else if (version_id == version_id_0_7_2) {
        android_string_equ((android_string_t *)(ninecraft_app + 3628), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3652), "./storage/external/");
    } else if (version_id >= version_id_0_5_0 && version_id <= version_id_0_6_1) {
        android_string_equ((android_string_t *)(ninecraft_app + 3544), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3568), "./storage/external/");
    } else if (version_id == version_id_0_4_0) {
        android_string_equ((android_string_t *)(ninecraft_app + 3540), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3564), "./storage/external/");
    } else if (version_id == version_id_0_3_3) {
        android_string_equ((android_string_t *)(ninecraft_app + 3536), "./storage/internal/");
        android_string_equ((android_string_t *)(ninecraft_app + 3560), "./storage/external/");
    } else if (version_id == version_id_0_3_2 || version_id == version_id_0_3_0) {
        android_string_equ((android_string_t *)(ninecraft_app + 3528), "./storage/external/");
    } else if (version_id == version_id_0_2_2) {
        android_string_equ((android_string_t *)(ninecraft_app + 3492), "./storage/external/");
    } else if (version_id == version_id_0_2_1) {
        android_string_equ((android_string_t *)(ninecraft_app + 3112), "./storage/external/");
    } else if (version_id == version_id_0_2_0) {
        android_string_equ((android_string_t *)(ninecraft_app + 3060), "./storage/external/");
    } else if (version_id == version_id_0_1_3) {
        android_string_equ((android_string_t *)(ninecraft_app + 3456), "./storage/external/");
    }

    AppPlatform_linux platform;
    AppPlatform_linux$AppPlatform_linux(&platform, handle, version_id);
    printf("%p\n", &platform);

    *(void **)(ninecraft_app + 0x08) = NULL; // egl_display
    *(void **)(ninecraft_app + 0x0c) = NULL; // egl_content
    *(void **)(ninecraft_app + 0x10) = NULL; // egl_surface
    *(void **)(ninecraft_app + 0x14) = &platform; // app_platform
    *(uint8_t *)(ninecraft_app + 0x18) = 0; // do_render

    ninecraft_app_init(ninecraft_app);

    *(uint8_t *)(ninecraft_app + 4) = 1; // is_inited
    
    minecraft_set_size(ninecraft_app, 720, 480);

    while (true) {
        size_t minecraft_isgrabbed_offset;
        if (version_id == version_id_0_7_2) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_2;
        } else if (version_id == version_id_0_7_0) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_7_0;
        } else if (version_id == version_id_0_6_1) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_6_1;
        } else if (version_id == version_id_0_5_0) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_6_1;
        } else if (version_id == version_id_0_4_0) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_4_0;
        } else if (version_id == version_id_0_3_3) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_3;
        } else if (version_id == version_id_0_3_2) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_2;
        } else if (version_id == version_id_0_3_0) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_3_0;
        } else if (version_id == version_id_0_2_2) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_2;
        } else if (version_id == version_id_0_2_1) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_1;
        } else if (version_id == version_id_0_2_0) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_2_0;
        } else if (version_id == version_id_0_1_3) {
            minecraft_isgrabbed_offset = MINECRAFT_ISGRABBED_OFFSET_0_1_3;
        }
        
        if (*(bool *)(ninecraft_app+minecraft_isgrabbed_offset)) {
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
        ninecraft_app_update(ninecraft_app);
        
        if (!mouse_pointer_hidden) {
            if (version_id >= version_id_0_6_0) {
                float inv_gui_scale = *((float *)internal_dlsym(handle, "_ZN3Gui11InvGuiScaleE"));
                double xpos, ypos;
                glfwGetCursorPos(_window, &xpos, &ypos);
                short cx = (short)(xpos * inv_gui_scale);
                short cy = (short)(ypos * inv_gui_scale);
                ((NINECRAFT_FLOAT_FUNC void (*)(float, float, void *))internal_dlsym(handle, "_Z12renderCursorffP9Minecraft"))(cx, cy, ninecraft_app);
            }
        }
        audio_engine_tick();
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    return 0;
}
