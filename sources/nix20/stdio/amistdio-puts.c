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
	Write(f, s, l);
	Write(f, "\r\n", 2);
	return l + 2;
}
