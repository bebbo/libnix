#include <string.h>
#include <proto/utility.h>

asm("_strcasecmp: .global _strcasecmp");
int stricmp(const char *s1,const char *s2)
{
  return Stricmp((STRPTR)s1,(STRPTR)s2);
}
