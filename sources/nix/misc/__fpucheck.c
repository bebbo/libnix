#include "bases.h"
#include "stabs.h"

#if defined(mc68020)
const char errtext2[]="Need some FPU to run";

asm(
"              .text;"
"              .even;"

"              .globl     ___fpucheck;"
"___fpucheck:;"
"              movel   "A4(_SysBase)",a1;"
"              movew a1@(0x128:W),d0;"
"              lea          _errtext2,a0;"
"              btst        #4,d0;"
"              jeq         error;"
"              rts;"
"error:"
"              movel   a0,sp@-;"
"              jsr           ___myrequest;" /* jbsr translates to jra which doesn't work on 68000 */
"              pea        20:W;"
"              jsr           _exit;"               
);

ADD2INIT(__fpucheck,-80); /* Highest priority */

#else

void __fpucheck(){}

#endif
