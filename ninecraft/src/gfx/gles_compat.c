#include <ninecraft/gfx/gles_compat.h>

NINECRAFT_FLOAT_FUNC void gl_alpha_func(GLenum func, GLclampf ref) {
    glAlphaFunc(func, ref);
}

void gl_bind_buffer(GLenum target, GLuint buffer) {
    glBindBuffer(target, buffer);
}

void gl_bind_texture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
}

void gl_blend_func(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}

void gl_buffer_data(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    glBufferData(target, size, data, usage);
}

void gl_clear(GLbitfield mask) {
    glClear(mask);
}

NINECRAFT_FLOAT_FUNC void gl_clear_color(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
    glClearColor(red, green, blue, alpha);
}

NINECRAFT_FLOAT_FUNC void gl_color_4_f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glColor4f(red, green, blue, alpha);
}

void gl_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glColorMask(red, green, blue, alpha);
}

void gl_color_pointer(GLint size, GLenum type, GLsizei stride, const void *pointer) {
    glColorPointer(size, type, stride, pointer);
}

void gl_cull_face(GLenum mode) {
    glCullFace(mode);
}

void gl_delete_buffers(GLsizei n, const GLuint *buffers) {
    glDeleteBuffers(n, buffers);
}

void gl_delete_textures(GLsizei n, const GLuint *textures) {
    glDeleteTextures(n, textures);
}

void gl_depth_func(GLenum func) {
    glDepthFunc(func);
}

void gl_depth_mask(GLboolean flag) {
    glDepthMask(flag);
}

NINECRAFT_FLOAT_FUNC void gl_depth_range_f(GLclampf near, GLclampf far) {
    glDepthRange((GLclampd)near, (GLclampd)far);
}

void gl_disable(GLenum cap) {
    glDisable(cap);
}

void gl_disable_client_state(GLenum array) {
    glDisableClientState(array);
}

void gl_draw_arrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
}

void gl_enable(GLenum cap) {
    glEnable(cap);
}

void gl_enable_client_state(GLenum array) {
    glEnableClientState(array);
}

NINECRAFT_FLOAT_FUNC void gl_fog_f(GLenum pname, GLfloat param) {
    glFogf(pname, param);
}

NINECRAFT_FLOAT_FUNC void gl_fog_f_v(GLenum pname, const GLfloat *params) {
    glFogfv(pname, params);
}

void gl_fog_x(GLenum pname, GLfixed param) {
    glFogi(pname, param);
}

void gl_gen_textures(GLsizei n, GLuint *textures) {
    glGenTextures(n, textures);
}

NINECRAFT_FLOAT_FUNC void gl_get_float_v(GLenum pname, GLfloat *params) {
    glGetFloatv(pname, params);
}

const GLubyte *gl_get_string(GLenum name) {
    return glGetString(name);
}

void gl_hint(GLenum target, GLenum mode) {
    glHint(target, mode);
}

NINECRAFT_FLOAT_FUNC void gl_line_width(GLfloat width) {
    glLineWidth(width);
}

void gl_load_identity() {
    glLoadIdentity();
}

void gl_matrix_mode(GLenum mode) {
    glMatrixMode(mode);
}

NINECRAFT_FLOAT_FUNC void gl_mult_matrix_f(const GLfloat *m) {
    glMultMatrixf(m);
}

NINECRAFT_FLOAT_FUNC void gl_normal_3_f(GLfloat nx, GLfloat ny, GLfloat nz) {
    glNormal3f(nx, ny, nz);
}

NINECRAFT_FLOAT_FUNC void gl_ortho_f(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
    glOrtho((GLdouble)left, (GLdouble)right, (GLdouble)bottom, (GLdouble)top, (GLdouble)near, (GLdouble)far);
}

NINECRAFT_FLOAT_FUNC void gl_polygon_offset(GLfloat factor, GLfloat units) {
    glPolygonOffset(factor, units);
}

void gl_pop_matrix() {
    glPopMatrix();
}

void gl_push_matrix() {
    glPushMatrix();
}

void gl_read_pixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) {
    glReadPixels(x, y, width, height, format, type, pixels);
}

NINECRAFT_FLOAT_FUNC void gl_rotate_f(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    glRotatef(angle, x, y, z);
}

NINECRAFT_FLOAT_FUNC void gl_scale_f(GLfloat x, GLfloat y, GLfloat z) {
    glScalef(x, y, z);
}

void gl_scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glScissor(x, y, width, height);
}

void gl_shade_model(GLenum mode) {
    glShadeModel(mode);
}

