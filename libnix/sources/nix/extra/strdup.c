#include <string.h>
#include <stdlib.h>
#include <strsup.h>

char *strdup(const char *s)
{
  char *s1;

  if ((s1=malloc(strlen_plus_one(s))))
    strcpy(s1,s);
  return s1;
}
