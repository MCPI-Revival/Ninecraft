#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/android/android_alloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

android_alloc_node_alloc_t android_alloc_node_alloc = NULL;
android_alloc_node_dealloc_t android_alloc_node_dealloc = NULL;

void android_alloc_setup_hooks(void *handle) {
    android_alloc_node_alloc = (android_alloc_node_alloc_t)internal_dlsym(handle, "_ZNSt17__node_alloc_impl11_M_allocateERj");
    android_alloc_node_dealloc = (android_alloc_node_dealloc_t)internal_dlsym(handle, "_ZNSt17__node_alloc_impl13_M_deallocateEPvj");
}

void *android_alloc_allocate(size_t *__np) {
    size_t __n = *__np;
    if (android_alloc_node_alloc != NULL && __n < 0x81) {
        return android_alloc_node_alloc(__np);
    }
    void *data = malloc(__n);
    if (data == NULL) {
        perror("Failed to allocate memeory with android_alloc");
        abort();
    }
    return data;
}

void android_alloc_deallocate(void *ptr, size_t __n) {
    if (android_alloc_node_alloc != NULL && __n < 0x81) {
        android_alloc_node_dealloc(ptr, __n);
    } else {
        if (ptr) {
            free(ptr);
        }
    }
}