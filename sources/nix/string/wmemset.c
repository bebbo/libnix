#undef __NO_INLINE__
#define __NO_INLINE__
#include <proto/exec.h>
#include <string.h>

void *wmemset(void *s, int c, size_t n)
{
	return memset(s, c, n + n);
}
