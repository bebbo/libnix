#include <stdlib.h>
#include "stdio.h"

long atol(const char *nptr)
{ return strtol(nptr,NULL,10); }
