#define __NO_INLINE__
#include <string.h>
__stdargs size_t strlen_plus_one(const char *string) {
	const char *s = string;

	while (*s++) {
	}
	return (s - string);
}
