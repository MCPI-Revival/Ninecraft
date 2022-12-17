#include <ninecraft/gfx/gles_state.h>
#include <ninecraft/gfx/gles_matrix.h>
#include <ninecraft/gfx/gles_compat.h>
#include <stdlib.h>
#include <stdio.h>

// Shaders
#define GL_FRAGMENT_SHADER 0x8b30
#define GL_VERTEX_SHADER 0x8b31
#define GL_INFO_LOG_LENGTH 0x8b84
#define GL_COMPILE_STATUS 0x8b81

typedef char GLchar;

extern void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);

extern void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);

extern void glShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length);

extern void glCompileShader(GLuint shader);

extern GLuint glCreateShader(GLenum shaderType);

extern GLuint glCreateProgram(void);

extern void glAttachShader(GLuint program, GLuint shader);

extern void glLinkProgram(GLuint program);

extern void glUseProgram(GLuint program);

extern GLint glGetUniformLocation(GLuint program, const GLchar *name);

extern void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

extern void glUniform1i(GLint location, GLint v0);

extern GLint glGetAttribLocation(GLuint program, const GLchar *name);

extern void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

extern void glEnableVertexAttribArray(GLuint index);

extern void glDisableVertexAttribArray(GLuint index);

extern void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

extern void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);

extern void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

extern void glUniform1f(GLint location, GLfloat v0);

// Compile Shader
static void gles_log_shader(GLuint shader, const char *name) {
    // Log
    GLint log_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    GLchar *log = malloc(log_length * sizeof(GLchar));
    glGetShaderInfoLog(shader, log_length, &log_length, log);
    if (log_length > 0) {
        if (log_length > 1 && log[log_length - 1] == '\n') {
            log[log_length - 1] = '\0';
        }
        printf("%s Shader Compile Log: %s\n", name, log);
    }
    free(log);

    // Check Status
    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled) {
        printf("Failed To Compile %s Shader\n", name);
    }
}

static GLuint gles_compile_shader(const char *vertex_shader_text, const int vertex_shader_length, const char *fragment_shader_text, const int fragment_shader_length) {
    // Vertex Shader
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, &vertex_shader_length);
    glCompileShader(vertex_shader);
    gles_log_shader(vertex_shader, "Vertex");

    // Fragment Shader
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, &fragment_shader_length);
    glCompileShader(fragment_shader);
    gles_log_shader(fragment_shader, "Fragment");

    // Link
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Return
    return program;
}

// Shader
extern unsigned char main_vsh[];
extern size_t main_vsh_len;
extern unsigned char main_fsh[];
extern size_t main_fsh_len;

static GLuint gles_get_shader() {
    static GLuint program = 0;
    if (program == 0) {
        program = gles_compile_shader((const char *) main_vsh, main_vsh_len, (const char *) main_fsh, main_fsh_len);
    }
    return program;
}

// Shader Switching
static void gles_use_shader(GLuint program) {
    static GLuint current_program = 0;
    if (current_program != program) {
        glUseProgram(program);
        current_program = program;
    }
}

