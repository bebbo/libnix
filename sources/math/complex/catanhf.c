/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

float complex catanhf(float complex z) {
	return -I * catanf(z * I);
}
