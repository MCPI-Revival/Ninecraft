#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <ninecraft/android_string.h>
#include <stdint.h>
#include <stdbool.h>

#define STLPORT_MAX_SIZE 178956970

typedef struct {
    uintptr_t _M_start;
    uintptr_t _M_finish;
    uintptr_t _M_end_of_storage;
} android_vector;

size_t android_vector$_M_compute_next_size(android_vector *__this, size_t __n);

uintptr_t android_vector$__uninitialized_fill(uintptr_t __first, size_t __n, uintptr_t __x, void *handle);

uintptr_t android_vector$__uninitialized_move(uintptr_t __first, uintptr_t __last, uintptr_t __result);

void android_vector$_M_insert_overflow_aux(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle);

void android_vector$push_back(android_vector *this_vector, android_string *item, void *handle);

size_t android_vector$_M_compute_next_size_2(android_vector *__this, size_t __n);

uintptr_t android_vector$__uninitialized_fill_2(uintptr_t __first, size_t __n, uintptr_t __x);

uintptr_t android_vector$__uninitialized_move_2(uintptr_t __first, uintptr_t __last, uintptr_t __result);

void android_vector$_M_insert_overflow_aux_2(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle);

void android_vector$push_back_2(android_vector *this_vector, void *item, void *handle);