#include <ninecraft/dlfcn_stub.h>
#include <ancmp/android_dlfcn.h>

void *internal_dlsym(void *handle, char *symbol) {
    return android_dlsym(handle, symbol);
}

void *internal_dlopen(char *filename, int flag) {
    return android_dlopen(filename, flag);
}

const char *internal_dlerror() {
    return android_dlerror();
}