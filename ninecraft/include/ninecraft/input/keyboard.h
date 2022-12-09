#ifndef NINECRAFT_INPUT_KEYBOARD_H
#define NINECRAFT_INPUT_KEYBOARD_H

#include <ninecraft/android_vector.h>

extern android_vector *keyboard_inputs;
extern int *keyboard_states;

void keyboard_feed(unsigned char key, int state, void *handle);

#endif