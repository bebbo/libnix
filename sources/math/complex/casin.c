/**
 * copilot suggests:
 */

#include <complex.h>
#include <math.h>

double complex casin(double complex z) {
	return -I * clog(I * z + csqrt(1 - z * z));
}
