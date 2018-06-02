#include <stdio.h>
#include "stabs.h"

extern void exit(int);
extern void free(void*);

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

struct _reent
{
  int _errno;			/* local copy of errno */
  FILE *_stdin, *_stdout, *_stderr;	/* XXX */
} errno;


FILE **__sF=&errno._stdin; /* stdin, stdout, stderr */

void __initstdfio(void)
{ FILE **f=__sF, *err;

  if(((*f++=fdopen(STDIN_FILENO,"r"))==NULL)||
     ((*f++=fdopen(STDOUT_FILENO,"w"))==NULL)||
     ((*f=err=fdopen(STDERR_FILENO,"w"))==NULL))
    exit(20);
  free(err->buffer);
  err->flags&=~(__SMBF|__SLBF); err->flags|=__SNBF;
  err->buffer=NULL;
}

/* Call our private constructor */
ADD2INIT(__initstdfio,-20);
