#include <ninecraft/input/action/keyboard_action.h>
#include <ninecraft/input/keyboard.h>

android_vector_t *keyboard_inputs = NULL;
int *keyboard_states = NULL;

void keyboard_feed(unsigned char key, int state, void *handle) {
    keyboard_action_t action;
    action.state = state;
    action.key = (int)key;
    android_vector_push_back(keyboard_inputs, &action, sizeof(keyboard_action_t), handle);
    keyboard_states[key] = state;
}