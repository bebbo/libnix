#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

static int bsz = 128;
static char *buffer;
static char *end;
static char *last;

void __freeBuff() {
	if (buffer)
		FreeVec(buffer);
}
void __initBuff() {
	bsz += bsz;
	__freeBuff();
	buffer = (char*) AllocVec(bsz, MEMF_PUBLIC);
	if (buffer) {
		end = bsz + buffer;
	} else {
		end = buffer;
		exit(10);
	}
}
ADD2INIT(__initBuff, -42);
ADD2EXIT(__freeBuff, -42);

#ifdef __baserel__
// needed to set a4 in the callback function
static void * mya4;
#endif

// the callback per character, checks for end of buffer!
static void pc(register char *ptr asm("a3")) {
#ifdef __baserel__
	register void * a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("move.l %1,%0" : "=r"(a4) : "m"(mya4));
#endif
	if (ptr < end) {
		last = ptr;
		asm volatile("move.b d0,(a3)+");
	}
#ifdef __baserel__
	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
#endif
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
#ifdef __baserel__
	register void * a4 asm("a4");
	asm volatile("move.l %1,%0" : "=m"(mya4) : "r"(a4));
#endif
	for (;;) {
		RawDoFmt(fmt, args, pc, buffer);
		if (last < end)
			break;
		__initBuff();
	}
	FPuts(f, buffer);
	return last - buffer;
}

