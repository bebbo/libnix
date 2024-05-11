#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

int amigets(char *p, unsigned sz) {
	BPTR in = Input();
	*p = 0;
	STRPTR s = FGets(in, p, sz);
	if (!s)
		return 0;
	int l = strlen(s);
	while (l > 0 && (p[l-1] == '\n' || p[l-1] == '\r')) {
		p[--l] = 0;
	}
	return l;
}
