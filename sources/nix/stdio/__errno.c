#include "stdio.h"

struct _reent
{
  int _errno;			/* local copy of errno */
  FILE *_stdin, *_stdout, *_stderr;	/* XXX */
} errno;
