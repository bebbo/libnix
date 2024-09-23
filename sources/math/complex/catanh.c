/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

double complex catanh(double complex z) {
	return -I * catan(z * I);
}
