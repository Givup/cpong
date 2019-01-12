#include "string.h"

String makestr(char* from) {
  int length = strlen(from);
  String str;
  str.length = length;
  str.allocated = length;
  str.str = (char*)malloc(length);
  strcpy(str.str, from);
  return str;
};

String allocstr(int allocAmount) {
  String str;
  str.length = 0;
  str.allocated = allocAmount;
  str.str = (char*)calloc(allocAmount, 1);
  return str;
}

int copystr(String* from, String* to) {
  if(from->length > to->allocated) return -1;
  int copied = 0;
  while(*(from->str + copied) != 0) {
    *(to->str + copied) = *(from->str + copied);
    copied++;
  }
  return copied;
};

int movestr(String* from, String* to) {
  to->str = from->str;
  to->length = from->length;
  to->allocated = from->allocated;
  from->str = NULL;
  from->length = 0;
  from->allocated = 0;
};
