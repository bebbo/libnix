#include <complex.h>

double complex cpow(double complex z, double complex w) {
	return cexp(w * clog(z));
}
