#undef __NO_INLINE__
#define __NO_INLINE__
#include <proto/exec.h>
#include <string.h>

void *wmemcpy(void *s1,const void *s2,size_t n)
{
  CopyMem((APTR)s2,s1,n + n); return s1;
}
