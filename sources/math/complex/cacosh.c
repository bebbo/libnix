/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

double complex cacosh(double complex z) {
	return clog(z + csqrt(z + 1) * csqrt(z - 1));
}
