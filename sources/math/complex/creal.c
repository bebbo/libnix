/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double creal(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	return c.x[0];
}
