#ifndef _MATRIX_H_
#define _MATRIX_H_

// Note(ville): Matrices should be made row major, ie. left to right, top to bottom (in that order)

typedef struct {
  float values[16];
} Matrix4;

extern void clear_mat4(Matrix4* mat, float def_value);
extern void identity_mat4(Matrix4* mat);
extern Matrix4 multiply_mat4(const Matrix4 a, const Matrix4 b);

extern void set_row_mat4(Matrix4* mat, int row, float v0, float v1, float v2, float v3);
extern void set_column_mat4(Matrix4* mat, int column, float v0, float v1, float v2, float v3);

extern void set_ortho_mat4(Matrix4* mat, float left, float top, float right, float bottom);
extern void set_scale_mat4(Matrix4* mat, float x, float y, float z);
extern void set_translate_mat4(Matrix4* mat, float x, float y, float z);

extern void print_mat4(const Matrix4 mat);

#endif
