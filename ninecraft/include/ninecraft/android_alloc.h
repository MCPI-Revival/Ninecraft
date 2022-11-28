#pragma once

void *android_alloc_allocate(size_t *__np, void *handle);

void android_alloc_deallocate(void *ptr, size_t __n, void *handle);