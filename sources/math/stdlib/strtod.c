#include "stdio.h"

double strtod(const char *nptr,char **endptr)
{ double a;
  unsigned long n=0;
  sscanf(nptr,"%lf%ln",&a,&n);
  if(endptr)
    *endptr=(char *)nptr+n;
  return a;
}

float strtof(const char *nptr,char **endptr) {
	return (float)strtod(nptr, endptr);
}

long double strtold(const char *nptr,char **endptr) {
	return strtod(nptr, endptr);
}
