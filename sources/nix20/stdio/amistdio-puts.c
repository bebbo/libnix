#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

int amiputs(char const *s) {
	BPTR f = Output();
	ULONG l = strlen(s);
	FPuts(f, s);
	FPuts(f, "\n");
	return l + 1;
}
