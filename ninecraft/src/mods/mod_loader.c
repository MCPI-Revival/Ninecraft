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

void **mod_handles = NULL;
size_t mod_handles_count = 0;

#define MOD_ERROR(path, reason) printf("Failed to load mod %s due to %s\n", path, reason)

void mod_loader_load(char *path) {
    void *handle = android_dlopen(path, ANDROID_RTLD_NOW);
    if (handle == NULL) {
        MOD_ERROR(path, android_dlerror());
        return;
    }
    void *init_addr = android_dlsym(handle, "mod_init");
    if (init_addr == NULL) {
        MOD_ERROR(path, android_dlerror());
        return;
    }
    if (mod_handles == NULL || mod_handles_count == 0) {
        mod_handles = (void **)malloc(sizeof(void *));
        mod_handles_count = 1;
        mod_handles[0] = handle;
    } else {
        mod_handles = realloc(mod_handles, ++mod_handles_count * sizeof(void *));
        mod_handles[mod_handles_count - 1] = handle;
    }
    ((void (*)(void))init_addr)();
    printf("Loaded mod: %s\n", path);
}

void mod_loader_load_all() {
    char *mods_path = (char *)malloc(1024);
    mods_path[0] = '\0';
    getcwd(mods_path, 1024);
    strcat(mods_path, "/mods/");
    
    android_DIR *dp = android_opendir(mods_path);
    if (dp == NULL) {
        puts("Failed to load mods");
    }
    
    android_dirent_t *entry;

    while((entry = android_readdir(dp))) {
        char *mod_path = (char *)malloc(1024);
        mod_path[0] = '\0';
        strcpy(mod_path, mods_path);
        strcat(mod_path, entry->d_name);

        if (strncmp(mod_path + (strlen(mod_path) - 3), ".so", 3) == 0) {
            mod_loader_load(mod_path);
        }
        free(mod_path);
    }
    free(mods_path);
    
    android_closedir(dp);
}