#include <stdlib.h>

static unsigned int a = 1;

int rand(void) {
	a = a * 1103515245 + 12345;
	a = (a >> 16 | a << 16);
#if (RAND_MAX==0x7fffffff)
	return a & RAND_MAX;
#else
	return a % RAND_MAX;
#endif
}

void srand(unsigned int seed) {
	a = seed;
}
