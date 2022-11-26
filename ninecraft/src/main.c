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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ninecraft/gles_compat.h>
#include <ninecraft/minecraft_keys.h>
#include <ninecraft/android_string.h>
#include <ninecraft/symbols.h>
#include <ninecraft/AppPlatform_linux.h>
#include <ninecraft/audio_engine.h>
#include <ninecraft/hooks.h>
#include <math.h>

#include <hybris/dlfcn.h>
#include <hybris/hook.h>
#include <hybris/jb/linker.h>

const char *libs[] = {
    "libc.so",
    "libstdc++.so",
    "libm.so",
    "libandroid.so",
    "liblog.so",
    "libEGL.so",
    "libOpenSLES.so",
    "libGLESv1_CM.so"};

void *handle;
GLFWwindow* _window;

float y_cam = 0.0;
float x_cam = 0.0;

int window_width = 720;
int window_height = 480;

#ifdef __i386__

void detour(void *dst_addr, void *src_addr, bool jump) {
    uint32_t page_size = sysconf(_SC_PAGESIZE);
    void *protect = (void *)((uintptr_t)(dst_addr) & -page_size);
    mprotect(protect, 5, PROT_READ | PROT_WRITE | PROT_EXEC);
    uint32_t addr = ((uint32_t)src_addr) - ((uint32_t)dst_addr) - 5;
    *(uint8_t *)(dst_addr) = jump ? 0xE9 : 0xE8;
    *(uint32_t *)(((uint32_t)dst_addr) + 1) = addr;
    mprotect(protect, 5, PROT_EXEC);
}

#else

#ifdef __arm__

void detour(void *dst_addr, void *src_addr, bool jump) {
    long page_size = sysconf(_SC_PAGESIZE);
    void *protect = (void *)(((uintptr_t)dst_addr-1) & -page_size);
    mprotect(protect, 10, PROT_READ | PROT_WRITE | PROT_EXEC);
    uint32_t i = 0;
    if ((((uint32_t)dst_addr & 0xFFFFFFFE) % 4) != 0) {
        ((uint16_t *)((uint32_t)dst_addr & 0xFFFFFFFE))[i++] = 0xBF00;
    }
    ((uint16_t *)((uint32_t)dst_addr & 0xFFFFFFFE))[i++] = 0xF8DF;
    ((uint16_t *)((uint32_t)dst_addr & 0xFFFFFFFE))[i++] = 0xF000;
    ((uint16_t *)((uint32_t)dst_addr & 0xFFFFFFFE))[i++] = (uint32_t)src_addr & 0xFFFF;
    ((uint16_t *)((uint32_t)dst_addr & 0xFFFFFFFE))[i++] = (uint32_t)src_addr >> 16;
    mprotect(protect, 10, PROT_EXEC);
}

#else

void detour(void *dst_addr, void *src_addr, bool jump);

#endif

#endif

bool load_library(const char *path) {
    #ifdef __i386__
    char *arch = "x86";
    #else
    #ifdef __arm__
    char *arch = "arm";
    #else
    char *arch = "";
    #endif
    #endif
    char fullpath[MAXPATHLEN];
    getcwd(fullpath, MAXPATHLEN);
    strcat(fullpath, "/libs/");
    strcat(fullpath, arch);
    strcat(fullpath, "/");
    strcat(fullpath, path);

    void *handle = hybris_dlopen(fullpath, RTLD_LAZY);
    if (handle == NULL)
    {
        printf("failed to load library %s: %s\n", fullpath, hybris_dlerror());
        return false;
    }
    printf("lib: %s: : %p\n", fullpath, handle);
    return true;
}

