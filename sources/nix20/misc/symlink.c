#include <proto/dos.h>
#include <unistd.h>

int symlink(const char *from, const char *to) {
	return DOSTRUE != MakeLink((STRPTR )to, (LONG )from, LINK_SOFT);
}
