/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex cproj(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	double x = c.x[0];
	double y = c.x[1];

	if (isinf(x) || isinf(y))
		return INFINITY + 0*I;

	return z;
}
