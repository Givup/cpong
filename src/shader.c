#include "shader.h"
#include "opengl_impl.h"

#include <stdio.h>
#include <stdlib.h>

char* load_file(const char* filename);

char* load_file_contents(const char* filename, int* length) {
  FILE* f = fopen(filename, "rb");

  if(f == NULL) {
    printf("Failed to open file: %s\n", filename);
    return NULL;
  }

  long int file_size = 0;
  fseek(f, 0, SEEK_END);
  file_size = ftell(f);

  char* contents = (char*)(malloc(file_size));

  if(contents == NULL) {
      printf("Failed to allocate memory for file!\n");
	  return NULL;
  }
  
  *(contents + file_size) = 0;

  fseek(f, 0, SEEK_SET);

  fread(contents, 1, file_size, f);

  fclose(f);

  *length = file_size;

  return (void*)contents;
};

void check_compile(GLuint shader) {
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  // Check if compilation failed
  if(success == GL_FALSE) {
    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    printf("The log length is %d\n", logLength);
    GLchar* logInfo = (GLchar*)malloc(logLength);
    glGetShaderInfoLog(shader, logLength, NULL, logInfo);
    printf("Shader compilation error: %s\n", logInfo);
    free(logInfo);
  }
};

void create_shader(Shader* shader, const char* vert_file, const char* frag_file) {
  GLuint pid = glCreateProgram();
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

  int v_length;
  char* vertex_source = load_file_contents(vert_file, &v_length);
  f_glShaderSource((GLuint)vertex_id, (GLsizei)1, (const GLchar**)&vertex_source, &v_length);
  glCompileShader((GLuint)vertex_id);
  check_compile(vertex_id);

  int f_length;
  char* fragment_source = load_file_contents(frag_file, &f_length);
  f_glShaderSource((GLuint)fragment_id, (GLsizei)1, (const GLchar**)&fragment_source, &f_length);
  glCompileShader((GLuint)fragment_id);
  check_compile(fragment_id);

  glAttachShader(pid, vertex_id);
  glAttachShader(pid, fragment_id);
  glLinkProgram(pid);

  shader->program_id = pid;
  shader->vertex_id = vertex_id;
  shader->fragment_id = fragment_id;

  free(vertex_source);
  free(fragment_source);
};

void use_shader(Shader* shader) {
  glUseProgram(shader->program_id);
};

void free_shader(Shader* shader) {
  // TODO: Shader deallocation
};

void uniform_matrix4_shader(Shader* shader, const char* uniform_name, const Matrix4 matrix) {
  GLint location = glGetUniformLocation(shader->program_id, uniform_name);
  glUniformMatrix4fv(location, 1, GL_TRUE, &matrix.values[0]);
};

void uniform_vec4_shader(Shader* shader, const char* uniform_name, const float* values) {
  GLint location = glGetUniformLocation(shader->program_id, uniform_name);
  glUniform4fv(location, 1, values);
};

