#include <string.h>
#include <proto/utility.h>

asm("_strncasecmp: .global _strncasecmp");
int strnicmp(const char *s1,const char *s2,size_t len)
{
  return Strnicmp((STRPTR)s1,(STRPTR)s2,(LONG)len);
}
