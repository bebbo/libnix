#include <stdio.h>
#include <errno.h>

int __swbuf(int c, FILE *stream) /* Get next output block */
{
	int out, lbs;

	if (stream->_flags & (__SSTR | __SERR)) /* sprintf buffer | error on stream */
	{
		stream->_w = 0;
		errno = EPERM;
		return EOF;
	} else if (stream->_flags & __SRD) {
		stream->_r = 0; /* throw away input buffer */
		stream->tmpp = NULL;
		stream->_flags &= ~__SRD;
	}
	lbs = stream->_flags & __SLBF ? -stream->_bf._size : 0;
	out = (stream->_flags & __SNBF ? 0 : stream->_bf._size - 1) + lbs;
	if (!(stream->_flags & __SWR)) /* File wasn't in write mode */
	{
		stream->_p = stream->_bf._base; /* set buffer */
		stream->_w = --out; /* and buffercount */
		stream->_flags |= __SWR;
	} /* and write mode */
	*stream->_p++ = c; /* put this character */
	if (stream->_w < 0 && (stream->_w < lbs || (char) c == '\n')) {
		if (__fflush(stream)) /* Buffer full */
			return EOF;
		stream->_p = stream->_bf._base; /* Set new buffer */
	}
	stream->linebufsize = lbs;
	stream->_w = out;
	stream->_flags |= __SWR;
	return c;
}
