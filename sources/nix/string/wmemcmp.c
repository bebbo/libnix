#include <wchar.h>
int wmemcmp(const wchar_t * s1, const wchar_t * s2, size_t n) {
	unsigned i;

	for (i = 0; i < n; ++i) {
		if (*s1 != *s2)
			return *s1 > *s2 ? 1 : -1;
		++s1;
		++s2;
	}
	return 0;
}
