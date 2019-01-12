#ifndef _SHADER_H_
#define _SHADER_H_

#include "matrix.h"
#include <gl/glcorearb.h>

typedef struct {
  GLuint program_id;
  GLuint vertex_id;
  GLuint fragment_id;
} Shader;

extern void create_shader(Shader* shader, const char* vert_file, const char* frag_file);
extern void use_shader(Shader* shader);
extern void free_shader(Shader* shader);

extern void uniform_matrix4_shader(Shader* shader, const char* uniform_name, const Matrix4 matrix);

#endif
