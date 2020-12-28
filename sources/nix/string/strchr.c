#include <string.h>

asm("_index: .global _index");
char *strchr(const char *s,int c)
{
  while (*s!=(char)c)
    if (!*s++)
      { s = (char *)0; break; }
  return (char *)s;
}
