#include <stdlib.h>
#include "stdio.h"

int atoi(const char *nptr)
{ return strtol(nptr,NULL,10); }
