#include <wchar.h>
wchar_t *
wmemchr(const wchar_t * s, wchar_t c, size_t n) {
	size_t i;

	for (i = 0; i < n; ++i) {
		if (*s == c) {
			return (wchar_t *) s;
		}
		++s;
	}
	return 0;
}
