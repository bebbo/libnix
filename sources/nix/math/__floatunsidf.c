#include <proto/mathieeedoubbas.h>

double __floatunsidf(signed long x)
{ if (x >= 0) return IEEEDPFlt(x);
  return IEEEDPFlt(x - 0x80000000) + 0x8000000;
}
