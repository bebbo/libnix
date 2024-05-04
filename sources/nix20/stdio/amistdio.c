#include "amistdio.h"
#include <stdarg.h>
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

int amiputs(char const *s) {
	BPTR f = Output();
	FPuts(f, s);
	return FPuts(f, "\r\n");
}

void amiputchar(char c) {
	Write(Output(), &c, 1);
}

static int bsz = 128;
static char *buffer;
static char *end;
static char *last;

void __initBuff() {
	bsz += bsz;
	free(buffer);
	buffer = (char*) malloc(bsz);
	end = bsz + buffer;
}
ADD2INIT(__initBuff, -42);

__saveds
static void pc(register char *ptr asm("a3")) {
	if (ptr >= end)
		return;
	last = ptr;
	asm volatile("move.b d0,(a3)+");
}

int amiprintf(char const *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int retval = amivfprintf(Output(), fmt, args);
	va_end(args);
	return retval;
}

int amifprintf(BPTR f, char const *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int retval = amivfprintf(f, fmt, args);
	va_end(args);
	return retval;
}

int amivfprintf(BPTR f, const char *fmt, va_list args) {
	for (;;) {
		RawDoFmt(fmt, args, pc, buffer);
		if (last < end)
			break;
		__initBuff();
	}
	FPuts(f, buffer);
	return last - buffer;
}

BPTR amistderr() {
	struct Process * p = (struct Process *)SysBase->ThisTask;
	return p->pr_CES ? p->pr_CES : Output();
}
