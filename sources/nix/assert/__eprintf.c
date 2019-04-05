#include <stdlib.h>
#include "stdio.h"

__stdargs void __eprintf(const char* format, const char* file, unsigned line, const char *expr) {
	fprintf(stderr, format, file, line, expr);
	abort();
}
