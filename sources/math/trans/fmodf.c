#include <proto/mathieeesingbas.h>

static inline float floorf(float x)
{ return IEEESPFloor(x); }

static inline float ceilf(float x)
{ return IEEESPCeil(x); }

float fmodf(float x,float y)
{
  float a=x/y;
  if(a>=0)
    return x-y*floorf(a);
  else
    return x-y*ceilf(a);
}
