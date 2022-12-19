#include <ninecraft/gfx/gles_compat.h>
#include <ninecraft/gfx/gles_defs.h>
#include <ninecraft/gfx/gles_state.h>
#include <stdio.h>
#include <string.h>

// GL State
gles_gl_state_t gl_state = {
    .color = {
        .red = 1,
        .green = 1,
        .blue = 1,
        .alpha = 1
    },
    .matrix_stacks = {
        .mode = GLES_GL_MODELVIEW
    },
    .alpha_test = 0,
    .texture_2d = 0,
    .fog = {
        .enabled = 0,
        .mode = GLES_GL_LINEAR,
        .color = {0, 0, 0, 0},
        .start = 0,
        .end = 1
    }
};

// Change Color
void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    gl_state.color.red = red;
    gl_state.color.green = green;
    gl_state.color.blue = blue;
    gl_state.color.alpha = alpha;
}

// Array Pointer Storage

void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer) {
    gl_state.array_pointers.vertex.size = size;
    gl_state.array_pointers.vertex.type = type;
    gl_state.array_pointers.vertex.stride = stride;
    gl_state.array_pointers.vertex.pointer = pointer;
}

void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer) {
    gl_state.array_pointers.color.size = size;
    gl_state.array_pointers.color.type = type;
    gl_state.array_pointers.color.stride = stride;
    gl_state.array_pointers.color.pointer = pointer;
}

void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer) {
    gl_state.array_pointers.tex_coord.size = size;
    gl_state.array_pointers.tex_coord.type = type;
    gl_state.array_pointers.tex_coord.stride = stride;
    gl_state.array_pointers.tex_coord.pointer = pointer;
}

static gles_array_pointer_t *gles_get_array_pointer(GLenum array) {
    switch (array) {
        case GLES_GL_VERTEX_ARRAY: {
            return &gl_state.array_pointers.vertex;
        }
        case GLES_GL_COLOR_ARRAY: {
            return &gl_state.array_pointers.color;
        }
        case GLES_GL_TEXTURE_COORD_ARRAY: {
            return &gl_state.array_pointers.tex_coord;
        }
        default: {
            printf("Unsupported Array Pointer: %i\n", array);
        }
    }
}

void gl_enable_client_state(GLenum array) {
    gles_get_array_pointer(array)->enabled = 1;
}

void gl_disable_client_state(GLenum array) {
    gles_get_array_pointer(array)->enabled = 0;
}

void gl_enable(GLenum cap) {
    switch (cap) {
        case GLES_GL_ALPHA_TEST: {
            gl_state.alpha_test = 1;
            break;
        }
        case GLES_GL_TEXTURE_2D: {
            gl_state.texture_2d = 1;
            break;
        }
        case GLES_GL_COLOR_MATERIAL: {
            // Ignore
            break;
        }
        case GLES_GL_FOG: {
            gl_state.fog.enabled = 1;
            break;
        }
        default: {
            glEnable(cap);
            break;
        }
    }
}

void gl_disable(GLenum cap) {
    switch (cap) {
        case GLES_GL_ALPHA_TEST: {
            gl_state.alpha_test = 0;
            break;
        }
        case GLES_GL_TEXTURE_2D: {
            gl_state.texture_2d = 0;
            break;
        }
        case GLES_GL_COLOR_MATERIAL: {
            // Ignore
            break;
        }
        case GLES_GL_FOG: {
            gl_state.fog.enabled = 0;
            break;
        }
        default: {
            glDisable(cap);
            break;
        }
    }
}

void gl_alpha_func(GLenum func, GLclampf ref) {
    if (func != GLES_GL_GREATER && ref != 0.1f) {
        puts("Unsupported Alpha Function");
    }
}

// Fog

void gl_fog_f_v(GLenum pname, const GLfloat *params) {
    if (pname == GLES_GL_FOG_COLOR) {
        memcpy((void *) gl_state.fog.color, params, sizeof (gl_state.fog.color));
    } else {
        puts("Unsupported Fog Configuration");
    }
}

void gl_fog_x(GLenum pname, GLfixed param) {
    if (pname == GLES_GL_FOG_MODE && (param == GLES_GL_LINEAR || param == GLES_GL_EXP)) {
        gl_state.fog.mode = param;
    } else {
        puts("Unsupported Fog Configuration");
    }
}

void gl_fog_f(GLenum pname, GLfloat param) {
    switch (pname) {
        case GLES_GL_FOG_DENSITY:
        case GLES_GL_FOG_START: {
            gl_state.fog.start = param;
            break;
        }
        case GL_FOG_END: {
            gl_state.fog.end = param;
            break;
        }
        default: {
            puts("Unsupported Fog Configuration");
            break;
        }
    }
}

// Get Matrix Data
void gl_get_float_v(GLenum pname, GLfloat *params) {
    switch (pname) {
        case GLES_GL_MODELVIEW_MATRIX: {
            memcpy((void *) params, gl_state.matrix_stacks.model_view.stack[gl_state.matrix_stacks.model_view.i].data, MATRIX_DATA_SIZE);
            break;
        }
        case GLES_GL_PROJECTION_MATRIX: {
            memcpy((void *) params, gl_state.matrix_stacks.projection.stack[gl_state.matrix_stacks.projection.i].data, MATRIX_DATA_SIZE);
            break;
        }
        default: {
            glGetFloatv(pname, params);
            break;
        }
    }
}