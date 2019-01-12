#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdlib.h>

typedef struct {
  int length;
  int allocated;
  int data_size;
  void* data;
} Array;

Array makearray(int length, int size) {
  Array arr;
  arr.length = 0;
  arr.allocated = length;
  arr.data_size = size;
  arr.data = calloc(length, size);
  return arr;
};

int pusharray(Array* to, void* value) {
  if(to->length + 1 >= to->allocated) {
    to->data = realloc(to->data, (to->allocated + 10) * to->data_size);
    to->allocated += 10;
  }
  memcpy(to->data + (to->data_size * to->length++), value, to->data_size);
  return 0;
};

void resizetofitarray(Array* arr) {
  arr->data = realloc(arr->data, arr->length * arr->data_size);
  arr->allocated = arr->length;
}

int getarray(Array* from, void** values) {
  *values = from->data;
  return from->length;
};

void memswap(char* a, char* b, int size) {
  for(int i = 0;i < size;i++) {
    *(a + i) = *(b + i);
  }
};

// Currently does not retain the insertation order
int removearray(Array* from, int index) {
  if(index < 0 || index >= from->length) {
    return -1;
  }

  memswap(((char*)from->data) + (index * from->data_size), ((char*)from->data) + ((from->length - 1) * from->data_size), from->data_size);
  from->length--;

  return 0;
}

#endif
