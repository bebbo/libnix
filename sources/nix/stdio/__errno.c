#include "stdio.h"

struct _reent
{
  int _errno;			/* local copy of errno */
  FILE *_stdin, *_stdout, *_stderr;	/* XXX */
}
#ifdef __posix_threads__
__thread
#endif
errno;
