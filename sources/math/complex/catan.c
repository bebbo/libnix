/*
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex catan(double complex z) {
	double complex iz = I * z;
	return 0.5 * I * (clog(1 - iz) - clog(1 + iz));
}