void *load_minecraftpe()
{
    #ifdef __i386__
    char *arch = "x86";
    #else
    #ifdef __arm__
    char *arch = "arm";
    #else
    char *arch = "";
    #endif
    #endif
    char fullpath[MAXPATHLEN];
    getcwd(fullpath, MAXPATHLEN);
    strcat(fullpath, "/libs/");
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

void stub_symbols(const char **symbols, void *stub_func)
{
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

void android_stub()
{
    puts("warn: android call");
}

void egl_stub()
{
    //puts("warn: egl call");
}

void sles_stub()
{
    puts("warn: sles call");
}

void sound_engine_stub()
{
    // puts("warn: sound engine");
}

void *ninecraft_app;

struct KeyboardAction
{
    int action;
    int keyCode;
};

android_vector *keyboard_inputs;
static int *keyboard_states;

static unsigned char *controller_states;
static float *controller_x_stick;
static float *controller_y_stick;

audio_engine_t audio_engine;

static void minecraft_draw()
{
    ((void (*)(void *))hybris_dlsym(handle, "_ZN12NinecraftApp6updateEv"))(ninecraft_app);
}

bool mouse_pointer_hidden = false;

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
        ((void (*)(char, char, short, short, short, short))hybris_dlsym(handle, "_ZN5Mouse4feedEccssss"))((char) mc_button, (char) (action == GLFW_PRESS ? 1 : 0), (short)xpos, (short)ypos, 0, 0);
    } else {
        int game_keycode = mouseToGameKeyCode(button);
        
        if (action == GLFW_PRESS) {
            struct KeyboardAction action = {1, game_keycode};
            android_vector$push_back_2(keyboard_inputs, &action, handle);
            keyboard_states[game_keycode] = 1;
        } else if (action == GLFW_RELEASE) {
            struct KeyboardAction action = {0, game_keycode};
            android_vector$push_back_2(keyboard_inputs, &action, handle);
            keyboard_states[game_keycode] = 0;
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
    struct KeyboardAction action1 = {1, key_code};
    android_vector$push_back_2(keyboard_inputs, &action1, handle);
    keyboard_states[key_code] = 1;
    struct KeyboardAction action2 = {0, key_code};
    android_vector$push_back_2(keyboard_inputs, &action2, handle);
    keyboard_states[key_code] = 0;
}

static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!mouse_pointer_hidden) {
        ((void (*)(char, char, short, short, short, short))hybris_dlsym(handle, "_ZN5Mouse4feedEccssss"))(0, 0, (short)xpos, (short)ypos, 0, 0);
    } else {
        int cx;
        int cy;
        glfwGetWindowSize(window, &cx, &cy);
        cx /= 2;
        cy /= 2;
        if ((int)xpos != cy || (int)ypos != cy) {
            glfwSetCursorPos(window, cx, cy);
            y_cam -= ((float) ypos - (float)cy) / 6.0;
            x_cam += ((float)xpos - (float)cx) / 4.0;
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
    window_width = width;
    window_height = height;
    ((void (*)(void *, int, int))hybris_dlsym(handle, "_ZN9Minecraft7setSizeEii"))(ninecraft_app, width, height);
}

static void char_callback(GLFWwindow* window, unsigned int codepoint) {
    ((void (*)(char))hybris_dlsym(handle, "_ZN8Keyboard8feedTextEc"))((char)codepoint);
}

void mcinit()
{
    if (!*((int *)ninecraft_app + 183))
    {
        ((void (*)(void *))hybris_dlsym(handle, "_ZN9Minecraft12_reloadInputEv"))(ninecraft_app);
    }
}

int old_pos_x, old_pos_y, old_width, old_height;

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
        } else if (action == GLFW_PRESS) {
            struct KeyboardAction action = {1, game_keycode};
            android_vector$push_back_2(keyboard_inputs, &action, handle);
            keyboard_states[game_keycode] = 1;
        } else if (action == GLFW_RELEASE) {
            struct KeyboardAction action = {0, game_keycode};
            android_vector$push_back_2(keyboard_inputs, &action, handle);
            keyboard_states[game_keycode] = 0;
        }
    }
}

