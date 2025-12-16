#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ninecraft/ptpatch/apply.h>
#include <ninecraft/ptpatch/lib.h>

// Copy File
static FILE *copy_file(const char *src, const char *dst) {
    // Open Files
    FILE *src_file = fopen(src, "rb");
    if (!src_file) {
        return NULL;
    }
    FILE *dst_file = fopen(dst, "wb");
    if (!dst_file) {
        fclose(src_file);
        return NULL;
    }

    // Copy File
    fseek(src_file, 0, SEEK_END);
    const size_t src_size = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);
    int success = 1;
    void *buf = NULL;
    do {
        buf = malloc(src_size);
        if (!buf) {
            success = 0;
            break;
        }
        if (fread(buf, src_size, 1, src_file) != 1) {
            success = 0;
            break;
        }
        if (fwrite(buf, src_size, 1, dst_file) != 1) {
            success = 0;
            break;
        }
    } while (0);
    free(buf);
    fclose(src_file);
    if (!success) {
        fclose(dst_file);
        return NULL;
    }

    // Return
    return dst_file;
}

// Check If String Ends With Prefix
static int ends_with(const char *str, const char *prefix) {
    const size_t prefix_len = strlen(prefix);
    const size_t str_len = strlen(str);
    if (str_len < prefix_len) {
        return 0;
    }
    return strncmp(str + (str_len - prefix_len), prefix, prefix_len) == 0;
}

// Patch Callback
static void on_data(const off_t offset, const size_t data_length, unsigned char *data, void *user_data) {
    FILE *file = user_data;
    fseek(file, offset, SEEK_SET);
    fwrite(data, data_length, 1, file);
}

// Apply Patches
int apply_ptpatches(const char *src, const char *dst, const char *patches_dir) {
    // Copy Files
    FILE *dst_file = copy_file(src, dst);
    if (!dst_file) {
        return 0;
    }

    // Apply Patches
    DIR *dir = opendir(patches_dir);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            const char *name = entry->d_name;
            if (ends_with(name, ".mod")) {
                printf("Applying PTPatch: %s...", name);
                int ret = 0;
                char *patch_path = (char *)malloc(1024);
                if (patch_path) {
                    patch_path[0] = '\0';
                    strcat(patch_path, patches_dir);
                    strcat(patch_path, "/");
                    strcat(patch_path, name);
                    ret = load_patch(patch_path, NULL, on_data, dst_file) == PATCH_OK;
                    free(patch_path);
                }
                printf(" %s\n", ret ? "Success" : "Failure");
            }
        }
        closedir(dir);
    }
    fclose(dst_file);
    return 1;
}
