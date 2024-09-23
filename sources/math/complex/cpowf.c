#include <complex.h>

float complex cpowf(float complex z, float complex w) {
	return cexpf(w * clogf(z));
}
