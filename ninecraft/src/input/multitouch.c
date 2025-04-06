#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/input/action/mouse_action.h>
#include <ninecraft/input/mouse_device.h>
#include <ninecraft/input/multitouch.h>

void *multitouch_pointers = NULL;
char *multitouch_released = NULL;
char *multitouch_released_ut = NULL;
char *multitouch_pressed = NULL;
char *multitouch_pressed_ut = NULL;
android_vector_t *multitouch_inputs = NULL;

void multitouch_setup_hooks(void *handle) {
    multitouch_pointers = (void *)internal_dlsym(handle, "_ZN10Multitouch9_pointersE");
    multitouch_released = (char *)internal_dlsym(handle, "_ZN10Multitouch12_wasReleasedE");
    multitouch_released_ut = (char *)internal_dlsym(handle, "_ZN10Multitouch22_wasReleasedThisUpdateE");
    multitouch_pressed = (char *)internal_dlsym(handle, "_ZN10Multitouch11_wasPressedE");
    multitouch_pressed_ut = (char *)internal_dlsym(handle, "_ZN10Multitouch21_wasPressedThisUpdateE");
    multitouch_inputs = (android_vector_t *)internal_dlsym(handle, "_ZN10Multitouch7_inputsE");
}

void multitouch_feed_0_5(char button, char type, short x, short y, char pointer_id) {
    mouse_action_0_5_t action;
    action.x = x;
    action.y = y;
    action.pointer_id = pointer_id;
    action.button = button;
    action.type = type;

    android_vector_push_back(multitouch_inputs, &action, sizeof(mouse_action_0_5_t));

    mouse_device_feed_0_5((mouse_device_0_5_t *)((char *)multitouch_pointers + (action.pointer_id * sizeof(mouse_device_0_5_t))), action.button, action.type, action.x, action.y);
    
    if (action.button) {
        if (action.type == 1) {
            multitouch_pressed[action.pointer_id] = 1;
            multitouch_pressed_ut[action.pointer_id] = 1;
        } else if (action.type == 0) {
            multitouch_released[action.pointer_id] = 1;
            multitouch_released_ut[action.pointer_id] = 1;
        }
    }
}

void multitouch_feed_0_6(char button, char type, short x, short y, char pointer_id) { 
    mouse_action_0_6_t action;
    action.x = x;
    action.y = y;
    action.dx = 0;
    action.dy = 0;
    action.pointer_id = pointer_id;
    action.button = button;
    action.type = type;

    android_vector_push_back(multitouch_inputs, &action, sizeof(mouse_action_0_6_t));

    mouse_device_feed_0_6((mouse_device_0_6_t *)((char *)multitouch_pointers + (action.pointer_id * sizeof(mouse_device_0_6_t))), action.button, action.type, action.x, action.y, action.dx, action.dy);
    
    if (action.button) {
        if (action.type == 1) {
            multitouch_pressed[action.pointer_id] = 1;
            multitouch_pressed_ut[action.pointer_id] = 1;
        } else if (action.type == 0) {
            multitouch_released[action.pointer_id] = 1;
            multitouch_released_ut[action.pointer_id] = 1;
        }
    }
}