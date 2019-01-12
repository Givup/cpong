#include "matrix.h"

#include <stdio.h>

void clear_mat4(Matrix4* mat, float def_value) {
  for(int i = 0;i < 16;i++) {
    mat->values[i] = def_value;
  }
};

void identity_mat4(Matrix4* mat) {
  for(int i= 0; i < 16; i++) {
    if(i % 5 == 0) {
      mat->values[i] = 1.0f;
    } else {
      mat->values[i] = 0.0f;
    }
  }
};

Matrix4 multiply_mat4(const Matrix4 a, const Matrix4 b) {
  Matrix4 tot;

  for(int i = 0;i < 16;i++) {

    int r_index = i % 4;
    int c_index = i / 4;

    float total = 0.0f;
    for(int j = 0;j < 4;j++) {
      total += a.values[r_index * 4 + j] * b.values[j * 4 + c_index];
    }
    tot.values[i] = total;
  }

  return tot;
};

void set_row_mat4(Matrix4* mat, int row, float v0, float v1, float v2, float v3){
  mat->values[row +  0] = v0;
  mat->values[row +  4] = v1;
  mat->values[row +  8] = v2;
  mat->values[row + 12] = v3;
};

void set_column_mat4(Matrix4* mat, int column, float v0, float v1, float v2, float v3) {
  mat->values[column * 4 + 0] = v0;
  mat->values[column * 4 + 1] = v1;
  mat->values[column * 4 + 2] = v2;
  mat->values[column * 4 + 3] = v3;
};

// Source: https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix
void set_ortho_mat4(Matrix4* mat, float left, float top, float right, float bottom) {
  float far  =  1.0f;
  float near = -1.0f;

  mat->values[ 0] = 2.0f / (right - left);
  mat->values[ 1] = 0.0f;
  mat->values[ 2] = 0.0f;
  mat->values[ 3] = -((right + left) / (right - left));

  mat->values[ 4] = 0.0f;
  mat->values[ 5] = 2.0f / (top - bottom);
  mat->values[ 6] = 0.0f;
  mat->values[ 7] = -((top + bottom) / (top - bottom));

  mat->values[ 8] = 0.0f;
  mat->values[ 9] = 0.0f;
  mat->values[10] = -2.0f / (far - near);
  mat->values[11] = -((far + near) / (far - near));

  mat->values[12] = 0.0f;
  mat->values[13] = 0.0f;
  mat->values[14] = 0.0f;
  mat->values[15] = 1.0f;
};

void set_scale_mat4(Matrix4* mat, float x, float y, float z) {
  clear_mat4(mat, 0.0f);
  mat->values[0] = x;
  mat->values[5] = y;
  mat->values[10] = z;
  mat->values[15] = 1.0f;
};

void set_translate_mat4(Matrix4* mat, float x, float y, float z) {
  clear_mat4(mat, 0.0f);
  set_row_mat4(mat, 0, 1.0f, 0.0f, 0.0f,    x);
  set_row_mat4(mat, 1, 0.0f, 1.0f, 0.0f,    y);
  set_row_mat4(mat, 2, 0.0f, 0.0f, 1.0f,    z);
  set_row_mat4(mat, 3, 0.0f, 0.0f, 0.0f, 1.0f);
};

void print_mat4(const Matrix4 mat){
  for(int y = 0;y < 4;y++) {
    printf("{");
    for(int x = 0;x < 4;x++) {
      printf("[%f]", mat.values[x + y * 4]);
    }
    printf("}\n");
  }
};
