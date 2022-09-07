#pragma once

#include <glad/glad.h>

typedef struct {
    int width;
    int height;
    unsigned char *pixels;
    int unknown;
    unsigned char alpha;
    char unknown2[3];
    int mipmap_level;
} TextureData;

TextureData read_png(char *path, bool alpha);

GLuint load_texture(TextureData texture);