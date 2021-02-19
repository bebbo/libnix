#include <ctype.h>

asm("_strupr: .global _strupr");
char *strupper(char *s)
{ unsigned char *s1;

  s1=(unsigned char *)s;
  while(*s1) {
    if (islower(*s1))
      *s1-='a'-'A';
    ++s1;
  }
  return s;
}
