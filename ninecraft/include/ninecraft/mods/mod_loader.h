#ifndef NINECRAFT_MODS_MOD_LOADER_H
#define NINECRAFT_MODS_MOD_LOADER_H

extern void mod_loader_execute_on_minecraft_construct(void *minecraft, int version_id);

extern void mod_loader_execute_on_minecraft_init(void *minecraft, int version_id);

extern void mod_loader_execute_on_minecraft_update(void *minecraft, int version_id);

extern void mod_loader_execute_on_minecraft_grab_mouse(void *minecraft, int version_id);

extern void mod_loader_execute_on_minecraft_release_mouse(void *minecraft, int version_id);

// Give mods ability to fire functions upon keys being pressed or released
extern void mod_loader_execute_on_key(int key, int action);

extern void mod_loader_load_all(void *minecraft_handle, int version_id);

#endif
