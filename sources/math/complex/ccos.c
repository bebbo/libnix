/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex ccos(double complex z) {
	double complex iz = I * z;
	return (cexp(iz) + cexp(-iz)) / 2;
}
