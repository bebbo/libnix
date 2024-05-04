#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

#define __libnix__ 1
#include "stabs.h"

#pragma GCC push_options
#pragma GCC optimize ("-O2")

register long * __sp asm("sp");

void __markstack() {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
	struct Task * task = SysBase->ThisTask;

	long * p = (long *)task->tc_SPLower;
	while (p < __sp) {
		*p = 0xDEADBEEF ^ (long)p;
		++p;
	}
}

__entrypoint
static void pc(char c asm("d0"), char * to asm("a3")) {
	asm volatile("move.b d0,(a3)+");
}

void __checkstack() {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
	struct Process * process = (struct Process *) SysBase->ThisTask;

	long * p = (long *)process->pr_Task.tc_SPLower;
	while (p < __sp) {
		if (*p != (0xDEADBEEF ^ (long)p))
			break;
		++p;
	}
	--p;

	struct DOSBase * DOSBase = (struct DOSBase *)OldOpenLibrary((UBYTE*)"dos.library");
	UBYTE buf[32];
	long sz = ((char *)process->pr_Task.tc_SPUpper - (char *)p);
	RawDoFmt((CONST_STRPTR)"used stack %ld\r\n", &sz, (VOID (*)())pc, buf);
	Write(process->pr_COS, buf, strlen(buf));
	CloseLibrary((struct Library *)DOSBase);
}

ADD2INIT(__markstack, -69);
ADD2EXIT(__checkstack, -69);
