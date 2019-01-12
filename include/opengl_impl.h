#ifndef _OPENGL_IMPLEMENTATION_H_
#define _OPENGL_IMPLEMENTATION_H_

#include <windows.h>
#include <gl/glcorearb.h>
#include <gl/wglext.h>

typedef struct {
  HMODULE gl_library;
} OpenGLFunctions;

// Defines

// General
#define glGetError() f_glGetError()
#define glGetString(name) f_glGetString(name)
#define glClear(mask) f_glClear(mask)
#define glEnable(cap) f_glEnable(cap)
#define glDisable(cap) f_glDisable(cap)

// Buffer
#define glGenBuffers(n, buffers) f_glGenBuffers(n, buffers)
#define glBindBuffer(target, buffer) f_glBindBuffer(target, buffer)
#define glBufferData(target, size, data, usage) f_glBufferData(target, size, data, usage)
#define glDeleteBuffers(n, buffers) f_glDeleteBuffers(n, buffers)

// Vertex
#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) f_glVertexAttribPointer(index, size, type, normalized, stride, pointer)
#define glEnableVertexAttribArray(index) f_glEnableVertexAttribArray(index)
#define glDisableVertexAttribArray(index) f_glDisableVertexAttribArray(index)
#define glGenVertexArrays(n, arrays) f_glGenVertexArrays(n, arrays)
#define glBindVertexArray(array) f_glBindVertexArray(array)
#define glDeleteVertexArrays(n, arrays) f_glDeleteVertexArrays(n, arrays)

// Shader
#define glGetShaderiv(shader, pname, params) f_glGetShaderiv(shader, pname, params)
#define glGetShaderInfoLog(shader, maxLength, length, infoLog) f_glGetShaderInfoLog(shader, maxLength, length, infoLog)
#define glCreateProgram() f_glCreateProgram()
#define glCreateShader(type) f_glCreateShader(type)
#define glShaderSource(shader, count, string, length) f_glShaderSource(shader, count, string, length)
#define glCompileShader(shader) f_glCompileShader(shader)
#define glAttachShader(program, shader) f_glAttachShader(program, shader)
#define glLinkProgram(program) f_glLinkProgram(program)
#define glUseProgram(program) f_glUseProgram(program)
#define glDeleteShader(shader) f_glDeleteShader(shader)

// Drawcall
#define glClearColor(r, g, b, a) f_glClearColor(r, g, b, a)
#define glViewport(x, y, width, height) f_glViewport(x, y, width, height)
#define glDrawArrays(mode, first, count) f_glDrawArrays(mode, first, count)
#define glDrawElements(mode, count, type, indices) f_glDrawElements(mode, count, type, indices)

// Uniform
#define glGetUniformLocation(program, name) f_glGetUniformLocation(program, name)
#define glUniformMatrix4fv(location, count, transpose, value) f_glUniformMatrix4fv(location, count, transpose, value)
#define glUniform4fv(location, count, value) f_glUniform4fv(location, count, value)

/*
  Function pointers
*/

// General
extern GLenum(__cdecl *f_glGetError)();
extern GLubyte*(__cdecl *f_glGetString)(GLenum);
extern void(__cdecl *f_glClear)(GLbitfield);
extern void(__cdecl *f_glEnable)(GLenum);
extern void(__cdecl *f_glDisable)(GLenum);

// Buffer
extern void(__cdecl *f_glGenBuffers)(GLsizei, GLuint*);
extern void(__cdecl *f_glBindBuffer)(GLenum, GLuint);
extern void(__cdecl *f_glBufferData)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
extern void(__cdecl *f_glDeleteBuffers)(GLsizei, const GLuint*);

// Vertex
extern void(__cdecl *f_glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
extern void(__cdecl *f_glEnableVertexAttribArray)(GLuint);
extern void(__cdecl *f_glDisableVertexAttribArray)(GLuint);
extern void(__cdecl *f_glGenVertexArrays)(GLsizei, GLuint*);
extern void(__cdecl *f_glBindVertexArray)(GLuint);
extern void(__cdecl *f_glDeleteVertexArrays)(GLsizei, GLuint*);

// Shader
extern void(__cdecl *f_glGetShaderiv)(GLuint, GLenum, GLint*);
extern void(__cdecl *f_glGetShaderInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*);
extern GLuint(__cdecl *f_glCreateProgram)();
extern GLuint(__cdecl *f_glCreateShader)(GLenum);
extern void(__cdecl *f_glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
extern void(__cdecl *f_glCompileShader)(GLuint shader);
extern void(__cdecl *f_glAttachShader)(GLuint program, GLuint shader);
extern void(__cdecl *f_glLinkProgram)(GLuint program);
extern void(__cdecl *f_glUseProgram)(GLuint program);
extern void(__cdecl *f_glDeleteShader)(GLuint shader);

// Drawcall
extern void(__cdecl *f_glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
extern void(__cdecl *f_glViewport)(GLint, GLint, GLsizei, GLsizei);
extern void(__cdecl *f_glDrawArrays)(GLenum, GLint, GLsizei);
extern void(__cdecl *f_glDrawElements)(GLenum, GLsizei, GLenum, const GLvoid*);

// Uniform
extern GLint(__cdecl *f_glGetUniformLocation)(GLuint, const GLchar*);
extern void(__cdecl *f_glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat*);
extern void(__cdecl *f_glUniform4fv)(GLint, GLsizei, const GLfloat*);

// OpenGLFunctions loading and freeing

extern void initialize_opengl_functions(OpenGLFunctions* context);
extern void free_opengl_functions(OpenGLFunctions* context);

#endif
