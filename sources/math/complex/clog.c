/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex clog(double complex z) {
	union C {
		double complex c;
		double x[2];
	} c = { .c = z};
	double x = c.x[0];
	double y = c.x[1];

	double mod = sqrt(x*x + y*y);
	double arg = atan2(y, x);
	return log(mod) + I * arg;
}
