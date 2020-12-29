#include <stdlib.h>
#include <errno.h>
#include <wchar.h>
#include "stdio.h"

int __fflush(FILE *stream);

#ifdef __posix_threads__
static wint_t __ungetwc2(wint_t c, FILE * stream);
#endif
wint_t ungetwc(wint_t c,FILE *stream) {
#ifdef __posix_threads__
	wint_t r;
	__STDIO_LOCK(stream);
	r = __ungetwc2(c, stream);
	__STDIO_UNLOCK(stream);
	return r;
}
static wint_t __ungetwc2(wint_t c, FILE *stream) {
#endif
	size_t i;
	wint_t cc;

	if (c == (wint_t)EOF)
		return EOF;
	if (stream->_flags & __SERR)/* Error on stream */
	{
		errno = EPERM;
		return EOF;
	}
	if (stream->_flags & __SWR) /* File is in write mode */
		if (__fflush(stream)) /* write buffer */
			return EOF;
	if (stream->tmpp == NULL) {
		if (stream->_flags & __SRD) /* File is in read mode */
		{
			stream->tmpp = stream->_p; /* store actual position */
			stream->tmpinc = stream->_r;
			stream->_p = &stream->unget[4]; /* and use other buffer */
			stream->_r = 0;
		} else /* File is in indeterminated state */
		{
			stream->tmpp = (unsigned char *) 2; /* Dummy */
			stream->tmpinc = 0;
			stream->_p = &stream->unget[4]; /* use other buffer */
			stream->_r = 0;
			stream->_flags |= __SRD;
		}
	}
	if ((wint_t)stream->_r >= 4 + 1 - sizeof(wint_t)) /* ungetc buffer overflow */
		return EOF;
	stream->_r += sizeof(wint_t);

	cc = c;
	for (i = 0; i < sizeof(wint_t); ++i) {
		*--stream->_p = cc;
		cc >>= 8;
	}

	return c;
}
