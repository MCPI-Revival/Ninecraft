#ifndef NINECRAFT_INPUT_ACTION_MOUSE_ACTION_H
#define NINECRAFT_INPUT_ACTION_MOUSE_ACTION_H

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

#endif