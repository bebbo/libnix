#include <proto/dos.h>
#include <string.h>

char *dirname(char *path) {
	if (!path || !*path)
		return ".";

	char *p = path;
	while (*p) {
		++p;
	}
	while (--p > path && *p == '/') {
		*p = 0;
	}
	while (--p >= path && *p != '/') {
		*p = 0;
	}
	if (p > path && *p == '/')
		*p = 0;

	if (!*path || 0 == strcmp("..", path))
		return ".";

	return path;
}
