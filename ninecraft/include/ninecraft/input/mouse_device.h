#ifndef NINECRAFT_INPUT_MOUSE_DEVICE_H
#define NINECRAFT_INPUT_MOUSE_DEVICE_H

#include <ninecraft/android/android_vector.h>

typedef struct {
    int event_index;
    short x;
    short y;
    short old_x;
    short old_y;
    char button_states[4];
    android_vector_t actions;
} mouse_device_0_1_t;

typedef struct {
    int event_index;
    short x;
    short y;
    short old_x;
    short old_y;
    char button_states[4];
    android_vector_t actions;
    int last_pressed;
} mouse_device_0_2_1_t;

typedef struct {
    int event_index;
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

extern void mouse_device_feed_0_1(mouse_device_0_1_t *mouse_device, char button, char type, short x, short y);

extern void mouse_device_feed_0_2_1(mouse_device_0_2_1_t *mouse_device, char button, char type, short x, short y);

extern void mouse_device_feed_0_6(mouse_device_0_6_t *mouse_device, char button, char type, short x, short y, short dx, short dy);

#endif