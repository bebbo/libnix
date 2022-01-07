#include <complex.h>
#include <math.h>

double complex cexp(double complex z) {
	double y = cimag(z);
	double r = exp(creal(z));
	return r * cos(y) + r * sin(y) * I;
}
