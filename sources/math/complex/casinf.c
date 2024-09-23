/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex casinf(float complex z) {
	return -I * clogf(I * z + csqrtf(1 - z * z));
}
