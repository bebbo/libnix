/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include <complex.h>
#include <math.h>

float cargf(float complex z) {
	union C {
		float complex c;
		float x[2];
	} c = { .c = z};
	float x = c.x[0];
	float y = c.x[1];

	return atan2f(y, x);
}
