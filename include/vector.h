#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct {
  float v[3];
} vec3;

typedef struct {
  float v[4];
} vec4;

extern void make_vec4(vec4* v, float x, float y, float z, float w);

#endif
