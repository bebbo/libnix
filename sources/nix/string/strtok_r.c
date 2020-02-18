#include <string.h>

char *strtok_r(char *s1, const char *s2, char **s3)
{ static char *t;
  if (s1 == NULL)
    s1=*s3;
  s1+=strspn(s1,s2);
  if(*s1=='\0')
    return (char *)0;
  t=s1;
  s1+=strcspn(s1,s2);
  if (*s1!='\0')
    *s1++='\0';
  *s3 = s1;
  return t;
}