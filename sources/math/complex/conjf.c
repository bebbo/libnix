/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float complex conjf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	c.x[1] = -c.x[1];
	return c.c;
}
