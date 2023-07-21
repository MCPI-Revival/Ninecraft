#ifndef NINECRAFT_APP_CONTEXT_H
#define NINECRAFT_APP_CONTEXT_H

typedef struct {
    void *egl_display;
    void *egl_context;
    void *egl_surface;
    void *unknown;
    void *platform;
    bool do_render;
} app_context_0_9_0_t;

#endif