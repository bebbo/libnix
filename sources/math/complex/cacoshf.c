/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

float complex cacoshf(float complex z) {
	return clogf(z + csqrtf(z + 1) * csqrtf(z - 1));
}
