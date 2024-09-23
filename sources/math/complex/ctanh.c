/**
 * copilot suggests:
 */

#include <complex.h>

double complex ctanh(double complex z) {
	double complex cz = cexp(z);
	double complex cmz = cexp(-z);
	double complex num = cz - cmz;
	double complex den = cz + cmz;
	return num / den;
}
