#ifndef NINECRAFT_GFX_GLES_STATE_H
#define NINECRAFT_GFX_GLES_STATE_H

#include <GLES2/gl2.h>
#include <ninecraft/gfx/gles_matrix.h>

// Matrix Data
#define MATRIX_STACK_DEPTH 256
typedef struct {
    gles_matrix_t stack[MATRIX_STACK_DEPTH];
    unsigned int i;
} gles_matrix_stack_t;

// Array Pointer Storage
typedef struct {
    GLboolean enabled;
    GLint size;
    GLenum type;
    GLsizei stride;
    const void *pointer;
} gles_array_pointer_t;

// GL State
typedef struct {
    struct {
        GLfloat red;
        GLfloat green;
        GLfloat blue;
        GLfloat alpha;
    } color;
    struct {
        GLenum mode;
        gles_matrix_stack_t model_view;
        gles_matrix_stack_t projection;
        gles_matrix_stack_t texture;
    } matrix_stacks;
    struct {
        gles_array_pointer_t vertex;
        gles_array_pointer_t color;
        gles_array_pointer_t tex_coord;
    } array_pointers;
    GLboolean alpha_test;
    GLboolean texture_2d;
    struct {
        GLboolean enabled;
        GLfixed mode;
        GLfloat color[4];
        GLfloat start;
        GLfloat end;
    } fog;
} gles_gl_state_t;

extern gles_gl_state_t gl_state;

#endif