#ifndef NINECRAFT_GFX_GLES_COMPAT_H
#define NINECRAFT_GFX_GLES_COMPAT_H

#include <GLES/gl.h>

// Function documentation
// https://registry.khronos.org/OpenGL-Refpages/es1.1/xhtml/

extern void gl_alpha_func(GLenum func, GLclampf ref);

extern void gl_bind_buffer(GLenum target, GLuint buffer);

extern void gl_bind_texture(GLenum target, GLuint texture);

extern void gl_blend_func(GLenum sfactor, GLenum dfactor);

extern void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

extern void gl_clear(GLbitfield mask);

extern void gl_clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

extern void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

extern void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

extern void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer);

extern void gl_cull_face(GLenum mode);

extern void gl_delete_buffers(GLsizei n, const GLuint *buffers);

extern void gl_delete_textures(GLsizei n, const GLuint *textures);

extern void gl_depth_func(GLenum func);

extern void gl_depth_mask(GLboolean flag);

extern void gl_depth_range_f(GLclampf near, GLclampf far);

extern void gl_disable(GLenum cap);

extern void gl_disable_client_state(GLenum array);

extern void gl_draw_arrays(GLenum mode, GLint first, GLsizei count);

extern void gl_enable(GLenum cap);

extern void gl_enable_client_state(GLenum array);

extern void gl_fog_f(GLenum pname, GLfloat param);

extern void gl_fog_f_v(GLenum pname, const GLfloat *params);

extern void gl_fog_x(GLenum pname, GLfixed param);

extern void gl_gen_textures(GLsizei n, GLuint *textures);

extern void gl_get_float_v(GLenum pname, GLfloat *params);

const GLubyte *gl_get_string(GLenum name);

extern void gl_hint(GLenum target, GLenum mode);

extern void gl_line_width(GLfloat width);

extern void gl_load_identity();

extern void gl_matrix_mode(GLenum mode);

extern void gl_mult_matrix_f(const GLfloat *m);

extern void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz);

extern void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);

extern void gl_polygon_offset(GLfloat factor, GLfloat units);

extern void gl_pop_matrix();

extern void gl_push_matrix();

extern void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);

extern void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

extern void gl_scale_f(GLfloat x, GLfloat y, GLfloat z);

extern void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height);

extern void gl_shade_model(GLenum mode);

extern void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

extern void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param);

extern void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

extern void gl_translate_f(GLfloat x, GLfloat y, GLfloat z);

extern void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height);

#endif