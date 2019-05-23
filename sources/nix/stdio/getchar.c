#define __NO_INLINE__
#include "stdio.h"
__stdargs int getchar() {
	return getc(stdin);
}
