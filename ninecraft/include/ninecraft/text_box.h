#ifndef NINECRAFT_TEXT_BOX
#define NINECRAFT_TEXT_BOX

#include <ninecraft/android/android_string.h>
#include <stdbool.h>

typedef struct {
    void **vtable;
    float z_coord;
    int x;
    int y;
    int width;
    int height;
    char *text;
    size_t text_len;
    char *placeholder;
    bool is_focused;
    bool is_modifyable;
    bool is_finished;
} text_box_t;

void text_box_construct(text_box_t *__this);

bool text_box_is_hovered(text_box_t *__this, int x, int y);

void text_box_set_focused(text_box_t *__this, bool is_focused);

void text_box_keyboard_new_char(text_box_t *__this, char c);

void text_box_keyboard_key_pressed(text_box_t *__this, char code);

void text_box_render(text_box_t *__this, void *minecraft, int x, int y);

#endif