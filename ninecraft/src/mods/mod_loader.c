#include <dlfcn.h>
#include <stdlib.h>
#include <sys/param.h>
#include <dirent.h>
#include <ninecraft/mods/mod_loader.h>
#include <string.h>
#include <stdio.h>

void **mod_handles = NULL;
size_t mod_handles_count = 0;

#define MOD_ERROR(path, reason) printf("Failed to load mod %s due to %s\n", path, reason)

void mod_loader_load(char *path) {
    void *handle = dlopen(path, RTLD_NOW);
    if (handle == NULL) {
        MOD_ERROR(path, dlerror());
        return;
    }
    void *init_addr = dlsym(handle, "mod_init");
    if (init_addr == NULL) {
        MOD_ERROR(path, dlerror());
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
    char mods_path[MAXPATHLEN];
    getcwd(mods_path, MAXPATHLEN);
    strcat(mods_path, "/mods/");
    
    DIR *dp = opendir(mods_path);
    if (dp == NULL) {
        puts("Failed to load mods");
    }
    
    struct dirent *entry;

    while((entry = readdir(dp))) {
        char mod_path[MAXPATHLEN];
        strcpy(mod_path, mods_path);
        strcat(mod_path, entry->d_name);

        if (strncmp(mod_path + (strlen(mod_path) - 3), ".so", 3) == 0) {
            mod_loader_load(mod_path);
        }
    }
    
    closedir(dp);
}