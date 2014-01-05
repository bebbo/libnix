#include <proto/mathieeesingbas.h>
#include "stabs.h"

signed long __eqsf2(float x,float y)
{ return IEEESPCmp(x,y); }

ALIAS(__gesf2,__eqsf2);
ALIAS(__nesf2,__eqsf2);
ALIAS(__gtsf2,__eqsf2);
ALIAS(__ltsf2,__eqsf2);
ALIAS(__lesf2,__eqsf2);
