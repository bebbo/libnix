#include <stdlib.h>

static unsigned int a=1;

int rand(void)
#if (RAND_MAX==0x7fffffff)
{ return (a=a*1103515245+12345)&RAND_MAX; }
#else
{ return (a=a*1103515245+12345)%RAND_MAX; }
#endif

void srand(unsigned int seed)
{ a=seed; }
