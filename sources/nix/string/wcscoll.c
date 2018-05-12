#include <wchar.h>

int wcscoll(const wchar_t *a, const wchar_t *b) {
	return wcscmp(a, b);
}
