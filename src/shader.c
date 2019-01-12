#include "shader.h"
#include "opengl_impl.h"

#include <stdio.h>
#include <stdlib.h>

char* load_file(const char* filename);

char* load_file_contents(const char* filename) {
  FILE* f = fopen(filename, "r");

  if(f == NULL) {
    return NULL;
  }

  char* contents;

  long int file_size = 0;
  fseek(f, 0, SEEK_END);
  file_size = ftell(f);

  contents = (char*)calloc(file_size + 1, 1);
  *(contents + file_size) = '\0';

  fseek(f, 0, SEEK_SET);

  fread(contents, 1, file_size, f);

  fclose(f);

  return contents;
};

void check_compile(GLuint shader) {
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  // Check if compilation failed
  if(success == GL_FALSE) {
    char logInfo[512];
    glGetShaderInfoLog(shader, 512, NULL, logInfo);
    printf("Shader compilation error: %s\n", logInfo);
  }
};

void create_shader(Shader* shader, const char* vert_file, const char* frag_file) {
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

  char* vertex_source = load_file_contents(vert_file);
  char* fragment_source = load_file_contents(frag_file);

  glShaderSource(vertex_id, 1, (const GLchar**)&vertex_source, NULL);
  glShaderSource(fragment_id, 1, (const GLchar**)&fragment_source, NULL);

  glCompileShader(vertex_id);
  check_compile(vertex_id);
  glCompileShader(fragment_id);
  check_compile(fragment_id);

  GLuint pid = glCreateProgram();

  glAttachShader(pid, vertex_id);
  glAttachShader(pid, fragment_id);
  glLinkProgram(pid);
  
  //glDeleteShader(vertex_id);
  //glDeleteShader(fragment_id);

  free(vertex_source);
  free(fragment_source);

  shader->program_id = pid;
  shader->vertex_id = vertex_id;
  shader->fragment_id = fragment_id;
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

