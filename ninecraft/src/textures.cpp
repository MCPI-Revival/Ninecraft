#include <ninecraft/textures.hpp>
#include <png.h>
#include <cerrno>
#include <cstdlib>

TextureData read_png(char *path, bool alpha, bool reverse_load) {
    TextureData texture_data;
    FILE *file = fopen(path, "r");

    if (!file) {
        printf("Error[%d] failed to read %s\n", errno, path);
        texture_data.height = 0;
        texture_data.width = 0;
        return texture_data;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        texture_data.height = 0;
        texture_data.width = 0;
        return texture_data;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        texture_data.height = 0;
        texture_data.width = 0;
        return texture_data;
    }
    if (setjmp(png_jmpbuf(png))) {
        texture_data.height = 0;
        texture_data.width = 0;
        return texture_data;
    }
    png_init_io(png, file);
    png_read_info(png, info);
    texture_data.width = png_get_image_width(png, info);
    texture_data.height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    if (bit_depth == 16)
        png_set_strip_16(png);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png);
    }
    png_read_update_info(png, info);
    png_size_t rowbytes = png_get_rowbytes(png, info);
    texture_data.pixels = (unsigned char *)malloc(rowbytes * texture_data.height);
    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * texture_data.height);
    for (unsigned int y = 0; y < texture_data.height; ++y) {
        if (!reverse_load) {
            row_pointers[y] = (png_byte *)&texture_data.pixels[y * rowbytes];
        } else {
            row_pointers[y] = (png_byte *)&texture_data.pixels[((texture_data.height - 1 - y) * rowbytes)];
        }
    }
    png_read_image(png, row_pointers);
    fclose(file);
    free(row_pointers);
    texture_data.alpha = alpha;
    texture_data.mipmap_level = 0;
    return texture_data;
}

GLuint load_texture(TextureData texture) {
    GLuint textureID;
    glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, texture.alpha ? GL_RGBA : GL_RGB, texture.width, texture.height, 0, texture.alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}