#include "stdio.h"

char* fgets(char *s, int n, FILE *stream) {
	char *s2 = s;

	__STDIO_LOCK(stream);
	while (--n) {
		int c = getc(stream);
		if (c == EOF) {
			if (s2 == s) {
				__STDIO_UNLOCK(stream);
				return NULL;
			}
			break;
		}
		*s2++ = c;
		if (c == '\n')
			break;
	}
	*s2++ = '\0';
	__STDIO_UNLOCK(stream);
	return s;
}
