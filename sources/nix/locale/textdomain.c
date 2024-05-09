#include <libintl.h>

static char * __domain;
char * textdomain (const char * domainname) {
	return __domain = (char *)domainname;
}
