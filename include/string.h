#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>

typedef struct {
  int length;
  int allocated;
  char* str;
} String;

extern String makestr(char* from);
extern String allocstr(int allocAmount);
extern int copystr(String* from, String* to);
extern int movestr(String* from, String* to);

#endif
