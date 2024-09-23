/*
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex catanf(float complex z) {
	float complex iz = I * z;
	return 0.5 * I * (clogf(1 - iz) - clogf(1 + iz));
}
