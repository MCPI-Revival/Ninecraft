#ifndef NINECRAFT_ANDROID_ANDROID_ALLOC_H
#define NINECRAFT_ANDROID_ANDROID_ALLOC_H

#include <stddef.h>

typedef void *(*android_alloc_node_alloc_t)(size_t *__np);
typedef void (*android_alloc_node_dealloc_t)(void *ptr, size_t __n);

extern android_alloc_node_alloc_t android_alloc_node_alloc;
extern android_alloc_node_dealloc_t android_alloc_node_dealloc;

extern void android_alloc_setup_hooks(void *handle);

extern void *android_alloc_allocate(size_t *__np);

extern void android_alloc_deallocate(void *ptr, size_t __n);

#endif