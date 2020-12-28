#include <string.h>

asm("_rindex: .global _rindex");
char *strrchr(const char *s,int c)
{ char *c1=(char *)0;
  do
    if (*s==(char)c)
      c1=(char *)s;
  while(*s++);
  return c1;
}
