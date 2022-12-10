#ifndef NINECRAFT_DLFCN_STUB_H
#define NINECRAFT_DLFCN_STUB_H

void *internal_dlsym(void *handle, char *symbol);

void *internal_dlopen(char *filename, int flag);

const char *internal_dlerror();

#endif