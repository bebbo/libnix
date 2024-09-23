/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex ccoshf(float complex z) {
	return (cexpf(z) + cexpf(-z)) / 2;
}
