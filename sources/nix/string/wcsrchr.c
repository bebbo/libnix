#include <wchar.h>


wchar_t *wcsrchr(const wchar_t *s, wchar_t c)
{ wchar_t *c1=(wchar_t *)0;
  do
    if (*s == c)
      c1=(wchar_t *)s;
  while(*s++);
  return c1;
}
