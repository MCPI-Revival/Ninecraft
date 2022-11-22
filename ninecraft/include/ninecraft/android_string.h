#pragma once

#include <stdint.h>

typedef union {
    void *_M_end_of_storage;
    char _M_static_buf[16];
} buffers_t;

typedef struct {
    buffers_t buffers;
    void *_M_finish;
    void *_M_start_of_storage;
} android_string;

void *android_string$__ucopy_trivial(const void *__first, const void *__last, void *__result);

void android_string$_M_allocate_block(android_string *__this, size_t __n, void *handle);

void to_str(android_string *str, char *cstr, void *handle);

void android_string$string(android_string *__this, android_string *str, void *handle);

void android_string$_M_deallocate_block(android_string *__this, void *handle);

void android_string$_M_move_src(android_string *__this, android_string *src);