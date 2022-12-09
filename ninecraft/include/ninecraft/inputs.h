#pragma once

#include <ninecraft/android_vector.h>

typedef struct {
    int action;
    int keyCode;
} keyboard_action_t;

typedef struct {
    short x;
    short y;
    short dx;
    short dy;
    char button;
    char type;
    char pointer_id;
} mouse_action_0_6_t;

typedef struct {
    short x;
    short y;
    char button;
    char type;
    char pointer_id;
} mouse_action_0_5_t;

typedef struct {
    void *vtable;
    short x;
    short y;
    short old_x;
    short old_y;
    char button_states[4];
    android_vector actions;
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
    android_vector actions;
    int last_pressed;
} mouse_device_0_6_t;