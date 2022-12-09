#include <hybris/dlfcn.h>
#include <ninecraft/input/action/mouse_action.h>
#include <ninecraft/input/mouse_device.h>

void mouse_device_feed_0_5(mouse_device_0_5_t *mouse_device, char button, char type, short x, short y, void *handle) {
    mouse_action_0_5_t action;
    action.x = x;
    action.y = y;
    action.button = button;
    action.type = type;
    action.pointer_id = 0;

    android_vector_push_back(&mouse_device->actions, &action, sizeof(mouse_action_0_5_t), handle);
    
    if (button) {
        mouse_device->button_states[button] = type;
        if (button == 1) {
            mouse_device->last_pressed = -1;
        }
    } else {
        mouse_device->last_pressed = mouse_device->last_pressed == -1;
    }

    mouse_device->old_x = mouse_device->x;
    mouse_device->old_y = mouse_device->y;
    mouse_device->x = x;
    mouse_device->y = y;
}

void mouse_device_feed_0_6(mouse_device_0_6_t *mouse_device, char button, char type, short x, short y, short dx, short dy, void *handle) {
    mouse_action_0_6_t action;
    action.x = x;
    action.y = y;
    action.dx = dx;
    action.dy = dy;
    action.button = button;
    action.type = type;
    action.pointer_id = 0;

    android_vector_push_back(&mouse_device->actions, &action, sizeof(mouse_action_0_6_t), handle);
    
    if (button) {
        mouse_device->button_states[button] = type;
        if (button == 1) {
            mouse_device->last_pressed = -1;
        }
    } else {
        if (mouse_device->dx == -9999) {
            mouse_device->dx = 0;
            mouse_device->dy = 0;
        }
        mouse_device->dx += dx;
        mouse_device->dy += dy;

        mouse_device->last_pressed = mouse_device->last_pressed == -1;
    }

    mouse_device->old_x = mouse_device->x;
    mouse_device->old_y = mouse_device->y;
    mouse_device->x = x;
    mouse_device->y = y;
}