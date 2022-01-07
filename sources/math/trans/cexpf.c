#include <complex.h>
#include <math.h>

float complex cexpf(float complex z) {
	float y = cimagf(z);
	float r = expf(crealf(z));
	return r * cosf(y) + r * sinf(y) * I;
}
