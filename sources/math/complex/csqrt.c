/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex csqrt(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	double x = c.x[0];
	double y = c.x[1];
	double r = sqrt(x*x + y*y);
	double theta = atan2(y, x) / 2;
	return sqrt(r) * (cos(theta) + sin(theta) * I);
}
