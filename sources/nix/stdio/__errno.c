#include "stdio.h"

struct _reent
{
  int _errno;			/* local copy of errno */
#ifndef __posix_threads__
  FILE *_stdin, *_stdout, *_stderr;	/* XXX */
#endif
}
#ifdef __posix_threads__
__thread
#endif
errno;
