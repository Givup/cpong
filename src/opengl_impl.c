#include <assert.h>
#include "opengl_impl.h"

// Macro define
#define LOAD_FUNC(f, n) (f = get_gl_func_address(context, n)); assert("Failed to bind OpenGL function call" && f)

/*
  Function pointers
 */

// General
GLenum(__cdecl *f_glGetError)();
GLubyte*(__cdecl *f_glGetString)(GLenum);
void(__cdecl *f_glClear)(GLbitfield);
void(__cdecl *f_glEnable)(GLenum);
void(__cdecl *f_glDisable)(GLenum);

// Buffer
void(__cdecl *f_glGenBuffers)(GLsizei, GLuint*);
void(__cdecl *f_glBindBuffer)(GLenum, GLuint);
void(__cdecl *f_glBufferData)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
void(__cdecl *f_glDeleteBuffers)(GLsizei, const GLuint*);

// Vertex
void(__cdecl *f_glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
void(__cdecl *f_glEnableVertexAttribArray)(GLuint);
void(__cdecl *f_glDisableVertexAttribArray)(GLuint);
void(__cdecl *f_glGenVertexArrays)(GLsizei, GLuint*);
void(__cdecl *f_glBindVertexArray)(GLuint);
void(__cdecl *f_glDeleteVertexArrays)(GLsizei, GLuint*);

// Shader
void(__cdecl *f_glGetShaderiv)(GLuint, GLenum, GLint*);
void(__cdecl *f_glGetShaderInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*);
GLuint(__cdecl *f_glCreateProgram)();
GLuint(__cdecl *f_glCreateShader)(GLenum);
void(__cdecl *f_glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
void(__cdecl *f_glCompileShader)(GLuint shader);
void(__cdecl *f_glAttachShader)(GLuint program, GLuint shader);
void(__cdecl *f_glLinkProgram)(GLuint program);
void(__cdecl *f_glUseProgram)(GLuint program);
void(__cdecl *f_glDeleteShader)(GLuint shader);

// Drawcall
void(__cdecl *f_glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
void(__cdecl *f_glViewport)(GLint, GLint, GLsizei, GLsizei);
void(__cdecl *f_glDrawArrays)(GLenum, GLint, GLsizei);
void(__cdecl *f_glDrawElements)(GLenum, GLsizei, GLenum, const GLvoid*);

// Uniform
GLint(__cdecl *f_glGetUniformLocation)(GLuint, const GLchar*);
void(__cdecl *f_glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat*);
void(__cdecl *f_glUniform4fv)(GLint, GLsizei, const GLfloat*);

// Load opengl function dynamically from opengl32.dll
void* get_gl_func_address(OpenGLFunctions* context, const char* func_name) {
  void* p = (void*)wglGetProcAddress(func_name);
  if(p == 0 || p == (void*)1 || p == (void*)2 ||p == (void*)3 || p == (void*)-1) {
    p = (void*)GetProcAddress(context->gl_library, func_name);
  }
  return p;
};

// Load library and load all required function pointers
void initialize_opengl_functions(OpenGLFunctions* context) {
  HMODULE library = LoadLibrary("opengl32.dll");
  context->gl_library = library;

  // General
  LOAD_FUNC(f_glGetError, "glGetError");
  LOAD_FUNC(f_glGetString, "glGetString");
  LOAD_FUNC(f_glClear, "glClear");
  LOAD_FUNC(f_glEnable, "glEnable");
  LOAD_FUNC(f_glDisable, "glDisable");

  // Buffer
  LOAD_FUNC(f_glGenBuffers, "glGenBuffers");
  LOAD_FUNC(f_glBindBuffer, "glBindBuffer");
  LOAD_FUNC(f_glBufferData, "glBufferData");
  LOAD_FUNC(f_glDeleteBuffers, "glDeleteBuffers");

  // Vertex
  LOAD_FUNC(f_glVertexAttribPointer, "glVertexAttribPointer");
  LOAD_FUNC(f_glEnableVertexAttribArray, "glEnableVertexAttribArray");
  LOAD_FUNC(f_glDisableVertexAttribArray, "glDisableVertexAttribArray");
  LOAD_FUNC(f_glGenVertexArrays, "glGenVertexArrays");
  LOAD_FUNC(f_glBindVertexArray, "glBindVertexArray");
  LOAD_FUNC(f_glDeleteVertexArrays, "glDeleteVertexArrays");

  // Shader
  LOAD_FUNC(f_glGetShaderiv, "glGetShaderiv");
  LOAD_FUNC(f_glGetShaderInfoLog, "glGetShaderInfoLog");
  LOAD_FUNC(f_glCreateProgram, "glCreateProgram");
  LOAD_FUNC(f_glCreateShader, "glCreateShader");
  LOAD_FUNC(f_glShaderSource, "glShaderSource");
  LOAD_FUNC(f_glCompileShader, "glCompileShader");
  LOAD_FUNC(f_glAttachShader, "glAttachShader");
  LOAD_FUNC(f_glLinkProgram, "glLinkProgram");
  LOAD_FUNC(f_glUseProgram, "glUseProgram");
  LOAD_FUNC(f_glDeleteShader, "glDeleteShader");

  // Drawcall
  LOAD_FUNC(f_glClearColor, "glClearColor");
  LOAD_FUNC(f_glViewport, "glViewport");
  LOAD_FUNC(f_glDrawArrays, "glDrawArrays");
  LOAD_FUNC(f_glDrawElements, "glDrawElements");

  // Uniform
  LOAD_FUNC(f_glGetUniformLocation, "glGetUniformLocation");
  LOAD_FUNC(f_glUniformMatrix4fv, "glUniformMatrix4fv");
  LOAD_FUNC(f_glUniform4fv, "glUniform4fv");
};

// Free loaded library
void free_opengl_functions(OpenGLFunctions* context) {
  if(context->gl_library != NULL) {
    FreeLibrary(context->gl_library);
  }
};
