#ifndef NINECRAFT_INPUT_MOUSE_DEVICE_H
#define NINECRAFT_INPUT_MOUSE_DEVICE_H

#include <ninecraft/android/android_vector.h>

typedef struct {
    void *vtable;
    short x;
    short y;
    short old_x;
    short old_y;
    char button_states[4];
    android_vector_t actions;
    int last_pressed;
} mouse_device_0_5_t;

typedef struct {
    void *vtable;
    short x;
    short y;
    short dx;
    short dy;
    short old_x;
    short old_y;
    char button_states[4];
    android_vector_t actions;
    int last_pressed;
} mouse_device_0_6_t;

void mouse_device_feed_0_5(mouse_device_0_5_t *mouse_device, char button, char type, short x, short y, void *handle);

void mouse_device_feed_0_6(mouse_device_0_6_t *mouse_device, char button, char type, short x, short y, short dx, short dy, void *handle);

#endif