// Array Pointer Drawing
void gl_draw_arrays(GLenum mode, GLint first, GLsizei count) {
    // Verify
    if (gl_state.array_pointers.vertex.size != 3 || !gl_state.array_pointers.vertex.enabled || gl_state.array_pointers.vertex.type != GL_FLOAT) {
        puts("Unsupported Vertex Conifguration");
    }

    // Check Mode
    int use_color_pointer = gl_state.array_pointers.color.enabled;
    if (use_color_pointer && (gl_state.array_pointers.color.size != 4 || gl_state.array_pointers.color.type != GL_UNSIGNED_BYTE)) {
        puts("Unsupported Color Conifguration");
    }
    int use_texture = gl_state.texture_2d && gl_state.array_pointers.tex_coord.enabled;
    if (use_texture && (gl_state.array_pointers.tex_coord.size != 2 || gl_state.array_pointers.tex_coord.type != GL_FLOAT)) {
        puts("Unsupported Texture Conifguration");
    }

    // Load Shader
    GLuint program = gles_get_shader();
    gles_use_shader(program);

    // Projection Matrix
    static GLint u_projection_handle = -1;
    if (u_projection_handle == -1) {
        u_projection_handle = glGetUniformLocation(program, "u_projection");
    }
    gles_matrix_t *p = &gl_state.matrix_stacks.projection.stack[gl_state.matrix_stacks.projection.i];
    glUniformMatrix4fv(u_projection_handle, 1, 0, (GLfloat *) &p->data[0][0]);

    // Model View Matrix
    static GLint u_model_view_handle = -1;
    if (u_model_view_handle == -1) {
        u_model_view_handle = glGetUniformLocation(program, "u_model_view");
    }
    p = &gl_state.matrix_stacks.model_view.stack[gl_state.matrix_stacks.model_view.i];
    glUniformMatrix4fv(u_model_view_handle, 1, 0, (GLfloat *) &p->data[0][0]);

    // Has Texture
    static GLint u_has_texture_handle = -1;
    if (u_has_texture_handle == -1) {
        u_has_texture_handle = glGetUniformLocation(program, "u_has_texture");
    }
    glUniform1i(u_has_texture_handle, use_texture);

    // Texture Matrix
    static GLint u_texture_handle = -1;
    if (u_texture_handle == -1) {
        u_texture_handle = glGetUniformLocation(program, "u_texture");
    }
    p = &gl_state.matrix_stacks.texture.stack[gl_state.matrix_stacks.texture.i];
    glUniformMatrix4fv(u_texture_handle, 1, 0, (GLfloat *) &p->data[0][0]);

    // Texture Unit
    static GLint u_texture_unit_handle = -1;
    if (u_texture_unit_handle == -1) {
        u_texture_unit_handle = glGetUniformLocation(program, "u_texture_unit");
    }
    glUniform1i(u_texture_unit_handle, 0);

    // Alpha Test
    static GLint u_alpha_test_handle = -1;
    if (u_alpha_test_handle == -1) {
        u_alpha_test_handle = glGetUniformLocation(program, "u_alpha_test");
    }
    glUniform1i(u_alpha_test_handle, gl_state.alpha_test);

    // Color
    GLint a_color_handle = glGetAttribLocation(program, "a_color");
    if (use_color_pointer) {
        glVertexAttribPointer(a_color_handle, gl_state.array_pointers.color.size, gl_state.array_pointers.color.type, 1, gl_state.array_pointers.color.stride, gl_state.array_pointers.color.pointer);
        glEnableVertexAttribArray(a_color_handle);
    } else {
        glVertexAttrib4f(a_color_handle, gl_state.color.red, gl_state.color.green, gl_state.color.blue, gl_state.color.alpha);
    }

    // Fog
    static GLint u_fog_handle = -1;
    if (u_fog_handle == -1) {
        u_fog_handle = glGetUniformLocation(program, "u_fog");
    }
    glUniform1i(u_fog_handle, gl_state.fog.enabled);
    if (gl_state.fog.enabled) {
        static GLint u_fog_color_handle = -1;
        if (u_fog_color_handle == -1) {
            u_fog_color_handle = glGetUniformLocation(program, "u_fog_color");
        }
        glUniform4f(u_fog_color_handle, gl_state.fog.color[0], gl_state.fog.color[1], gl_state.fog.color[2], gl_state.fog.color[3]);
        static GLint u_fog_is_linear_handle = -1;
        if (u_fog_is_linear_handle == -1) {
            u_fog_is_linear_handle = glGetUniformLocation(program, "u_fog_is_linear");
        }
        glUniform1i(u_fog_is_linear_handle, gl_state.fog.mode == GL_LINEAR);
        static GLint u_fog_start_handle = -1;
        if (u_fog_start_handle == -1) {
            u_fog_start_handle = glGetUniformLocation(program, "u_fog_start");
        }
        glUniform1f(u_fog_start_handle, gl_state.fog.start);
        static GLint u_fog_end_handle = -1;
        if (u_fog_end_handle == -1) {
            u_fog_end_handle = glGetUniformLocation(program, "u_fog_end");
        }
        glUniform1f(u_fog_end_handle, gl_state.fog.end);
    }

    // Vertices
    GLint a_vertex_coords_handle = glGetAttribLocation(program, "a_vertex_coords");
    glVertexAttribPointer(a_vertex_coords_handle, gl_state.array_pointers.vertex.size, gl_state.array_pointers.vertex.type, 0, gl_state.array_pointers.vertex.stride, gl_state.array_pointers.vertex.pointer);
    glEnableVertexAttribArray(a_vertex_coords_handle);

    // Texture Coordinates
    GLint a_texture_coords_handle = glGetAttribLocation(program, "a_texture_coords");
    if (use_texture) {
        glVertexAttribPointer(a_texture_coords_handle, gl_state.array_pointers.tex_coord.size, gl_state.array_pointers.tex_coord.type, 0, gl_state.array_pointers.tex_coord.stride, gl_state.array_pointers.tex_coord.pointer);
        glEnableVertexAttribArray(a_texture_coords_handle);
    } else {
        glVertexAttrib3f(a_texture_coords_handle, 0, 0, 0);
    }

    // Draw
    glDrawArrays(mode, first, count);

    // Cleanup
    if (use_color_pointer) {
        glDisableVertexAttribArray(a_color_handle);
    }
    glDisableVertexAttribArray(a_vertex_coords_handle);
    if (use_texture) {
        glDisableVertexAttribArray(a_texture_coords_handle);
    }
}