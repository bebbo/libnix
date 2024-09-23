#include <complex.h>

double cimag(double complex z) {
	union C {
		double complex c;
		double x[2];
	};
	union C c = { .c = z };
	return c.x[1];
}
