#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

__stdargs char* concat(const char *s0, ...) {
	int sz = 1 + strlen(s0);
	va_list args;
	va_start(args, s0);
	for(;;) {
		char const *s = va_arg(args, char const*);
		if (!s)
			break;
		sz += strlen(s);
	}
	va_end(args);
	char * r = (char *)malloc(sz);
	if (r) {
		char * q = r;
		va_start(args, s0);
		while ((*q = *s0++)) {
			++q;
		}
		for(;;) {
			char const *s = va_arg(args, char const*);
			if (!s)
				break;
			while ((*q = *s++)) {
				++q;
			}
		}
		va_end(args);
	}
	return r;
}
