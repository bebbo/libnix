/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex ccosf(float complex z) {
	float complex iz = I * z;
	return (cexpf(iz) + cexpf(-iz)) / 2;
}
