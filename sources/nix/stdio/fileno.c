#define __NO_INLINE__
#include "stdio.h"
__stdargs int fileno(FILE *file) {
	return file->file;
}

