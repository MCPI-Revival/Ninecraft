#ifndef NINECRAFT_ANDROID_ANDROID_ALLOC_H
#define NINECRAFT_ANDROID_ANDROID_ALLOC_H

void *android_alloc_allocate(size_t *__np, void *handle);

void android_alloc_deallocate(void *ptr, size_t __n, void *handle);

#endif