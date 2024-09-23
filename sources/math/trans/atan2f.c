#include <proto/mathieeesingtrans.h>

#define PI 3.14159265358979323846

static inline float atanf(float x)
{ return IEEESPAtan(x); }

float atan2f(float y,float x)
{ return x>=y?(x>=-y?      atanf(y/x):     -PI/2-atanf(x/y)):
              (x>=-y? PI/2-atanf(x/y):y>=0? PI  +atanf(y/x):
                                          -PI  +atanf(y/x));
}
