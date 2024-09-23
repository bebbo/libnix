/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include <complex.h>
#include <math.h>

double cabs(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	double x = c.x[0];
	double y = c.x[1];

	return hypot(x, y);
}
