#include <stdio.h>
#include <stdarg.h>

extern int __vfprintf_total_size(FILE *stream, const char *fmt, va_list args);

int vsnprintf(char *s,size_t size,const char *format,va_list args) {
	int retval;
	FILE buffer;

	if ((s == NULL && (int)size != 0) || (size < 0)) {
		return EOF;
	}

	buffer.p=s;
	buffer.incount=0;
	buffer.outcount=size-1;
	buffer.flags=__SSTR|__SWR;
	buffer.linebufsize=0;
	retval=__vfprintf_total_size(&buffer,format,args);
	s[size-1] = '\0';
	
	return retval;
}
