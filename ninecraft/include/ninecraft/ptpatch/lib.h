#pragma once

#include <sys/types.h>

typedef struct {
    int version_code;
    int patch_count;
} patch_data_t;
typedef enum {
    PATCH_OK,
    PATCH_SKIPPED,
    PATCH_INVALID
} patch_ret_t;

typedef int (*patch_data_callback_t)(patch_data_t *data, void *user_data);
typedef void (*patch_apply_callback_t)(off_t offset, size_t data_length, unsigned char *data, void *user_data);
patch_ret_t load_patch(const char *path, patch_data_callback_t on_data, patch_apply_callback_t on_apply, void *user_data);