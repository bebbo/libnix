#include "bases.h"
#include "stabs.h"

#if defined(mc68020)

asm(
"	.text;"
"	.even;"

"	.globl	___fpucheck;"
"___fpucheck:;"
"	movel	"A4(_SysBase)",a1;"
"	movew	a1@(0x128:W),d0;"
"	btst	#4,d0;"
"	jeq	error;"
"	rts;"
"error:"

"   move.l  a1,a6;"
"	move.l	#0x68881,d7;"
"   jsr -0x6c(a6);"
"	pea	20:W;"
"	jsr	_exit;"		/* dito */
);

ADD2INIT(__fpucheck,-80); /* Highest priority */

#else

void __fpucheck(){}

#endif
