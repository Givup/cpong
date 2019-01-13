#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct {
  float v[2];
} vec2;

typedef struct {
  float v[3];
} vec3;

typedef struct {
  float v[4];
} vec4;

extern vec2 make_vec2(float x, float y);
extern void set_vec2(vec2* v, float x, float y);
extern float dot_vec2(const vec2 a, const vec2 b);
extern vec2 sub_vec2(const vec2 a, const vec2 b);
extern vec2 scale_vec2(const vec2 a, const float t);
extern vec2 normalize_vec2(const vec2 v);
extern vec2 reflect_vec2(const vec2 v, const vec2 n);


extern vec4 make_vec4(float x, float y, float z, float w);
extern void set_vec4(vec4* v, float x, float y, float z, float w);

#endif
