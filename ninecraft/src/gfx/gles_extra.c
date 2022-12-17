#include <ninecraft/gfx/gles_compat.h>

void gl_bind_texture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
}

void gl_bind_buffer(GLenum target, GLuint buffer) {
    glBindBuffer(target, buffer);
}

void gl_blend_func(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}

void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid *pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void gl_shade_model(GLenum mode) {
    // nothing
}

void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz) {
    // nothing
}

void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glScissor(x, y, width, height);
}

void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) {
    glReadPixels(x, y, width, height, format, type, pixels);
}

void gl_polygon_offset(GLfloat factor, GLfloat units) {
    glPolygonOffset(factor, units);
}

void gl_line_width(GLfloat width) {
    glLineWidth(width);
}

void gl_hint(GLenum target, GLenum mode) {
    if (target != GL_PERSPECTIVE_CORRECTION_HINT) {
        glHint(target, mode);
    } 
}

const GLubyte *gl_get_string(GLenum name) {
    return glGetString(name);
}


void gl_gen_textures(GLsizei n, GLuint *textures) {
    glGenTextures(n, textures);
}

void gl_depth_range_f(GLclampf zNear, GLclampf zFar) {
    glDepthRangef(zNear, zFar);
}

void gl_depth_mask(GLboolean flag) {
    glDepthMask(flag);
}

void gl_depth_func(GLenum func) {
    glDepthFunc(func);
}

void gl_delete_textures(GLsizei n, const GLuint *textures) {
    glDeleteTextures(n, textures);
}

void gl_delete_buffers(GLsizei n,const GLuint *buffers) {
    glDeleteBuffers(n, buffers);
}

void gl_cull_face(GLenum mode) {
    glCullFace(mode);
}

void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glColorMask(red, green, blue, alpha);
}

void gl_clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glClearColor(red, green, blue, alpha);
}

void gl_clear(GLbitfield mask) {
    glClear(mask);
}

void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    glBufferData(target, size, data, usage);
}