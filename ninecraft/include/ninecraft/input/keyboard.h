#ifndef NINECRAFT_INPUT_KEYBOARD_H
#define NINECRAFT_INPUT_KEYBOARD_H

#include <ninecraft/android/android_vector.h>

extern android_vector_t *keyboard_inputs;
extern int *keyboard_states;

void keyboard_setup_hooks(void *handle);

void keyboard_feed(unsigned char key, int state);

#endif