#ifndef NINECRAFT_GFX_TEXTURES_H
#define NINECRAFT_GFX_TEXTURES_H

#include <stdbool.h>
#include <stdint.h>

enum texture_type {
    texture_type_ub = 0,
    texture_type_us565 = 1,
    texture_type_us5551 = 1,
    texture_type_us4444 = 3
};

typedef struct {
    uint32_t width;
    uint32_t height;
    uint8_t *pixels;
} png_data_t;

typedef struct {
    uint32_t width;// 0 0x00
    uint32_t height; // 4 0x04
    uint8_t *pixels; // 8 0x08
    uint32_t unknown; // 12 0x0c
    uint8_t alpha; // 16 0x10
    uint8_t keep_buffer_data; // 17 0x11
    uint32_t texture_type; // 20 0x14
    uint32_t unknown2; // 24 0x18
} texture_data_t;

typedef struct {
    uint32_t width;// 0 0x00
    uint32_t height; // 4 0x04
    uint8_t *pixels; // 8 0x08
    uint8_t alpha; // 12 0x0c
    uint8_t keep_buffer_data; // 13 0x0d
} texture_data_old_t;

extern png_data_t read_png(char *path);

#endif
