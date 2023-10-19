#include <proto/dos.h>
#include <unistd.h>

asm("_link: .global _link");
int symlink(const char *from, const char *to) {
	return DOSTRUE != MakeLink((STRPTR )to, (LONG )from, LINK_SOFT);
}
