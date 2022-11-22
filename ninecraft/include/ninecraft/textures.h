#pragma once

#include <glad/glad.h>
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    unsigned char *pixels;
    int unknown;
    unsigned char alpha;
    char unknown2[3];
    int mipmap_level;
} TextureData;

TextureData read_png(char *path, bool alpha, bool reverse_load);

GLuint load_texture(TextureData texture);