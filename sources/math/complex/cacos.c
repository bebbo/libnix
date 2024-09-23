/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>
#include <math.h>

double complex cacos(double complex z) {
	double complex w = casin(z);

	union C {
		double complex c;
		double x[2];
	} c = { .c = w};
	double x = c.x[0];
	double y = c.x[1];

	return (M_PI_2 - x) - y * I;
}
