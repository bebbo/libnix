#include <stdio.h>
#include <stdarg.h>

extern int __vfprintf_total_size(FILE *stream, const char *fmt, va_list args);

int vsnprintf(char *s,size_t size,const char *format,va_list args) {
	int retval;
	FILE buffer;

	if (!s && size )
		return EOF;

	buffer._p=(unsigned char *)s;
	buffer._r=0;
	buffer._w=size-1;
	buffer._flags=__SSTR|__SWR;
	buffer.linebufsize=0;
	retval=__vfprintf_total_size(&buffer,format,args);
	if (retval < size)
		s[retval] = 0;
	else if (size > 0)
		s[size - 1] = 0;
	return retval;
}
