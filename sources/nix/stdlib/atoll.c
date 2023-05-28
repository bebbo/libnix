#include <stdlib.h>
#include "stdio.h"

long long atoll(const char *nptr)
{ return strtoll(nptr,NULL,10); }
