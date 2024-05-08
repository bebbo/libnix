#include "bases.h"
#include "stabs.h"

#if defined(mc68020) || defined(mc68030) || defined(mc68040) || defined(mc68060) || defined(mc68080)

asm(
"	.text;"
"	.even;"

"	.globl	___fpucheck;"
"___fpucheck:;"
"	move.l	#0x68020,d1;"
"	movel	"A4(_SysBase)",a1;"
"	movew	a1@(0x128:W),d0;"
"	btst	#1,d0;"
"	jeq	error;"
"	move.l	#0x68881,d1;"
"	btst	#4,d0;"
"	jeq	error;"
);

// init rounding
asm("fmove.l fpcr,d0");
asm("and.w #65487,d0");
asm("fmove.l d0,fpcr");

asm(
"	rts;"
"error:"

"   move.l  a1,a6;"
"	move.l	d1,d7;"
"   jsr -0x6c(a6);"
"	pea	20:W;"
"	jsr	_exit;"		/* dito */
);

ADD2INIT(__fpucheck,-80); /* Highest priority */

#else

void __fpucheck(){}

#endif
