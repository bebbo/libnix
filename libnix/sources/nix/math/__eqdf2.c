#include <proto/mathieeedoubbas.h>
#include "stabs.h"

signed long __eqdf2(double x,double y)
{ return IEEEDPCmp(x,y); }

ALIAS(__gedf2,__eqdf2);
ALIAS(__nedf2,__eqdf2);
ALIAS(__gtdf2,__eqdf2);
ALIAS(__ltdf2,__eqdf2);
ALIAS(__ledf2,__eqdf2);
