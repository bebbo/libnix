#include <wchar.h>

wchar_t *wcschr(const wchar_t *s,int c)
{
  while (*s!=(wchar_t)c)
    if (!*s++)
      { s = (wchar_t *)0; break; }
  return (char *)s;
}
