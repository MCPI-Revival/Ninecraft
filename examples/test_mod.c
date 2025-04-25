#include <stdio.h>

void ninecraft_mod_on_load(void *minecraft_handle, int version_id) {
    puts("[test_mod] loaded");
}

void ninecraft_mod_on_minecraft_construct(void *minecraft, int version_id) {
    puts("[test_mod] minecraft constructed");
}

void ninecraft_mod_on_minecraft_init(void *minecraft, int version_id) {
    puts("[test_mod] minecraft initialized");
}

void ninecraft_mod_on_minecraft_update(void *minecraft, int version_id) {
    //puts("[test_mod] minecraft updated");
}

void ninecraft_mod_on_minecraft_grab_mouse(void *minecraft, int version_id) {
    puts("[test_mod] minecraft grabbed the mouse");
}

void ninecraft_mod_on_minecraft_release_mouse(void *minecraft, int version_id) {
    puts("[test_mod] minecraft released the mouse");
}