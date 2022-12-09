#ifndef NINECRAFT_ANDROID_ANDROID_STRING_H
#define NINECRAFT_ANDROID_ANDROID_STRING_H

typedef union {
    void *_M_end_of_storage;
    char _M_static_buf[16];
} buffers_t;

typedef struct {
    buffers_t buffers;
    void *_M_finish;
    void *_M_start_of_storage;
} android_string_t;

typedef void (*android_string_clone_t)(android_string_t *__this, android_string_t *__ps, void *handle);
typedef void (*android_string_deallocate_block_t)(android_string_t *__this, void *handle);

extern android_string_clone_t android_string_clone;
extern android_string_deallocate_block_t android_string_deallocate_block;

void android_string_setup_hooks(void *handle);

void *android_string_ucopy_trivial(const void *__first, const void *__last, void *__result);

void android_string_move_src(android_string_t *__this, android_string_t *__ps);

void android_string_allocate_block(android_string_t *__this, size_t __n);

void android_string_cstr(android_string_t *__this, char *__s);

#endif