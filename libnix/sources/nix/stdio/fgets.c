#include <stdio.h>

char *fgets(char *s,int n,FILE *stream)
{
  int c;
  char *s2=s;
  while(--n)
  {
    c=fgetc(stream);
    if(c==EOF)
    {
      if(s2==s)
        return NULL;
      break;
    }
    *s2++=c;
    if(c=='\n')
      break;
  }
  *s2++='\0';
  return s;
}
