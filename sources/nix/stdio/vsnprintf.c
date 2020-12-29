#include <stdarg.h>
#include "stdio.h"

extern int __vfprintf_total_size(FILE *stream, const char *fmt, va_list args);

int vsnprintf(char *s,size_t size,const char *format,va_list args) {
	size_t retval;
	FILE buffer;

	if (!s && size )
		return EOF;

	buffer._p=(unsigned char *)s;
	buffer._r=0;
	buffer._w=size-1;
	buffer._flags=__SSTR|__SWR;
	buffer.linebufsize=0;
#ifdef __posix_threads__
	buffer.__spinlock[0] = 0;
#endif
	retval=__vfprintf_total_size(&buffer,format,args);
	if (retval < size)
		s[retval] = 0;
	else if (size > 0)
		s[size - 1] = 0;
	return retval;
}
