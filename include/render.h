#ifndef _RENDER_H_
#define _RENDER_H_

#include "shader.h"
#include "opengl_impl.h"

typedef struct {
  float x, y, w, h;
} RenderRect;

extern RenderRect make_rrect(float x, float y, float w, float h);

typedef struct {
  float x, y, r;
} RenderCircle;

extern RenderCircle make_rcircle(float x, float y, float r);

typedef struct {
  unsigned int draw_call_count;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
} RenderShape;

typedef struct {
  Shader* shader;

  RenderShape square;
  RenderShape circle;
} Renderer;

extern void init_renderer(Renderer* renderer, Shader* shader, int circle_segments);
extern void free_renderer(Renderer* renderer);

extern void render_rect(Renderer* renderer, const RenderRect rect);
extern void render_circle(Renderer* renderer, const RenderCircle circle);

#endif
