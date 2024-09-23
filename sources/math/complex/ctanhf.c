/**
 * copilot suggests:
 */

#include <complex.h>

float complex ctanhf(float complex z) {
	float complex cz = cexp(z);
	float complex cmz = cexp(-z);
	float complex num = cz - cmz;
	float complex den = cz + cmz;
	return num / den;
}
