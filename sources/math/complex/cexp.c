/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex cexp(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	double x = c.x[0];
	double y = c.x[1];
	double r;

	r = exp(x);
	return r * cos(y) + r * sin(y) * I;
}
