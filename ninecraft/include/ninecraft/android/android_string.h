#ifndef NINECRAFT_ANDROID_ANDROID_STRING_H
#define NINECRAFT_ANDROID_ANDROID_STRING_H

#include <stddef.h>

typedef union {
    void *_M_end_of_storage;
    char _M_static_buf[16];
} buffers_t;

typedef struct {
    buffers_t buffers;
    void *_M_finish;
    void *_M_start_of_storage;
} android_string_stlp_t;

typedef struct {
    char *data;
} android_string_gnu_t;

typedef union {
    android_string_stlp_t stlp;
    android_string_gnu_t gnu;
} android_string_t;

typedef void (*android_string_deallocate_block_t)(android_string_t *__this);
typedef void (*android_string_assign_t)(android_string_t *__this, const char *__first, const char *__last);

extern android_string_deallocate_block_t android_string_deallocate_block;
extern android_string_assign_t android_string_assign;

extern void android_string_setup_hooks(void *handle);

extern void *android_string_ucopy_trivial(const void *__first, const void *__last, void *__result);

extern void android_string_move_src(android_string_t *__this, android_string_t *__ps);

extern void android_string_allocate_block(android_string_t *__this, size_t __n);

char *android_string_to_str(android_string_t *__this);

size_t android_string_tsize();

extern void android_string_cstr(android_string_t *__this, char *__s);

void android_string_destroy(android_string_t *__this);

extern void android_string_equ(android_string_t *__this, char *__s);

#endif