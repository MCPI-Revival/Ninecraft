#ifndef NINECRAFT_ANDROID_ANDROID_VECTOR_H
#define NINECRAFT_ANDROID_ANDROID_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <ninecraft/android/android_string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uintptr_t _M_start;
    uintptr_t _M_finish;
    uintptr_t _M_end_of_storage;
} android_vector_t;

extern size_t android_vector_compute_next_size(android_vector_t *__this, size_t __n, size_t __entry_size);

extern uintptr_t android_vector_uninitialized_fill(uintptr_t __first, size_t __n, uintptr_t __x, size_t __entry_size);

extern uintptr_t android_vector_uninitialized_move(uintptr_t __first, uintptr_t __last, uintptr_t __result, size_t __entry_size);

extern void android_vector_insert_overflow_aux(android_vector_t *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, size_t __entry_size);

extern void android_vector_push_back(android_vector_t *this_vector, void *item, size_t __entry_size);

#endif