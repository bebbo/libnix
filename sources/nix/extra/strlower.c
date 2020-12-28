#include <ctype.h>

asm("_strlwr: .global _strlwr");
char *strlower(char *s)
{ unsigned char *s1;

  s1=(unsigned char *)s;
  while(*s1) {
    if (isupper(*s1))
      *s1+='a'-'A';
    ++s1;
  }
  return s;
}
