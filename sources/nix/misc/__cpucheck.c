#include "bases.h"
#include "stabs.h"

#if defined(mc68020)
const char errtext1[]="Need a 68020 or higher CPU";

asm(
"              .text;"
"              .even;"

"              .globl     ___cpucheck;"
"___cpucheck:;"
"              movel   "A4(_SysBase)",a1;"
"              movew a1@(0x128:W),d0;"
"              lea          _errtext1,a0;"
"              btst        #1,d0;"
"              jeq         error;"
"              rts;"
"error:"
"              movel   a0,sp@-;"
"              jsr           ___myrequest;" /* jbsr translates to jra which doesn't work on 68000 */
"              pea        20:W;"
"              jsr           _exit;"                  /* dito */


"              .globl     ___myrequest;"
"___myrequest:;"
//              if (((struct Process *) SysBase->ThisTask)->pr_WindowPtr != (APTR) -1L)         
"               move.l 4,a0;"
"               move.l (276,a0),a0;"
"               move.l (184,a0),d0;"
"               moveq #-1,d1;"
"               cmp.l d0,d1;"
"               jeq Ende;"             // -1, dont show requester
//              IntuitionBase=OpenLibrary((unsigned char*)"intuition.library",0);
"               move.l 4,a6;"
"               lea IntuitionName,a1;"        // libname
"               move.l #0,d0;"        // version
"               jsr a6@(-0x228:W);"   // -552 OpenLibrary
"               move.l d0,IntuitionBase;"        // IntuitionBase
//              if(IntuitionBase) 
"               tst.l d0;"            // ==NULL?
"               jeq Ende;"
//              AutoRequest(0, &body, 0, &ok, 0, 0, 640, 72);
"               move.l #0,a2;"          // ptext
"               lea ok,a3;"         // ntext
"               move.l #oktxt,12(a3);"  // "Ok"-Text
"               move.l #0,d0;"          // pflag
"               move.l #0,d1;"          // nflag
"               move.w #640,d2;"        // w
"               move.w #72,d3;"         // h
"               move.l #0,a0;"          // Window
"               lea body,a1;"           // body
"               move.l 4(a7),12(a1);"   // body-message from stack
"               move.l IntuitionBase,a6;"          // IntuitionBase
"               jsr a6@(-0x15c:W);\n"     // -348 Autorequest
//              CloseLibrary(IntuitionBase);
"               move.l 4,d0;\n"
"               move.l d0,a6;\n"
"               move.l IntuitionBase,a1;\n"          // IntuitionBase
"               jsr a6@(-0x19e:W);\n"     // -414 CloseLibrary

"Ende:;"
"               rts;"
"IntuitionName:;"
"               dc.b 'i','n','t','u','i','t','i','o','n','.','l','i','b','r','a','r','y',0;"
"               align;"

"IntuitionBase:;"
"               dc.l 1;"


"body:;"
"               dc.b    0,0;"              // ;colour
"               dc.b    0;"                // ;mode
"               align;"
"               dc.w    15,5;"             // ;text position
"               dc.l    0;"                // ;standard font
"               dc.l    0;"                // ;pointer to text
"               dc.l    0;"                // ;no more text

"ok:;"
"               dc.b    0,0;"              // ;colour
"               dc.b    0;"                // ;mode
"               align;"
"               dc.w    6,3;"              // ;text position
"               dc.l    0;"                // ;standard font
"               dc.l    0;"                // ;pointer to text
"               dc.l    0;"                // ;no more text

"oktxt:;"
"               dc.b    'O','k',0;"
"               align;"


);

ADD2INIT(__cpucheck,-80); /* Highest priority */

#else

void __cpucheck(){}

#endif

