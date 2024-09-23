/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

float crealf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	return c.x[0];
}
