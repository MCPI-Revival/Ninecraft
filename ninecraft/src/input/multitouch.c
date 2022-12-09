#include <ninecraft/input/action/mouse_action.h>
#include <ninecraft/input/mouse_device.h>
#include <ninecraft/input/multitouch.h>

void multitouch_feed_0_5(char button, char type, short x, short y, char pointer_id, void *handle) {
    void *pointers = hybris_dlsym(handle, "_ZN10Multitouch9_pointersE");
    char *released = hybris_dlsym(handle, "_ZN10Multitouch12_wasReleasedE");
    char *released_ut = hybris_dlsym(handle, "_ZN10Multitouch22_wasReleasedThisUpdateE");
    char *pressed = hybris_dlsym(handle, "_ZN10Multitouch11_wasPressedE");
    char *pressed_ut = hybris_dlsym(handle, "_ZN10Multitouch21_wasPressedThisUpdateE");
    android_vector *inputs = (android_vector *)hybris_dlsym(handle, "_ZN10Multitouch7_inputsE");
    
    mouse_action_0_5_t action;
    action.x = x;
    action.y = y;
    action.pointer_id = pointer_id;
    action.button = button;
    action.type = type;

    android_vector$push_back_2(inputs, &action, handle);

    mouse_device_feed_0_5(pointers + (action.pointer_id * sizeof(mouse_device_0_5_t)), action.button, action.type, action.x, action.y, handle);
    
    if (action.button) {
        if (action.type == 1) {
            pressed[action.pointer_id] = 1;
            pressed_ut[action.pointer_id] = 1;
        } else if (action.type == 0) {
            released[action.pointer_id] = 1;
            released_ut[action.pointer_id] = 1;
        }
    }
}

void multitouch_feed_0_6(char button, char type, short x, short y, char pointer_id, void *handle) {
    void *pointers = hybris_dlsym(handle, "_ZN10Multitouch9_pointersE");
    char *released = hybris_dlsym(handle, "_ZN10Multitouch12_wasReleasedE");
    char *released_ut = hybris_dlsym(handle, "_ZN10Multitouch22_wasReleasedThisUpdateE");
    char *pressed = hybris_dlsym(handle, "_ZN10Multitouch11_wasPressedE");
    char *pressed_ut = hybris_dlsym(handle, "_ZN10Multitouch21_wasPressedThisUpdateE");
    android_vector *inputs = (android_vector *)hybris_dlsym(handle, "_ZN10Multitouch7_inputsE");
    
    mouse_action_0_6_t action;
    action.x = x;
    action.y = y;
    action.dx = 0;
    action.dy = 0;
    action.pointer_id = pointer_id;
    action.button = button;
    action.type = type;

    android_vector$push_back_3(inputs, &action, handle);

    mouse_device_feed_0_6(pointers + (action.pointer_id * sizeof(mouse_device_0_6_t)), action.button, action.type, action.x, action.y, action.dx, action.dy, handle);
    
    if (action.button) {
        if (action.type == 1) {
            pressed[action.pointer_id] = 1;
            pressed_ut[action.pointer_id] = 1;
        } else if (action.type == 0) {
            released[action.pointer_id] = 1;
            released_ut[action.pointer_id] = 1;
        }
    }
}