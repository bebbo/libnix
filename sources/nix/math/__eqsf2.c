#include <proto/mathieeesingbas.h>

asm("___eqsf2: .global ___eqsf2");
asm("___nesf2: .global ___nesf2");
asm("___ltsf2: .global ___ltsf2");
asm("___lesf2: .global ___lesf2");
asm("___gtsf2: .global ___gtsf2");
asm("___gesf2: .global ___gesf2");
signed long __cmpsf2(float x,float y)
{ return IEEESPCmp(x,y); }
