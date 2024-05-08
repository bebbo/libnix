#include <wchar.h>

wchar_t *wcschr(const wchar_t *s, wchar_t c)
{
  while (*s != c)
    if (!*s++)
      { s = (wchar_t *)0; break; }
  return (wchar_t *)s;
}