void window_close_callback(GLFWwindow* handle, GLFWwindowclosefun cbfun) {
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
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void sound_engine_playui(void *sound_engine, android_string *sound_name, float volume, float pitch) {
    audio_engine_play(&audio_engine, handle, sound_name->_M_start_of_storage, 0, 0, 0, volume, pitch, true);
}

void sound_engine_play(void *sound_engine, android_string *sound_name, float x, float y, float z, float volume, float pitch) {
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
    audio_engine_update(&audio_engine, 1, x, y, z, yaw);
}

android_string get_game_version() {
    android_string out;
    to_str(&out, "Ninecraft 1.0.0", handle);
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

void render_menu_background(void *screen) {
    void *minecraft = *(void **)(screen + 20);
    void *textures = *(void **)(minecraft + 688);
    android_string str;
    to_str(&str, "gui/bg32.png", handle);
    ((void (*)(void *, android_string *))hybris_dlsym(handle, "_ZN8Textures18loadAndBindTextureERKSs"))(textures, &str);
    ((void (*)(void *, int, int, int, int, int, int, int, int))hybris_dlsym(handle, "_ZN12GuiComponent4blitEiiiiiiii"))(screen, 0, 0, 0, 0, *(int *)(screen+8), *(int *)(screen+12), 0x100, 0x100);
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
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    _window = glfwCreateWindow(window_width, window_height, "Ninecraft", NULL, NULL);
    if (!_window) {
        puts("cant create");
    }
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwInit();
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    gles_hook();
    hybris_hook("__android_log_print", (void *)__android_log_print);
    stub_symbols(android_symbols, (void *)android_stub);
    stub_symbols(egl_symbols, (void *)egl_stub);
    stub_symbols(sles_symbols, (void *)sles_stub);
    
    int i;
    for (i = 0; i < 8; ++i)
    {
        load_library(libs[i]);
    }
    handle = load_minecraftpe();

    audio_engine_create_audio_device(&audio_engine);
    keyboard_inputs = (android_vector *)hybris_dlsym(handle, "_ZN8Keyboard7_inputsE");
    keyboard_states = (int *)hybris_dlsym(handle, "_ZN8Keyboard7_statesE");
    controller_states = (unsigned char *)hybris_dlsym(handle, "_ZN10Controller15isTouchedValuesE");
    controller_x_stick = (float *)hybris_dlsym(handle, "_ZN10Controller12stickValuesXE");
    controller_y_stick = (float *)hybris_dlsym(handle, "_ZN10Controller12stickValuesYE");

    unsigned char *dat = (unsigned char *)hybris_dlsym(handle, "_ZN15StartMenuScreenC1Ev");
    
    #ifdef __i386__
    dat[268] = 0xa0;
    #endif
    
    detour(hybris_dlsym(handle, "_ZN6Screen20renderDirtBackgroundEi"), (void *)render_menu_background, true);
    detour(hybris_dlsym(handle, "_ZN6Common20getGameVersionStringERKSs"), (void *)get_game_version, true);
    
    detour(hybris_dlsym(handle, "_ZN11SoundEngineC1Ef"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine4initEP9MinecraftP7Options"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine14_getVolumeMultEfff"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine7destroyEv"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine6enableEb"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine4playERKSsfffff"), (void *)sound_engine_play, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine6playUIERKSsff"), (void *)sound_engine_playui, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine6updateEP3Mobf"), (void *)sound_engine_update, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngine13updateOptionsEv"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngineD1Ev"), (void *)sound_engine_stub, true);
    detour(hybris_dlsym(handle, "_ZN11SoundEngineD2Ev"), (void *)sound_engine_stub, true);
    
    ninecraft_app = malloc(0xe6c);

    printf("app: %p\n", ninecraft_app);

    printf("%s\n", glGetString(GL_VERSION));

    NinecraftApp$construct ninecraft_app_construct = (NinecraftApp$construct)hybris_dlsym(handle, "_ZN12NinecraftAppC2Ev");
    printf("nine construct %p\n", ninecraft_app_construct);
    ninecraft_app_construct(ninecraft_app);

    ((void (*)(int, const char *))hybris_dlsym(handle, "_ZNSsaSEPKc"))((int)ninecraft_app + 3544, "./storage/internal/");
    ((void (*)(int, const char *))hybris_dlsym(handle, "_ZNSsaSEPKc"))((int)ninecraft_app + 3568, "./storage/external/");
    AppPlatform_linux platform;
    AppPlatform_linux$AppPlatform_linux(&platform, handle);
    *(uintptr_t *)(((int)ninecraft_app) + 0x14) = (uintptr_t)&platform;
    printf("%p\n", &platform);
    NinecraftApp$init ninecraft_app_init = (NinecraftApp$init)hybris_dlsym(handle, "_ZN12NinecraftApp4initEv");
    ninecraft_app_init(ninecraft_app);


    printf("%d\n", *(char *)(ninecraft_app+84));
    printf("%d\n", *(char *)(ninecraft_app+112));
    printf("%d\n", *(char *)(ninecraft_app+280));
    printf("%d\n", *(char *)(ninecraft_app+196));
    printf("%d\n", *(char *)(ninecraft_app+140));
    printf("%d\n", *(char *)(ninecraft_app+168));
    printf("%d\n", *(char *)(ninecraft_app+224));
    printf("%d\n", *(char *)(ninecraft_app+252));
    printf("%d\n", *(char *)(ninecraft_app+336));
    printf("%d\n", *(char *)(ninecraft_app+364));
    printf("%d\n", *(char *)(ninecraft_app+392));
    printf("%d\n", *(char *)(ninecraft_app+420));
    printf("%d\n", *(char *)(ninecraft_app+448));
    printf("%d\n", *(char *)(ninecraft_app+476));

    ((void (*)(void *, int, int))hybris_dlsym(handle, "_ZN9Minecraft7setSizeEii"))(ninecraft_app, 720, 480);

    glfwSetKeyCallback(_window, key_callback);
    glfwSetCharCallback(_window, char_callback);
    glfwSetMouseButtonCallback(_window, mouse_click_callback);
    glfwSetScrollCallback(_window, mouse_scroll_callback);
    glfwSetCursorPosCallback(_window, mouse_pos_callback);
    glfwSetWindowSizeCallback(_window, resize_callback);
    glfwSetWindowCloseCallback(_window, window_close_callback);

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
        minecraft_draw();
        
        if (!mouse_pointer_hidden) {
            float inv_gui_scale = *((float *)hybris_dlsym(handle, "_ZN3Gui11InvGuiScaleE"));
            short cx = (short)((float)((short (*)())hybris_dlsym(handle, "_ZN5Mouse4getXEv"))() * inv_gui_scale);
            short cy = (short)((float)((short (*)())hybris_dlsym(handle, "_ZN5Mouse4getYEv"))() * inv_gui_scale);
            ((void (*)(float, float, void *))hybris_dlsym(handle, "_Z12renderCursorffP9Minecraft"))(cx, cy, ninecraft_app);
        }
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    return 0;
}
