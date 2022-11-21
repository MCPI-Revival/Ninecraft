#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <ninecraft/android_string.hpp>
#include <stdint.h>

#include <new>
#include <limits>
#include <iostream>
#include <vector>

#define STLPORT_MAX_SIZE 178956970
#define STLPORT_SIZE_TYPE(x) (-1431655765 * (x >> 3))

typedef struct {
    uintptr_t _M_start;
    uintptr_t _M_finish;
    uintptr_t _M_end_of_storage;
} android_vector;

uint32_t android_vector$_M_compute_next_size(android_vector *__this, size_t __n);

void android_vector$_M_insert_overflow_aux(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle);

void android_vector$_M_insert_overflow_aux_2(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle);

void android_vector$push_back(android_vector *this_vector, android_string *item, void *handle);