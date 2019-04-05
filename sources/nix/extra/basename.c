#include <proto/dos.h>

char *basename(char *path) {
	if (!path || !*path)
		return ".";

	char *p = path;
	while (*p) {
		++p;
	}
	while (--p > path && *p == '/') {
		*p = 0;
	}
	p = (char *)FilePart((CONST_STRPTR)path);
	if (!*p)
		return "/";
	return p;
}
