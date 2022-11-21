#include <hybris/dlfcn.h>
#include <ninecraft/android_alloc.hpp>

void *android_alloc$allocate(uint32_t *__np, void *handle) {
    uint32_t __n = *(uint32_t *)__np;
    if (__n < 0x81) {
        return ((void *(*)(uint32_t *))hybris_dlsym(handle, "_ZNSt17__node_alloc_impl11_M_allocateERj"))(__np);
    }
    return ((void *(*)(uint32_t))hybris_dlsym(handle, "_Znwj"))(__n);
}

void android_alloc$deallocate(void *ptr, uint32_t __n, void *handle) {
    if (__n < 0x81) {
        ((void (*)(void *, uint32_t))hybris_dlsym(handle, "_ZNSt17__node_alloc_impl13_M_deallocateEPvj"))(ptr, __n);
    } else {
        ((void (*)(void *))hybris_dlsym(handle, "_ZdlPv"))(ptr);
    }
}