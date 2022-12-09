#include <hybris/dlfcn.h>
#include <ninecraft/android/android_alloc.h>

void *android_alloc_allocate(size_t *__np, void *handle) {
    size_t __n = *__np;
    if (__n < 0x81) {
        return ((void *(*)(size_t *))hybris_dlsym(handle, "_ZNSt17__node_alloc_impl11_M_allocateERj"))(__np);
    }
    return ((void *(*)(size_t))hybris_dlsym(handle, "_Znwj"))(__n);
}

void android_alloc_deallocate(void *ptr, size_t __n, void *handle) {
    if (__n < 0x81) {
        ((void (*)(void *, size_t))hybris_dlsym(handle, "_ZNSt17__node_alloc_impl13_M_deallocateEPvj"))(ptr, __n);
    } else {
        ((void (*)(void *))hybris_dlsym(handle, "_ZdlPv"))(ptr);
    }
}