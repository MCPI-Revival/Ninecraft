#ifndef NINECRAFT_GFX_GLES_COMPAT_H
#define NINECRAFT_GFX_GLES_COMPAT_H

#include <GL/gl.h>

void gl_alpha_func(GLenum func, GLclampf ref);

void gl_bind_buffer(GLenum target, GLuint buffer);

void gl_bind_texture(GLenum target, GLuint texture);

void gl_blend_func(GLenum sfactor, GLenum dfactor);

void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

void gl_clear(GLbitfield mask);

void gl_clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer);

void gl_cull_face(GLenum mode);

void gl_delete_buffers(GLsizei n,const GLuint *buffers);

void gl_delete_textures(GLsizei n, const GLuint *textures);

void gl_depth_func(GLenum func);

void gl_depth_mask(GLboolean flag);

void gl_depth_range_f(GLclampf zNear, GLclampf zFar);

void gl_disable(GLenum cap);

void gl_disable_client_state(GLenum array);

void gl_draw_arrays(GLenum mode, GLint first, GLsizei count);

void gl_enable(GLenum cap);

void gl_enable_client_state(GLenum array);

void gl_fog_f(GLenum pname, GLfloat param);

void gl_fog_f_v(GLenum pname, const GLfloat *params);

void gl_fog_x(GLenum pname, GLfixed param);

void gl_gen_textures(GLsizei n, GLuint *textures);

void gl_get_float_v(GLenum pname, GLfloat *params);

const GLubyte *gl_get_string(GLenum name);

void gl_hint(GLenum target, GLenum mode);

void gl_line_width(GLfloat width);

void gl_load_identity();

void gl_matrix_mode(GLenum mode);

void gl_mult_matrix_f(const GLfloat *m);

void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz);

void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

void gl_polygon_offset(GLfloat factor, GLfloat units);

void gl_pop_matrix();

void gl_push_matrix();

void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);

void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

void gl_scale_f(GLfloat x, GLfloat y, GLfloat z);

void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height);

void gl_shade_model(GLenum mode);

void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid *pixels);

void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param);

void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

void gl_translate_f(GLfloat x, GLfloat y, GLfloat z);

void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height);

#endif