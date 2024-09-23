/**
 * copilot suggests:
 */

#include <complex.h>

double complex ctan(double complex z) {
	double complex iz = I * z;
	double complex ciz = cexp(iz);
	double complex cmiz = cexp(-iz);
	double complex num = ciz - cmiz;
	double complex den = (ciz + cmiz) * I;
	return num / den;
}
