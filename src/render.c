#include "render.h"
#include "matrix.h"
#include "math.h"

#include <stdio.h>
#include <stdlib.h>


float square_vertices[] = {
		    -0.5f, -0.5f, 0.0f,
		     0.5f, -0.5f, 0.0f,
		     0.5f,  0.5f, 0.0f,
		    -0.5f,  0.5f, 0.0f
};

unsigned int square_indices[] = {
			  0, 1, 2, 2, 3, 0
};

float * circle_vertices;

RenderRect make_rrect(float x, float y, float w, float h) {
  RenderRect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  return r;
};

RenderCircle make_rcircle(float x, float y, float r) {
  RenderCircle c = { x, y, r};
  c.x = x;
  c.y = y;
  c.r = r;
  return c;
};

RenderMaterial make_rmaterial_color(vec4 color) {
  RenderMaterial mat;
  mat.color = color;
  return mat;
};

float* get_material_color_ptr(const RenderMaterial mat) {
  return mat.color.v;
};

void create_render_square(RenderShape* shape) {
  // Create square shape
  RenderShape *square = shape;

  glGenVertexArrays(1, &square->VAO);
  glBindVertexArray(square->VAO);

  glGenBuffers(1, &square->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, square->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &square->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
  glEnableVertexAttribArray(0);

  square->draw_call_count = 6;

  glBindVertexArray(0);
};

void create_render_circle(RenderShape* shape, int circle_segments) {
  circle_segments += 2;

  RenderShape* circle = shape;

  circle_vertices = (float*)malloc(sizeof(float) * (circle_segments) * 3);

  circle_vertices[0] = 0.0f;
  circle_vertices[1] = 0.0f;
  circle_vertices[2] = 0.0f;

  float step = 3.14f * 2.0f / (float)(circle_segments - 2);
  float angle = 0.0f;

  for(int i = 1; i < circle_segments; i++) {
    float cx = sin(angle);
    float cy = cos(angle);

    *(circle_vertices + i * 3 + 0) = cx;
    *(circle_vertices + i * 3 + 1) = cy;
    *(circle_vertices + i * 3 + 2) = 0.0f;

    angle += step;
  };

  glGenVertexArrays(1, &circle->VAO);
  glBindVertexArray(circle->VAO);

  glGenBuffers(1, &circle->VBO);  
  glBindBuffer(GL_ARRAY_BUFFER, circle->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (circle_segments) * 3, circle_vertices, GL_STATIC_DRAW);

  circle->EBO = 0;

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
  glEnableVertexAttribArray(0);

  circle->draw_call_count = circle_segments;

  glBindVertexArray(0);
};

void init_renderer(Renderer* renderer, Shader* shader, int circle_segments) {
  renderer->shader = shader;
  create_render_square(&renderer->square);
  create_render_circle(&renderer->circle, circle_segments);
};

void free_render_shape(RenderShape* shape) {
  if(shape->VAO != 0) {
    glDeleteVertexArrays(1, &shape->VAO);
  }
  if(shape->VBO != 0) {
    glDeleteBuffers(1, &shape->VBO);
  }
  if(shape->EBO != 0) {
    glDeleteBuffers(1, &shape->EBO);
  }
}

void free_renderer(Renderer* renderer) {
  free_render_shape(&renderer->square);
  free_render_shape(&renderer->circle);
  free(circle_vertices);
};

void render_rect(Renderer* renderer, const RenderRect rect, const RenderMaterial mat) {
  Matrix4 scale;
  set_scale_mat4(&scale, rect.w, rect.h, 1.0f);

  Matrix4 translation;
  set_translate_mat4(&translation, rect.x, rect.y, 0.0f);

  Matrix4 model = multiply_mat4(scale, translation);

  uniform_matrix4_shader(renderer->shader, "model", model);
  uniform_vec4_shader(renderer->shader, "color", get_material_color_ptr(mat));
  
  glBindVertexArray(renderer->square.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->square.VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->square.EBO);


  glDrawElements(GL_TRIANGLES, renderer->square.draw_call_count, GL_UNSIGNED_INT, 0);
};

void render_circle(Renderer* renderer, const RenderCircle circle, const RenderMaterial mat) {
  Matrix4 scale;
  set_scale_mat4(&scale, circle.r, circle.r, 1.0f);

  Matrix4 translation;
  set_translate_mat4(&translation, circle.x, circle.y, 0.0f);

  Matrix4 model = multiply_mat4(scale, translation);

  uniform_matrix4_shader(renderer->shader, "model", model);
  uniform_vec4_shader(renderer->shader, "color", get_material_color_ptr(mat));
  
  glBindVertexArray(renderer->circle.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->circle.VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->circle.EBO);

  glDrawArrays(GL_TRIANGLE_FAN, 0, renderer->circle.draw_call_count);
};
