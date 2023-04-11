#ifndef NINECRAFT_INPUT_KEYBOARD_H
#define NINECRAFT_INPUT_KEYBOARD_H

#include <ninecraft/android/android_vector.h>

typedef struct {
    android_string_gnu_t text;
    bool replace_last;
} keyboard_text_input_gnu_t;

typedef struct {
    android_string_stlp_t text;
    bool replace_last;
} keyboard_text_input_stlp_t;

typedef union {
    keyboard_text_input_gnu_t gnu;
    keyboard_text_input_stlp_t stlp;
} keyboard_text_input_t;

extern android_vector_t *keyboard_inputs;
extern android_vector_t *keyboard_input_text;
extern int *keyboard_states;

extern void keyboard_setup_hooks(void *handle);

extern void keyboard_feed(unsigned char key, int state);

extern void keyboard_feed_text_0_6_0(char c);

extern void keyboard_feed_text_0_7_2(android_string_t *text, bool replace_last);

#endif