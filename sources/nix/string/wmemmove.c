#include <wchar.h>
wchar_t *
wmemmove(wchar_t * d, const wchar_t * s, size_t n) {
	return (wchar_t *) memmove(d, s, n * sizeof(wchar_t));
}