void gl_tex_coord_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glTexCoordPointer(size, type, stride, pointer);
}

void gl_tex_image_2_d(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void gl_tex_parameter_i(GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

void gl_tex_sub_image_2_d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

NINECRAFT_FLOAT_FUNC void gl_translate_f(GLfloat x, GLfloat y, GLfloat z) {
    glTranslatef(x, y, z);
}

void gl_vertex_pointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    glVertexPointer(size, type, stride, pointer);
}

void gl_viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

void gl_draw_elements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    glDrawElements(mode, count, type, indices);
}

GLenum gl_get_error() {
    return glGetError();
}

void gl_gen_buffers(GLsizei n, GLuint *buffers) {
    glGenBuffers(n, buffers);
}

void gl_stencil_func(GLenum func, GLint ref, GLuint mask) {
    glStencilFunc(func, ref, mask);
}

void gl_stencil_mask(GLuint mask) {
    glStencilMask(mask);
}

NINECRAFT_FLOAT_FUNC void gl_light_model_f(GLenum pname, GLfloat param) {
    glLightModelf(pname, param);
}

NINECRAFT_FLOAT_FUNC void gl_light_f_v(GLenum light, GLenum pname, const GLfloat *params) {
    glLightfv(light, pname, params);
}

void gl_normal_pointer(GLenum type, GLsizei stride, const GLvoid *pointer) {
    glNormalPointer(type, stride, pointer);
}

void gl_stencil_op(GLenum fail, GLenum zfail, GLenum zpass) {
    glStencilOp(fail, zfail, zpass);
}

void gl_active_texture(GLenum texture) {
    glActiveTexture(texture);
}

void gl_attach_shader(GLuint program, GLuint shader) {
    glAttachShader(program, shader);
}

void gl_clear_stencil(GLint s) {
    glClearStencil(s);
}

void gl_compile_shader(GLuint shader) {
    glCompileShader(shader);
}

GLuint gl_create_program() {
    return glCreateProgram();
}

GLuint gl_create_shader(GLenum type) {
    return glCreateShader(type);
}

void gl_delete_program(GLuint program) {
    glDeleteProgram(program);
}

void gl_enable_vertex_attrib_array(GLuint index) {
    glEnableVertexAttribArray(index);
}

void gl_get_active_attrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

void gl_get_active_uniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

GLint gl_get_attrib_location(GLuint program, const GLchar *name) {
    return glGetAttribLocation(program, name);
}

void gl_get_program_info_log(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void gl_get_program_i_v(GLuint program, GLenum pname, GLint *params) {
    glGetProgramiv(program, pname, params);
}

void gl_get_shader_info_log(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void gl_get_shader_i_v(GLuint shader, GLenum pname, GLint *params) {
    glGetShaderiv(shader, pname, params);
}

void gl_get_shader_precision_format(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) {
    glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

GLint gl_get_uniform_location(GLuint program, const GLchar *name) {
    return glGetUniformLocation(program, name);
}

void gl_link_program(GLuint program) {
    glLinkProgram(program);
}

void gl_release_shader_compiler() {
    glReleaseShaderCompiler();
}

void gl_shader_source(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length) {
    glShaderSource(shader, count, string, length);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_1_f_v(GLint location, GLsizei count, const GLfloat *value) {
    glUniform1fv(location, count, value);
}

void gl_uniform_1_i_v(GLint location, GLsizei count, const GLint *value) {
    glUniform1iv(location, count, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_2_f_v(GLint location, GLsizei count, const GLfloat *value) {
    glUniform2fv(location, count, value);
}

void gl_uniform_2_i_v(GLint location, GLsizei count, const GLint *value) {
    glUniform2iv(location, count, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_3_f_v(GLint location, GLsizei count, const GLfloat *value) {
    glUniform3fv(location, count, value);
}

void gl_uniform_3_i_v(GLint location, GLsizei count, const GLint *value) {
    glUniform3iv(location, count, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_4_f_v(GLint location, GLsizei count, const GLfloat *value) {
    glUniform4fv(location, count, value);
}

void gl_uniform_4_i_v(GLint location, GLsizei count, const GLint *value) {
    glUniform4iv(location, count, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_matrix_2_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix2fv(location, count, transpose, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_matrix_3_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix3fv(location, count, transpose, value);
}

NINECRAFT_FLOAT_FUNC void gl_uniform_matrix_4_f_v(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix4fv(location, count, transpose, value);
}

void gl_use_program(GLuint program) {
    glUseProgram(program);
}

void gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}