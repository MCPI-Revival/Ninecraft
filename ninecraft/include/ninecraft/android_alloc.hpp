#pragma once

#include <stdint.h>

void *android_alloc$allocate(uint32_t *__np, void *handle);

void android_alloc$deallocate(void *ptr, uint32_t __n, void *handle);