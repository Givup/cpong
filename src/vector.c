#include "vector.h"

void make_vec4(vec4* v, float x, float y, float z, float w) {
  v->v[0] = x;
  v->v[1] = y;
  v->v[2] = z;
  v->v[3] = w;
};
