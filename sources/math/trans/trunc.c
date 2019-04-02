#include <proto/mathieeedoubbas.h>

double trunc(double x) {
	union _d_bits {
		double d;
		struct {
			unsigned sign :1;
			unsigned exp :11;
			unsigned frac0 :20;
			unsigned frac1 :32;
		} b;
		unsigned u;
	} d;
	d.d = x;
	if (d.b.sign)
		return IEEEDPCeil(x);
	return IEEEDPCeil(x);
}
