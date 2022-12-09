#include <hybris/dlfcn.h>
#include <ninecraft/android/android_alloc.h>
#include <stddef.h>

android_alloc_node_alloc_t android_alloc_node_alloc = NULL;
android_alloc_operator_new_t android_alloc_operator_new = NULL;
android_alloc_node_dealloc_t android_alloc_node_dealloc = NULL;
android_alloc_operator_delete_t android_alloc_operator_delete = NULL;

void android_alloc_setup_hooks(void *handle) {
    android_alloc_node_alloc = (android_alloc_node_alloc_t)hybris_dlsym(handle, "_ZNSt17__node_alloc_impl11_M_allocateERj");
    android_alloc_operator_new = (android_alloc_operator_new_t)hybris_dlsym(handle, "_Znwj");
    android_alloc_node_dealloc = (android_alloc_node_dealloc_t)hybris_dlsym(handle, "_ZNSt17__node_alloc_impl13_M_deallocateEPvj");
    android_alloc_operator_delete = (android_alloc_operator_delete_t)hybris_dlsym(handle, "_ZdlPv");
}

void *android_alloc_allocate(size_t *__np) {
    size_t __n = *__np;
    if (__n < 0x81) {
        return android_alloc_node_alloc(__np);
    }
    return android_alloc_operator_new(__n);
}

void android_alloc_deallocate(void *ptr, size_t __n) {
    if (__n < 0x81) {
        android_alloc_node_dealloc(ptr, __n);
    } else {
        android_alloc_operator_delete(ptr);
    }
}