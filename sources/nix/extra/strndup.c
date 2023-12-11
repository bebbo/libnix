#include <stdlib.h>
#include <string.h>

char* strndup(const char *s, size_t n) {
	int l = strlen_plus_one(s);
	if (++n < l)
		l = n;
	char *s1 = malloc(l);
	if (s1) {
		--l;
		memcpy(s1, s, l);
		s1[l] = 0;
	}
	return s1;
}
