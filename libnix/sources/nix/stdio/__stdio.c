#include <stdio.h>
#include <stabs.h>

static FILE *__files[3];

FILE **__sF=__files; /* stdin, stdout, stderr */

void __initstdfio(void)
{ FILE **f=__sF;

  if((*f++=fopen((char *)1,NULL))!=NULL)
    if((*f++=fopen((char *)2,NULL))!=NULL)
      if((*f=fopen((char *)3,NULL))!=NULL)
        return;
  exit(20);
}

/* Call our private constructor */
ADD2INIT(__initstdfio,-10);
