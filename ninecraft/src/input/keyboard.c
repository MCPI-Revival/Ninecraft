#include <ninecraft/input/action/keyboard_action.h>
#include <ninecraft/input/keyboard.h>

android_vector *keyboard_inputs = NULL;
int *keyboard_states = NULL;

void keyboard_feed(unsigned char key, int state, void *handle) {
    keyboard_action_t action;
    action.state = state;
    action.key = (int)key;
    android_vector$push_back_2(keyboard_inputs, &action, handle);
    keyboard_states[key] = state;
}