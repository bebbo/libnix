#include <stdio.h>

struct _reent
{
  int _errno;			/* local copy of errno */
  FILE *_stdin, *_stdout, *_stderr;	/* XXX */
} errno;

FILE **__sF=&errno._stdin; /* stdin, stdout, stderr */
