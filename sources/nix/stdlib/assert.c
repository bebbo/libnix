/*
 FUNCTION
 <<assert>>---macro for debugging diagnostics

 INDEX
 assert

 SYNOPSIS
 #include <assert.h>
 void assert(int <[expression]>);

 DESCRIPTION
 Use this macro to embed debuggging diagnostic statements in
 your programs.  The argument <[expression]> should be an
 expression which evaluates to true (nonzero) when your program
 is working as you intended.

 When <[expression]> evaluates to false (zero), <<assert>>
 calls <<abort>>, after first printing a message showing what
 failed and where:

 . Assertion failed: <[expression]>, file <[filename]>, line <[lineno]>, function: <[func]>

 If the name of the current function is not known (for example,
 when using a C89 compiler that does not understand __func__),
 the function location is omitted.

 The macro is defined to permit you to turn off all uses of
 <<assert>> at compile time by defining <<NDEBUG>> as a
 preprocessor variable.   If you do this, the <<assert>> macro
 expands to

 . (void(0))

 RETURNS
 <<assert>> does not return a value.

 PORTABILITY
 The <<assert>> macro is required by ANSI, as is the behavior
 when <<NDEBUG>> is defined.

 Supporting OS subroutines required (only if enabled): <<close>>, <<fstat>>,
 <<getpid>>, <<isatty>>, <<kill>>, <<lseek>>, <<read>>, <<sbrk>>, <<write>>.
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "proto/dos.h"

#ifndef HAVE_ASSERT_FUNC

static void myputs(char const * txt, BPTR out) {
	int len = strlen(txt);
	if (len != 0)
		Write(out, (APTR)txt, len);
}

/* func can be NULL, in which case no function information is given.  */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr) {
	BPTR out = Output();

	char buf[16];
	myputs("assertion \"", out);
	myputs(failedexpr, out);
	myputs("\" failed: file \"", out);
	myputs(file, out);
	myputs("\", line ", out);
	utoa(line, buf, 10);
	myputs(buf, out);
	if (func) {
		myputs(", function: ", out);
		myputs(func, out);
	}
	myputs("\n", out);

	abort();
	/* NOTREACHED */
}
#endif /* HAVE_ASSERT_FUNC */

void __assert(const char *file, int line, const char *failedexpr) {
	__assert_func(file, line, NULL, failedexpr);
	/* NOTREACHED */
}
