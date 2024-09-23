/**
 * copilot suggests:
 */

#include <complex.h>

float complex ctanf(float complex z) {
	float complex iz = I * z;
	float complex ciz = cexpf(iz);
	float complex cmiz = cexpf(-iz);
	float complex num = ciz - cmiz;
	float complex den = (ciz + cmiz) * I;
	return num / den;
}
