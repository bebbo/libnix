/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex cprojf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	float x = c.x[0];
	float y = c.x[1];

	if (isinff(x) || isinff(y))
		return INFINITY + 0*I;

	return z;
}
