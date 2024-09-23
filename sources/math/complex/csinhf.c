/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex csinhf(float complex z) {
	return (cexpf(z) - cexpf(-z)) / 2;
}
