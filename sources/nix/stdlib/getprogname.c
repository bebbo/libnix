#include <stdlib.h>
#include <proto/dos.h>

const char	* getprogname(void) {
	static char buf[512];
	GetProgramName(buf, 512);
	return buf;
}
