#include <ninecraft/gfx/gles_compat.h>
#include <ninecraft/gfx/gles_defs.h>
#include <ninecraft/gfx/gles_matrix.h>
#include <ninecraft/gfx/gles_state.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Matrix Common
static void gles_matrix_copy(gles_matrix_t *src, gles_matrix_t *dst) {
    memcpy((void *) dst->data, (void *) src->data, MATRIX_DATA_SIZE);
}

// Identity Matrix
static gles_matrix_t identity_matrix = {
    .data = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }
};

static void gles_init_matrix_stack(gles_matrix_stack_t *stack) {
    gles_matrix_copy(&identity_matrix, &stack->stack[0]);
}

__attribute__((constructor)) static void gles_init_matrix_stacks() {
    gles_init_matrix_stack(&gl_state.matrix_stacks.model_view);
    gles_init_matrix_stack(&gl_state.matrix_stacks.projection);
    gles_init_matrix_stack(&gl_state.matrix_stacks.texture);
}

// Matrix Mode
static gles_matrix_stack_t *gles_get_matrix_stack() {
    switch (gl_state.matrix_stacks.mode) {
        case GLES_GL_MODELVIEW: {
            return &gl_state.matrix_stacks.model_view;
        }
        case GLES_GL_PROJECTION: {
            return &gl_state.matrix_stacks.projection;
        }
        case GLES_GL_TEXTURE: {
            return &gl_state.matrix_stacks.texture;
        }
        default: {
            printf("Unsupported Matrix Mode: %i\n", gl_state.matrix_stacks.mode);
        }
    }
}

// Matrix Functions
void gl_matrix_mode(GLenum mode) {
    gl_state.matrix_stacks.mode = mode;
}

void gl_pop_matrix() {
    gles_get_matrix_stack()->i--;
}

void gl_load_identity() {
    gles_matrix_stack_t *stack = gles_get_matrix_stack();
    gles_matrix_copy(&identity_matrix, &stack->stack[stack->i]);
}
void gl_push_matrix() {
    gles_matrix_stack_t *stack = gles_get_matrix_stack();
    gles_matrix_copy(&stack->stack[stack->i], &stack->stack[stack->i + 1]);
    stack->i++;
}
void gl_mult_matrix_f(const GLfloat *m) {
    gles_matrix_t new_matrix;
    gles_matrix_stack_t *stack = gles_get_matrix_stack();
    gles_matrix_t *current_matrix = &stack->stack[stack->i];
    for (int x = 0; x < MATRIX_SIZE; x++) {
        for (int y = 0; y < MATRIX_SIZE; y++) {
            GLfloat result = 0;
            for (int i = 0; i < MATRIX_SIZE; i++) {
                result += (current_matrix->data[i][y] * m[(x * MATRIX_SIZE) + i]);
            }
            new_matrix.data[x][y] = result;
        }
    }
    gles_matrix_copy(&new_matrix, current_matrix);
}

void gl_scale_f(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat m[] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
    gl_mult_matrix_f(m);
}
void gl_translate_f(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat m[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
    gl_mult_matrix_f(m);
}
void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
    GLfloat m[] = {
        (2.f / (right - left)), 0, 0, 0,
        0, (2.f / (top - bottom)), 0, 0,
        0, 0, (-2.f / (far - near)), 0,
        -((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1
    };
    gl_mult_matrix_f(m);
}

void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    // Normalize
    GLfloat length = sqrtf((x * x) + (y * y) + (z * z));
    x /= length;
    y /= length;
    z /= length;

    // Values
    GLfloat angle_radians = angle * (3.1415926535897932384626433832795 / 180.f);
    GLfloat c = cosf(angle_radians);
    GLfloat s = sinf(angle_radians);
    GLfloat x2 = x * x;
    GLfloat y2 = y * y;
    GLfloat z2 = z * z;

    // Multiply
    GLfloat m[] = {
        x2 * (1.f - c) + c, (x * y) * (1.f - c) + (z * s), (x * z) * (1.f - c) - (y * s), 0,
        (x * y) * (1.f - c) - (z * s), y2 * (1.f - c) + c, (y * z) * (1.f - c) + (x * s), 0,
        (x * z) * (1.f - c) + (y * s), (y * z) * (1.f - c) - (x * s), z2 * (1.f - c) + c, 0,
        0, 0, 0, 1.f
    };
    gl_mult_matrix_f(m);
}