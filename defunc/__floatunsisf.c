#include <proto/mathieeesingbas.h>

float __floatunsisf(signed long x)
{ if (x >= 0) return IEEESPFlt(x);
  return IEEESPFlt(x - 0x80000000) + 0x8000000;
}
