#include <ninecraft/dlfcn_stub.h>
#include <hybris/dlfcn.h>

void *internal_dlsym(void *handle, char *symbol) {
    return hybris_dlsym(handle, symbol);
}

void *internal_dlopen(char *filename, int flag) {
    return hybris_dlopen(filename, flag);
}

const char *internal_dlerror() {
    return hybris_dlerror();
}