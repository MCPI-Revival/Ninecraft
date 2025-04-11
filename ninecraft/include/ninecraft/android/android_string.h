#ifndef NINECRAFT_ANDROID_ANDROID_STRING_H
#define NINECRAFT_ANDROID_ANDROID_STRING_H

#include <stddef.h>
#include <stdint.h>

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

extern void *android_string_ucopy_trivial(const void *__first, const void *__last, void *__result);

extern void android_string_move_src(android_string_t *__this, android_string_t *__ps);

extern void android_string_allocate_block(android_string_t *__this, size_t __n);

extern void android_string_deallocate_block(android_string_t *__this);

char *android_string_to_str(android_string_t *__this);

size_t android_string_tsize();

extern void android_string_cstr(android_string_t *__this, char *__s);

extern void android_string_cstrl(android_string_t *__this, char *__s, size_t length);

extern void android_string_destroy(android_string_t *__this);

extern uintptr_t android_string_rest(android_string_t *__this);

extern void android_string_erase(android_string_t *__this, void *__first, void *__last);

extern size_t android_string_next_size(android_string_t *__this, size_t __n);

extern void android_string_reset(android_string_t *__this, void *__new_start, void *__new_finish, void *__new_end);

extern void android_string_construct_null(void *addr);

extern void android_string_append(android_string_t *__this, char *__first, char *__last);

extern void android_string_assign(android_string_t *__this, char *__f, char *__l);

extern void android_string_equ(android_string_t *__this, char *__s);

#endif