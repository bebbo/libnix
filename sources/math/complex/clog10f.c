/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex clog10f(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	float x = c.x[0];
	float y = c.x[1];

	float mod = sqrtf(x*x + y*y);
	float arg = atan2f(y, x);
	return log10f(mod) + I * arg;
}
