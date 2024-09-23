/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex conj(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	c.x[1] = -c.x[1];
	return c.c;
}
