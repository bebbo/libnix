/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>

float complex casinhf(float complex z) {
	return -I * casinf(z * I);
}
