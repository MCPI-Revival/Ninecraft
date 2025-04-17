#ifndef NINECRAFT_GFX_GLES_COMPAT_H
#define NINECRAFT_GFX_GLES_COMPAT_H

#include <glad/gl.h>
#include <ancmp/abi_fix.h>

// Function documentation
// https://registry.khronos.org/OpenGL-Refpages/es1.1/xhtml/

extern void gl_alpha_func(GLenum func, GLclampf ref) FLOAT_ABI_FIX;

extern void gl_bind_buffer(GLenum target, GLuint buffer);

extern void gl_bind_texture(GLenum target, GLuint texture);

extern void gl_blend_func(GLenum sfactor, GLenum dfactor);

extern void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

extern void gl_clear(GLbitfield mask);

extern void gl_clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) FLOAT_ABI_FIX;

extern void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) FLOAT_ABI_FIX;

extern void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

extern void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer);

extern void gl_cull_face(GLenum mode);

extern void gl_delete_buffers(GLsizei n, const GLuint *buffers);

extern void gl_delete_textures(GLsizei n, const GLuint *textures);

extern void gl_depth_func(GLenum func);

extern void gl_depth_mask(GLboolean flag);

extern void gl_depth_range_f(GLclampf near, GLclampf far) FLOAT_ABI_FIX;

extern void gl_disable(GLenum cap);

extern void gl_disable_client_state(GLenum array);

extern void gl_draw_arrays(GLenum mode, GLint first, GLsizei count);

extern void gl_enable(GLenum cap);

extern void gl_enable_client_state(GLenum array);

extern void gl_fog_f(GLenum pname, GLfloat param) FLOAT_ABI_FIX;

extern void gl_fog_f_v(GLenum pname, const GLfloat *params) FLOAT_ABI_FIX;

extern void gl_fog_x(GLenum pname, GLfixed param);

extern void gl_gen_textures(GLsizei n, GLuint *textures);

extern void gl_get_float_v(GLenum pname, GLfloat *params) FLOAT_ABI_FIX;

extern const GLubyte *gl_get_string(GLenum name);

extern void gl_hint(GLenum target, GLenum mode);

extern void gl_line_width(GLfloat width) FLOAT_ABI_FIX;

extern void gl_load_identity();

extern void gl_matrix_mode(GLenum mode);

extern void gl_mult_matrix_f(const GLfloat *m) FLOAT_ABI_FIX;

extern void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz) FLOAT_ABI_FIX;

extern void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) FLOAT_ABI_FIX;

extern void gl_polygon_offset(GLfloat factor, GLfloat units) FLOAT_ABI_FIX;

extern void gl_pop_matrix();

extern void gl_push_matrix();

extern void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);

extern void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) FLOAT_ABI_FIX;

extern void gl_scale_f(GLfloat x, GLfloat y, GLfloat z) FLOAT_ABI_FIX;

extern void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height);

extern void gl_shade_model(GLenum mode);

extern void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

extern void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param);

extern void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

extern void gl_translate_f(GLfloat x, GLfloat y, GLfloat z) FLOAT_ABI_FIX;

extern void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height);

extern void gl_draw_elements(GLenum mode, GLsizei count, GLenum type, const void *indices);

extern GLenum gl_get_error();

extern void gl_gen_buffers(GLsizei n, GLuint *buffers);

extern void gl_stencil_func(GLenum func, GLint ref, GLuint mask);

extern void gl_stencil_mask(GLuint mask);

extern void gl_light_model_f(GLenum pname, GLfloat param) FLOAT_ABI_FIX;

extern void gl_light_f_v(GLenum light, GLenum pname, const GLfloat *params) FLOAT_ABI_FIX;

extern void gl_normal_pointer(GLenum type, GLsizei stride, const GLvoid *pointer);

extern void gl_stencil_op(GLenum fail, GLenum zfail, GLenum zpass);

extern void gl_active_texture(GLenum texture);
 
extern void gl_attach_shader(GLuint program, GLuint shader);
 
extern void gl_clear_stencil(GLint s);
 
extern void gl_compile_shader(GLuint shader);
 
extern GLuint gl_create_program();
 
extern GLuint gl_create_shader(GLenum type);
 
extern void gl_delete_program(GLuint program);

extern void gl_enable_vertex_attrib_array(GLuint index);

extern void gl_get_active_attrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);

extern void gl_get_active_uniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);

extern GLint gl_get_attrib_location(GLuint program, const GLchar *name);

extern void gl_get_program_info_log(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

extern void gl_get_program_i_v(GLuint program, GLenum pname, GLint *params);

extern void gl_get_shader_info_log(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

extern void gl_get_shader_i_v(GLuint shader, GLenum pname, GLint *params);

extern void gl_get_shader_precision_format(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);

extern GLint gl_get_uniform_location(GLuint program, const GLchar *name);

extern void gl_link_program(GLuint program);

extern void gl_release_shader_compiler();

extern void gl_shader_source(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);

extern void gl_uniform_1_f_v(GLint location, GLsizei count, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_1_i_v(GLint location, GLsizei count, const GLint *value);

extern void gl_uniform_2_f_v(GLint location, GLsizei count, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_2_i_v(GLint location, GLsizei count, const GLint *value);

extern void gl_uniform_3_f_v(GLint location, GLsizei count, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_3_i_v(GLint location, GLsizei count, const GLint *value);

extern void gl_uniform_4_f_v(GLint location, GLsizei count, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_4_i_v(GLint location, GLsizei count, const GLint *value);

extern void gl_uniform_matrix_2_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_matrix_3_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_uniform_matrix_4_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) FLOAT_ABI_FIX;

extern void gl_use_program(GLuint program);

extern void gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

#endif