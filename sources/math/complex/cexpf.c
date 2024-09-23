/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex cexpf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	float x = c.x[0];
	float y = c.x[1];	float r;

	x = crealf(z);
	y = cimagf(z);
	r = expf(x);
	return r * cosf(y) + r * sinf(y) * I;
}
