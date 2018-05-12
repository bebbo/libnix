#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wchar.h>

wint_t ungetwc(wint_t c, FILE *stream) {
	if (c == EOF)
		return EOF;
	if (stream->flags & __SERR)/* Error on stream */
	{
		errno = EPERM;
		return EOF;
	}
	if (stream->flags & __SWR) /* File is in write mode */
		if (__fflush(stream)) /* write buffer */
			return EOF;
	if (stream->tmpp == NULL) {
		if (stream->flags & __SRD) /* File is in read mode */
		{
			stream->tmpp = stream->p; /* store actual position */
			stream->tmpinc = stream->incount;
			stream->p = &stream->unget[4]; /* and use other buffer */
			stream->incount = 0;
		} else /* File is in indeterminated state */
		{
			stream->tmpp = (unsigned char *) 2; /* Dummy */
			stream->tmpinc = 0;
			stream->p = &stream->unget[4]; /* use other buffer */
			stream->incount = 0;
			stream->flags |= __SRD;
		}
	}
	if (stream->incount >= 4 + 1 - sizeof(wint_t)) /* ungetc buffer overflow */
		return EOF;
	stream->incount += sizeof(wint_t);

	wint_t cc = c;
	for (int i = 0; i < sizeof(wint_t); ++i) {
		*--stream->p = cc;
		cc >>= 8;
	}

	return c;
}
