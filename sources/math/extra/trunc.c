#include <math.h>

double trunc  (     double x) {
	union _d_bits {
		double d;
		struct {
			unsigned sign :1;
			unsigned exp :11;
			unsigned frac0 :20;
			unsigned frac1 :32;
		};
	} d;
	d.d = x;

	if (d.sign)
		return ceil(x);

	return floor(x);
}
