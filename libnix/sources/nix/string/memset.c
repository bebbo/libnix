#include <string.h>

void *memset(void *s,int c,size_t n)
{ 
  if (n) {
    unsigned char *p=s;
    do;while(*p++=c,--n);
  }
  return s;
}
