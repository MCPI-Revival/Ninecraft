#include <ninecraft/ptpatch/lib.h>

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

// Magic
static const union {
    unsigned char arr[4];
    uint32_t num;
} MAGIC = {
    .arr = {0xff, 0x50, 0x54, 0x50}
};

// Macros
#define ret(x) \
    do { \
        fclose(file); \
        return (x); \
    } while (0)
#define safe_read(out) \
    if (fread(&(out), sizeof(out), 1, file) != 1) { \
        ret(PATCH_INVALID); \
    } \
    (void) 0
#define fix_int(x) \
    x = ntohl(x)

// Load PTPatch
patch_ret_t load_patch(const char *path, const patch_data_callback_t on_data, patch_apply_callback_t on_apply, void *user_data) {
    // Open File
    FILE *file = fopen(path, "rb");
    if (!file) {
        return PATCH_INVALID;
    }

    // Check Magic
    uint32_t magic;
    safe_read(magic);
    if (magic != MAGIC.num) {
        // Invalid Magic
        ret(PATCH_INVALID);
    }

    // Read Metadata
    patch_data_t meta;
    unsigned char x;
    safe_read(x);
    meta.version_code = x;
    safe_read(x);
    meta.patch_count = x;
    if (on_data && on_data(&meta, user_data)) {
        ret(PATCH_SKIPPED);
    }

    // Read Patches
    patch_ret_t ret = PATCH_OK;
    for (int i = 0; i < meta.patch_count; i++) {
        // Read Offset Of Patch In File
        uint32_t offset;
        safe_read(offset);
        fix_int(offset);
        const off_t next_index = ftell(file);
        // Get Offset Of Next Patch In File
        // Used To Determine Patch Size
        uint32_t next_offset;
        if (i == (meta.patch_count - 1)) {
            fseek(file, 0, SEEK_END);
            next_offset = ftell(file);
        } else {
            safe_read(next_offset);
            fix_int(next_offset);
        }
        // Read Patch Address
        fseek(file, (off_t) offset, SEEK_SET);
        uint32_t addr;
        safe_read(addr);
        fix_int(addr);
        // Read Patch Data
        const off_t cursor = ftell(file);
        if (next_offset > cursor) {
            const size_t data_length = next_offset - cursor;
            unsigned char *data = malloc(data_length);
            if (!data || fread(data, data_length, 1, file) != 1) {
                ret = PATCH_INVALID;
            } else {
                on_apply((off_t) addr, data_length, data, user_data);
            }
            free(data);
        } else {
            ret = PATCH_INVALID;
        }
        // Advance To Next Patch
        if (ret == PATCH_OK) {
            fseek(file, next_index, SEEK_SET);
        } else {
            break;
        }
    }

    // Return
    ret(ret);
}