#include <ninecraft/gfx/gles_compat.h>

#ifdef NINECRAFT_HEADLESS
FLOAT_ABI_FIX void gl_alpha_func(GLenum func, GLclampf ref) {
    return;
}

void gl_bind_buffer(GLenum target, GLuint buffer) {
    return;
}

void gl_bind_texture(GLenum target, GLuint texture) {
    return;
}

void gl_blend_func(GLenum sfactor, GLenum dfactor) {
    return;
}

void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    return;
}

void gl_clear(GLbitfield mask) {
    return;
}

FLOAT_ABI_FIX void gl_clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
    return;
}

FLOAT_ABI_FIX void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    return;
}

void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    return;
}

void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer) {
    return;
}

void gl_cull_face(GLenum mode) {
    return;
}

void gl_delete_buffers(GLsizei n, const GLuint *buffers) {
    return;
}

void gl_delete_textures(GLsizei n, const GLuint *textures) {
    return;
}

void gl_depth_func(GLenum func) {
    return;
}

void gl_depth_mask(GLboolean flag) {
    return;
}

FLOAT_ABI_FIX void gl_depth_range_f(GLclampf near, GLclampf far) {
    return;
}

void gl_disable(GLenum cap) {
    return;
}

void gl_disable_client_state(GLenum array) {
    return;
}

void gl_draw_arrays(GLenum mode, GLint first, GLsizei count) {
    return;
}

void gl_enable(GLenum cap) {
    return;
}

void gl_enable_client_state(GLenum array) {
    return;
}

FLOAT_ABI_FIX void gl_fog_f(GLenum pname, GLfloat param) {
    return;
}

FLOAT_ABI_FIX void gl_fog_f_v(GLenum pname, const GLfloat *params) {
    return;
}

void gl_fog_x(GLenum pname, GLfixed param) {
    return;
}

void gl_gen_textures(GLsizei n, GLuint *textures) {
    return;
}

FLOAT_ABI_FIX void gl_get_float_v(GLenum pname, GLfloat *params) {
    return;
}

const GLubyte *gl_get_string(GLenum name) {
    return NULL;
}

void gl_hint(GLenum target, GLenum mode) {
    return;
}

FLOAT_ABI_FIX void gl_line_width(GLfloat width) {
    return;
}

void gl_load_identity() {
    return;
}

void gl_matrix_mode(GLenum mode) {
    return;
}

FLOAT_ABI_FIX void gl_mult_matrix_f(const GLfloat *m) {
    return;
}

FLOAT_ABI_FIX void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz) {
    return;
}

FLOAT_ABI_FIX void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
    return;
}

FLOAT_ABI_FIX void gl_polygon_offset(GLfloat factor, GLfloat units) {
    return;
}

void gl_pop_matrix() {
    return;
}

void gl_push_matrix() {
    return;
}

void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) {
    return;
}

FLOAT_ABI_FIX void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    return;
}

FLOAT_ABI_FIX void gl_scale_f(GLfloat x, GLfloat y, GLfloat z) {
    return;
}

void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    return;
}

void gl_shade_model(GLenum mode) {
    return;
}

void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    return;
}

void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
    return;
}

void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param) {
    return;
}

void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) {
    return;
}

FLOAT_ABI_FIX void gl_translate_f(GLfloat x, GLfloat y, GLfloat z) {
    return;
}

void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    return;
}

void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    return;
}

void gl_draw_elements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    return;
}

GLenum gl_get_error() {
    // For some reason this has to be 1 or Minecraft will crash
    return 1;
}

void gl_gen_buffers(GLsizei n, GLuint *buffers) {
    return;
}

void gl_stencil_func(GLenum func, GLint ref, GLuint mask) {
    return;
}

void gl_stencil_mask(GLuint mask) {
    return;
}

FLOAT_ABI_FIX void gl_light_model_f(GLenum pname, GLfloat param) {
    return;
}

FLOAT_ABI_FIX void gl_light_f_v(GLenum light, GLenum pname, const GLfloat *params) {
    return;
}

void gl_normal_pointer(GLenum type, GLsizei stride, const GLvoid *pointer) {
    return;
}

void gl_stencil_op(GLenum fail, GLenum zfail, GLenum zpass) {
    return;
}

void gl_active_texture(GLenum texture) {
    return;
}

void gl_attach_shader(GLuint program, GLuint shader) {
    return;
}

void gl_clear_stencil(GLint s) {
    return;
}

void gl_compile_shader(GLuint shader) {
    return;
}

GLuint gl_create_program() {
    return 0;
}

GLuint gl_create_shader(GLenum type) {
    return 0;
}

void gl_delete_program(GLuint program) {
    return;
}

void gl_enable_vertex_attrib_array(GLuint index) {
    return;
}

void gl_get_active_attrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    return;
}

void gl_get_active_uniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    return;
}

GLint gl_get_attrib_location(GLuint program, const GLchar *name) {
    return 0;
}

void gl_get_program_info_log(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    return;
}

void gl_get_program_i_v(GLuint program, GLenum pname, GLint *params) {
    return;
}

void gl_get_shader_info_log(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    return;
}

void gl_get_shader_i_v(GLuint shader, GLenum pname, GLint *params) {
    return;
}

void gl_get_shader_precision_format(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) {
    return;
}

GLint gl_get_uniform_location(GLuint program, const GLchar *name) {
    return 0;
}

void gl_link_program(GLuint program) {
    return;
}

void gl_release_shader_compiler() {
    return;
}

void gl_shader_source(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_1_f_v(GLint location, GLsizei count, const GLfloat *value) {
    return;
}

void gl_uniform_1_i_v(GLint location, GLsizei count, const GLint *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_2_f_v(GLint location, GLsizei count, const GLfloat *value) {
    return;
}

void gl_uniform_2_i_v(GLint location, GLsizei count, const GLint *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_3_f_v(GLint location, GLsizei count, const GLfloat *value) {
    return;
}

void gl_uniform_3_i_v(GLint location, GLsizei count, const GLint *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_4_f_v(GLint location, GLsizei count, const GLfloat *value) {
    return;
}

void gl_uniform_4_i_v(GLint location, GLsizei count, const GLint *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_matrix_2_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_matrix_3_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    return;
}

FLOAT_ABI_FIX void gl_uniform_matrix_4_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    return;
}

void gl_use_program(GLuint program) {
    return;
}

void gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    return;
}

void gl_stencil_func_separate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    return;
}

void gl_stencil_op_separate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    return;
}

void gl_delete_shader(GLuint shader) {
    return;
}

void gl_uniform_1_i(GLint location, GLint v0) {
    return;
}

void gl_buffer_sub_data(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {
    return;
}
#endif