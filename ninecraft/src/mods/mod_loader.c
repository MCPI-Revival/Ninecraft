#include <stdlib.h>
#include <ancmp/android_dirent.h>
#include <ninecraft/mods/mod_loader.h>
#include <string.h>
#include <stdio.h>
#include <ancmp/android_dlfcn.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

typedef struct _ninecraft_mods_t {
    struct _ninecraft_mods_t *next;
    void *handle;
} ninecraft_mods_t;

ninecraft_mods_t *ninecraft_mods = NULL;

#define MOD_ERROR(path, reason) printf("Failed to load mod %s due to %s\n", path, reason)

void mod_loader_execute_on_minecraft_construct(void *minecraft, int version_id) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_construct = android_dlsym(mod->handle, "ninecraft_mod_on_minecraft_construct");
            if (on_minecraft_construct) {
                ((void (*)(void *, int))on_minecraft_construct)(minecraft, version_id);
            }
        }
    }
}

void mod_loader_execute_on_minecraft_init(void *minecraft, int version_id) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_init = android_dlsym(mod->handle, "ninecraft_mod_on_minecraft_init");
            if (on_minecraft_init) {
                ((void (*)(void *, int))on_minecraft_init)(minecraft, version_id);
            }
        }
    }
}

void mod_loader_execute_on_minecraft_update(void *minecraft, int version_id) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_update = android_dlsym(mod->handle, "ninecraft_mod_on_minecraft_update");
            if (on_minecraft_update) {
                ((void (*)(void *, int))on_minecraft_update)(minecraft, version_id);
            }
        }
    }
}

void mod_loader_execute_on_minecraft_grab_mouse(void *minecraft, int version_id) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_grab_mouse = android_dlsym(mod->handle, "ninecraft_mod_on_minecraft_grab_mouse");
            if (on_minecraft_grab_mouse) {
                ((void (*)(void *, int))on_minecraft_grab_mouse)(minecraft, version_id);
            }
        }
    }
}

void mod_loader_execute_on_minecraft_release_mouse(void *minecraft, int version_id) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_release_mouse = android_dlsym(mod->handle, "ninecraft_mod_on_minecraft_release_mouse");
            if (on_minecraft_release_mouse) {
                ((void (*)(void *, int))on_minecraft_release_mouse)(minecraft, version_id);
            }
        }
    }
}


// Give mods ability to fire functions upon keys being pressed or released
void mod_loader_execute_on_key(int key, int action) {
    for (ninecraft_mods_t *mod = ninecraft_mods; mod != NULL; mod = mod->next) {
        if (mod->handle) {
            void *on_minecraft_key = android_dlsym(mod->handle, "ninecraft_mod_on_key");
            if (on_minecraft_key) {
                ((void (*)(int, int))on_minecraft_key)(key, action);
            }
        }
    }
}


void mod_loader_load_all(void *minecraft_handle, int version_id) {
    char *mods_path = (char *)malloc(1024);
    mods_path[0] = '\0';
    getcwd(mods_path, 1024);
    strcat(mods_path, "/mods/");
    
    android_DIR *dp = android_opendir(mods_path);
    if (dp == NULL) {
        puts("Failed to load mods");
    }
    size_t mods_path_len = strlen(mods_path);
    
    android_dirent_t *entry;

    while((entry = android_readdir(dp))) {
        if (entry->d_type == ANDROID_DT_REG) {
            size_t mod_path_len = mods_path_len + strlen(entry->d_name);
            char *mod_path = (char *)malloc(mod_path_len + 1);
            mod_path[0] = '\0';
            strcpy(mod_path, mods_path);
            strcat(mod_path, entry->d_name);
            mod_path[mod_path_len] = '\0';
            puts(mod_path);

            if (strncmp(mod_path + (strlen(mod_path) - 3), ".so", 3) == 0) {
                void *mod_handle = android_dlopen(mod_path, ANDROID_RTLD_NOW);
                if (!mod_handle) {
                    MOD_ERROR(entry->d_name, android_dlerror()); 
                } else {
                    ninecraft_mods_t *mod = (ninecraft_mods_t *)malloc(sizeof(ninecraft_mods_t));
                    if (mod) {
                        mod->next = ninecraft_mods;
                        mod->handle = mod_handle;
                        ninecraft_mods = mod;
                        void *on_load_func = android_dlsym(mod_handle, "ninecraft_mod_on_load");
                        if (on_load_func) {
                            ((void (*)(void *, int))on_load_func)(minecraft_handle, version_id);
                        }
                    } else {
                        MOD_ERROR(entry->d_name, "malloc failed"); 
                    }
                }
            }
            free(mod_path);
        }
    }
    free(mods_path);
    
    android_closedir(dp);
}
