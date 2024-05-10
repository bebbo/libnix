#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

BPTR amistderr() {
	struct Process * p = (struct Process *)SysBase->ThisTask;
	return p->pr_CES ? p->pr_CES : Output();
}
