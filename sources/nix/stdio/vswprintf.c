#include <stdarg.h>
#include "stdio.h"
#include "wchar.h"

extern int __vwfprintf_total_size(FILE *stream, const wchar_t *fmt, va_list args);

int vswprintf(wchar_t *s,size_t size,const wchar_t *format,va_list args) {
	size_t retval;
	FILE buffer;

	if (!s && size )
		return EOF;

	buffer._p=(unsigned char *)s;
	buffer._r=0;
	buffer._w= (size * sizeof(wchar_t)) - 1;
	buffer._flags=__SSTR|__SWR;
	buffer.linebufsize=0;
#ifdef __posix_threads__
	buffer.__spinlock[0] = 0;
#endif
	retval = __vwfprintf_total_size(&buffer,format,args) / sizeof(wchar_t);
	if (retval < size)
		s[retval] = 0;
	else if (size > 0)
		s[size - 1] = 0;
	return retval;
}
