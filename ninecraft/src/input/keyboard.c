#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/input/action/keyboard_action.h>
#include <ninecraft/input/keyboard.h>

android_vector_t *keyboard_inputs = NULL;
int *keyboard_states = NULL;

void keyboard_setup_hooks(void *handle) {
    keyboard_inputs = (android_vector_t *)internal_dlsym(handle, "_ZN8Keyboard7_inputsE");
    keyboard_states = (int *)internal_dlsym(handle, "_ZN8Keyboard7_statesE");
}

void keyboard_feed(unsigned char key, int state) {
    keyboard_action_t action;
    action.state = state;
    action.key = (int)key;
    android_vector_push_back(keyboard_inputs, &action, sizeof(keyboard_action_t));
    keyboard_states[key] = state;
}