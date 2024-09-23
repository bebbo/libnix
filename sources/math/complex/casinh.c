/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

double complex casinh(double complex z) {
	return -I * casin(z * I);
}
