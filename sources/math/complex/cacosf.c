/*
 * This code is derived from software written by Stephen L. Moshier.
 */

#include <complex.h>
#include <math.h>

float complex
cacosf(float complex z)
{
	float complex w = casinf(z);

	union C {
		float complex c;
		float x[2];
	} c = { .c = w};
	float x = c.x[0];
	float y = c.x[1];

	w = ((float)M_PI_2 - x) - y * I;
	return w;
}
