/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex csqrtf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	float x = c.x[0];
	float y = c.x[1];
	float r = sqrtf(x*x + y*y);
	float theta = atan2f(y, x) / 2;
	return sqrtf(r) * (cosf(theta) + sinf(theta) * I);
}
