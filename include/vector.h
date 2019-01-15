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

extern float get_x_vec2(const vec2 v);
extern float get_y_vec2(const vec2 v);
extern void set_x_vec2(vec2* v, float x);
extern void set_y_vec2(vec2* v, float y);

extern vec2 make_vec2(float x, float y);
extern void set_vec2(vec2* v, float x, float y);
extern float dot_vec2(const vec2 a, const vec2 b);
extern vec2 sub_vec2(const vec2 a, const vec2 b);
extern vec2 mul_vec2(const vec2 a, const vec2 b);
extern vec2 scale_vec2(const vec2 a, const float t);
extern vec2 normalize_vec2(const vec2 v);
extern vec2 reflect_vec2(const vec2 v, const vec2 n);

extern float get_x_vec4(const vec4 v);
extern float get_y_vec4(const vec4 v);
extern float get_z_vec4(const vec4 v);
extern float get_w_vec4(const vec4 v);
extern void set_x_vec4(vec4* v, float x);
extern void set_y_vec4(vec4* v, float y);
extern void set_z_vec4(vec4* v, float z);
extern void set_w_vec4(vec4* v, float w);

extern void add_vec4(vec4* a, const vec4 b);
extern vec4 scale_vec4(const vec4 a, const float t);


extern vec4 make_vec4(float x, float y, float z, float w);
extern void set_vec4(vec4* v, float x, float y, float z, float w);

#endif
