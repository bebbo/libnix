#include <proto/mathieeedoubbas.h>

asm("___eqdf2: .global ___eqdf2");
asm("___nedf2: .global ___nedf2");
asm("___ltdf2: .global ___ltdf2");
asm("___ledf2: .global ___ledf2");
asm("___gtdf2: .global ___gtdf2");
asm("___gedf2: .global ___gedf2");
signed long __cmpdf2(double x,double y)
{ return IEEEDPCmp(x,y); }
