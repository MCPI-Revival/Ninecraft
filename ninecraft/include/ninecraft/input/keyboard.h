#ifndef NINECRAFT_INPUT_KEYBOARD_H
#define NINECRAFT_INPUT_KEYBOARD_H

#include <ninecraft/android/android_vector.h>

extern android_vector_t *keyboard_inputs;
extern android_vector_t *keyboard_input_text;
extern int *keyboard_states;

extern void keyboard_setup_hooks(void *handle);

extern void keyboard_feed(unsigned char key, int state);

#endif