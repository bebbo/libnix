#include <limits.h>
#include <math.h>

long long llround(double x) {
	union {
		double d;
		short s;
	} u = {x};

	if (u.s < 0)
		x -= 0.5;
	else
		x += 0.5;

	return x;
}
