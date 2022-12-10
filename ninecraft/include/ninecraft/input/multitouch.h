#ifndef NINECRAFT_INPUT_MULTITOUCH_H
#define NINECRAFT_INPUT_MULTITOUCH_H

extern void *multitouch_pointers;
extern char *multitouch_released;
extern char *multitouch_released_ut;
extern char *multitouch_pressed;
extern char *multitouch_pressed_ut;
extern android_vector_t *multitouch_inputs;

extern void multitouch_setup_hooks(void *handle);

extern void multitouch_feed_0_5(char button, char type, short x, short y, char pointer_id);

extern void multitouch_feed_0_6(char button, char type, short x, short y, char pointer_id);

#endif