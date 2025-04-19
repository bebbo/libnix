#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

static char __printf_default_buffer[80];
static int bsz = sizeof(__printf_default_buffer);
static char *buffer = __printf_default_buffer;

void __freeBuff() {
	if (buffer && buffer != __printf_default_buffer) {
		FreeVec(buffer);
		buffer = 0;
	}
}

void setPrintfBufferSize(int sz) {
	char * p = (char*) AllocVec(sz, MEMF_PUBLIC);
	if (p) {
		__freeBuff();
		buffer = p;
		bsz = sz;
	}
}

ADD2EXIT(__freeBuff, -42);

// the callback per character, checks for end of buffer!
void __amiputs_putchar_callback(register char *ptr asm("a3")) {
	asm volatile("cmp.b #-1,(a3)");
	asm volatile("bne.s __Skip");
	asm volatile("move.b d0,(a3)+");
	asm volatile("__Skip:");
}

int amivsnprintf(char * buff, int sz, const char *fmt, va_list args) {
	memset(buff, 0xff, sz - 1);
	buff[sz - 1] = 0;
	RawDoFmt(fmt, args, __amiputs_putchar_callback, buff);
	return strlen(buff);
}

int amivfprintf(BPTR f, const char *fmt, va_list args) {
	int r;
	for(;;) {
		r = amivsnprintf(buffer, bsz, fmt, args);
		if (r + 1 < bsz) // reached end of buffer?
			break;
		int obsz = bsz; // try to resize
		setPrintfBufferSize(bsz * 3);
		if (obsz == bsz)
			break; // resize failed
		// print again with longer buffer
	}
	FPuts(f, buffer);
	if (strchr(buffer, '\n'))
		Flush(f);
	return r;
}

int amisnprintf(char * to, int sz, char const *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int retval = amivsnprintf(to, sz, fmt, args);
	va_end(args);
	return retval;
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
