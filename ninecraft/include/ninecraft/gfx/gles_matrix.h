#ifndef NINECRAFT_GFX_GLES_MATRIX_H
#define NINECRAFT_GFX_GLES_MATRIX_H

#include <GLES2/gl2.h>

// Matrix Common
#define MATRIX_SIZE 4
#define MATRIX_DATA_SIZE (sizeof (GLfloat) * MATRIX_SIZE * MATRIX_SIZE)

// OpenGL Matrices Are Column-Major
typedef struct {
    GLfloat data[MATRIX_SIZE][MATRIX_SIZE];
} gles_matrix_t;

#endif