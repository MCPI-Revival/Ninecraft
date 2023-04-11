#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/input/action/keyboard_action.h>
#include <ninecraft/input/keyboard.h>
#include <ninecraft/android/android_alloc.h>

android_vector_t *keyboard_inputs = NULL;
android_vector_t *keyboard_input_text = NULL;
int *keyboard_states = NULL;

void keyboard_setup_hooks(void *handle) {
    keyboard_inputs = (android_vector_t *)internal_dlsym(handle, "_ZN8Keyboard7_inputsE");
    keyboard_input_text = (android_vector_t *)internal_dlsym(handle, "_ZN8Keyboard10_inputTextE");
    keyboard_states = (int *)internal_dlsym(handle, "_ZN8Keyboard7_statesE");
}

void keyboard_feed(unsigned char key, int state) {
    keyboard_action_t action;
    action.state = state;
    action.key = (int)key;
    android_vector_push_back(keyboard_inputs, &action, sizeof(keyboard_action_t));
    keyboard_states[key] = state;
}

void keyboard_feed_text_0_6_0(char c) {
    android_vector_push_back(keyboard_input_text, &c, 1);
}

void keyboard_feed_text_0_7_2(android_string_t *text, bool replace_last) {
    if (android_alloc_node_alloc != NULL) {
        keyboard_text_input_stlp_t kti;
        kti.text = text->stlp;
        kti.replace_last = replace_last;
        android_vector_push_back(keyboard_input_text, &kti, sizeof(keyboard_text_input_stlp_t));
    } else {
        keyboard_text_input_gnu_t kti;
        kti.text = text->gnu;
        kti.replace_last = replace_last;
        android_vector_push_back(keyboard_input_text, &kti, sizeof(keyboard_text_input_gnu_t));
    }
}
    