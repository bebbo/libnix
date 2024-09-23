#include <complex.h>

float cimagf(float complex z) {
	union C {
		float complex c;
		float x[2];
	};
	union C c = { .c = z };
	return c.x[1];
}
