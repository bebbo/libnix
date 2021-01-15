// errno moved to __stdio.c
#include "errno.h"
int *__errno (void) {
	return &errno;
}
