#include <dlfcn.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <hybris/dlfcn.h>
#include <hybris/hook.h>
#include <hybris/jb/linker.h>
#include <cstdlib>
#include <ninecraft/android_string.hpp>

char *to_str(void *str, char *cstr, void *handle) {
    size_t length = strlen(cstr);
    *(void **)(str + 16) = str;
    *(void **)(str + 20) = str;
    ((void (*)(void *, unsigned int)) hybris_dlsym(handle, "_ZNSt4priv12_String_baseIcSaIcEE17_M_allocate_blockEj"))(str, length + 1);
    char *pcstr = *(char **)(str + 20);
    memcpy(pcstr, cstr, length);
    *(void **)(str + 16) = pcstr + length;
    pcstr[length] = 0;
}