#include <stdlib.h>
lldiv_t lldiv(long long num, long long denom) {
	lldiv_t r;

	r.quot = num / denom;
	r.rem = num % denom;
	if (num >= 0 && r.rem < 0) {
		++r.quot;
		r.rem -= denom;
	} else if (num < 0 && r.rem > 0) {
		--r.quot;
		r.rem += denom;
	}
	return r;
}
