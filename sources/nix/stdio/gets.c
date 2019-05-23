#define __NO_INLINE__
#include "stdio.h"
__stdargs char *gets(char *s) {
	return fgets(s, 0, stdin);
}
