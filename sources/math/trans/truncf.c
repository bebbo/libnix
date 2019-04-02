#include <proto/mathieeesingbas.h>

float truncf(float x) {
	union _d_bits {
		float f;
		struct {
			unsigned sign :1;
			unsigned exp :8;
			unsigned frac :23;
		} b;
		unsigned u;
	} f;
	f.f = x;
	if (f.b.sign)
		return IEEESPCeil(x);
	return IEEESPFloor(x);
}
