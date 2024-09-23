/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex csinh(double complex z) {
	return (cexp(z) - cexp(-z)) / 2;
}
