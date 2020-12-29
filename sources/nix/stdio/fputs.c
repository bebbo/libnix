#include "stdio.h"

int fputs(const char *s, FILE *stream) {
	__STDIO_LOCK(stream);
	while (*s) {
		if (fputc(*s++, stream) == EOF) {
			__STDIO_UNLOCK(stream);
			return EOF;
		}
	}
	__STDIO_UNLOCK(stream);
	return 0;
}
