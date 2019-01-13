#include <math.h>

#include "vector.h"

vec2 make_vec2(float x, float y) {
  vec2 v;
  v.v[0] = x;
  v.v[1] = y;
  return v;
};

void set_vec2(vec2* v, float x, float y) {
  v->v[0] = x;
  v->v[1] = y;
};

float dot_vec2(const vec2 v0, const vec2 v1) {
  return v0.v[0] * v1.v[0] + v0.v[1] * v1.v[1];
};

float length_vec2(const vec2 v) {
  return sqrt(v.v[0] * v.v[0] + v.v[1] * v.v[1]);
};

vec2 negate_vec2(const vec2 v) {
  vec2 result;
  result.v[0] = -v.v[0];
  result.v[1] = -v.v[1];
  return result;
}

vec2 normalize_vec2(const vec2 v) {
  float l = length_vec2(v);
  vec2 result;
  result.v[0] = v.v[0] / l;
  result.v[1] = v.v[1] / l;
  return result;
};

vec2 add_vec2(const vec2 a, const vec2 b) {
  vec2 result;
  result.v[0] = a.v[0] + b.v[0];
  result.v[1] = a.v[1] + b.v[1];
  return result;
};

vec2 sub_vec2(const vec2 a, const vec2 b) {
  vec2 result;
  result.v[0] = a.v[0] - b.v[0];
  result.v[1] = a.v[1] - b.v[1];
  return result;
};

vec2 scale_vec2(const vec2 a, const float t) {
  vec2 result;
  result.v[0] = a.v[0] * t;
  result.v[1] = a.v[1] * t;
  return result;
};

vec2 reflect_vec2(const vec2 v, const vec2 n) {
  float dot_vn = -2.0f * dot_vec2(v, n);
  vec2 dotted_n = scale_vec2(n, dot_vn);
  vec2 result = add_vec2(dotted_n, v);
  return result;
};


vec4 make_vec4(float x, float y, float z, float w) {
  vec4 v;
  v.v[0] = x;
  v.v[1] = y;
  v.v[2] = z;
  v.v[3] = w;
  return v;
};

void set_vec4(vec4* v, float x, float y, float z, float w) {
  v->v[0] = x;
  v->v[1] = y;
  v->v[2] = z;
  v->v[3] = w;
};
