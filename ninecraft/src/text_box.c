#include <ninecraft/text_box.h>
#include <ninecraft/minecraft.h>
#include <ninecraft/version_ids.h>
#include <ancmp/android_dlfcn.h>
#include <time.h>
#include <stdlib.h>
#include <ninecraft/input/minecraft_keys.h>

extern int version_id;
extern void *handle;

void text_box_construct(text_box_t *__this) {
    ((void (*)(void *__this))android_dlsym(handle, "_ZN12GuiComponentC2Ev"))(__this);
    __this->is_modifyable = true;
    __this->x = 0;
    __this->y = 0;
    __this->width = 200;
    __this->height = 18;
    __this->text = NULL;
    __this->text_len = 0;
    __this->is_focused = false;
    __this->is_finished = false;
    __this->placeholder = "";
}

bool text_box_is_hovered(text_box_t *__this, int x, int y) {
    return __this->x <= x && __this->y <= y && (__this->x + __this->width) > x && (__this->y + __this->height) > y;
}

void text_box_set_focused(text_box_t *__this, bool is_focused) {
    if (__this->is_modifyable) {
        __this->is_focused = is_focused;
    }
}

void text_box_keyboard_new_char(text_box_t *__this, char c) {
    if (__this->is_modifyable && __this->is_focused) {
        if (!__this->text || !__this->text_len) {
            __this->text = (char *)malloc(2);
            __this->text_len = 0;
        } else {
            __this->text = (char *)realloc(__this->text, __this->text_len + 2);
        }
        __this->text[__this->text_len++] = c;
        __this->text[__this->text_len] = '\0';
    }
}

void text_box_keyboard_key_pressed(text_box_t *__this, char code) {
    if (__this->is_modifyable && __this->is_focused) {
        if (code == MCKEY_SIGN_ENTER) {
            __this->is_finished = true;
            __this->is_focused = false;
        } else if (code == MCKEY_SIGN_BACKSPACE) {
            if (__this->text && __this->text_len != 0) {
                __this->text = (char *)realloc(__this->text, __this->text_len--);
                __this->text[__this->text_len] = '\0';
            }
        }
    }
}

void text_box_render(text_box_t *__this, void *minecraft, int x, int y) {
    android_string_t str;
    bool is_hovered = text_box_is_hovered(__this, x, y);
    int box_outline_color = 0xff676060;
    if (__this->is_modifyable) {
        if (is_hovered){
            box_outline_color = 0xffc0c000;
        } else if (__this->is_focused) {
            box_outline_color = 0xffffffff;
        }
    }
    gui_component_fill(__this, __this->x, __this->y, __this->x + __this->width, __this->y + __this->height, 0xff373535);
    gui_component_draw_rect(__this, __this->x, __this->y, __this->x + __this->width, __this->y + __this->height, box_outline_color, 1);
    if (__this->text && __this->text_len != 0) {
        android_string_cstrl(&str, __this->text, __this->text_len);
    } else if (!__this->is_focused && __this->placeholder) {
        android_string_cstr(&str, __this->placeholder);
        ((void (*)(void *__this, android_string_t *text, float x, float y, int z, bool u))android_dlsym(handle, "_ZN4Font4drawERKSsffib"))(*((void **)minecraft + 174), &str, __this->x + 10.0, __this->y + 5.0, 0xff808080, false);
        android_string_destroy(&str);
    }
    if (time(NULL) & 1 && __this->is_focused && __this->is_modifyable) {
        int text_w = 0;
        if (__this->text && __this->text_len != 0) {
            text_w = ((int (*)(void *__this, android_string_t *text))android_dlsym(handle, "_ZN4Font5widthERKSs"))(*((void **)minecraft + 174), &str);
        }
        android_string_t str2;
        android_string_cstr(&str2, "_");
        ((void (*)(void *__this, android_string_t *text, float x, float y, int z, bool u))android_dlsym(handle, "_ZN4Font4drawERKSsffib"))(*((void **)minecraft + 174), &str2, __this->x + 10.0 + text_w, __this->y + 5.0, __this->is_focused ? 0xffffffff : 0xffBBBBBB, false);
        android_string_destroy(&str2);
    }
    if (__this->text && __this->text_len != 0) {
        ((void (*)(void *__this, android_string_t *text, float x, float y, int z, bool u))android_dlsym(handle, "_ZN4Font4drawERKSsffib"))(*((void **)minecraft + 174), &str, __this->x + 10.0, __this->y + 5.0, __this->is_modifyable ? (__this->is_focused ? 0xffffffff : 0xffBBBBBB) : 0xff606060, false);
        android_string_destroy(&str);
    }
}