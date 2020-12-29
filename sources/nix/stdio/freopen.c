#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <proto/dos.h>

/**
 * Reopen a file.
 *
 * @return file stream.
 */
extern int __fclose(FILE *);

extern StdFileDes **__stdfiledes;

FILE *freopen(const char *filename, const char *mode, FILE *stream) {
	__STDIO_LOCK(stream);

	int error = __fclose(stream);
	if (error) {
		__STDIO_UNLOCK(stream);
		return NULL;
	}

	if (filename != NULL) {
		char ch;
		long file, flags;
		if (mode == NULL) {
			__STDIO_UNLOCK(stream);
			return NULL;
		}

		ch = *mode++;
		switch (ch) {
			case 'r':
				flags = O_RDONLY;
				break;
			case 'w':
				flags = O_WRONLY | O_CREAT | O_TRUNC;
				break;
			case 'a':
				flags = O_WRONLY | O_CREAT | O_APPEND;
				break;
			default:
				__STDIO_UNLOCK(stream);
				return NULL;
		}

		ch = *mode++;
		if (ch == 't' || ch == 'b') // ignore for compatibility
			ch = *mode++;

		if (ch == '+')
			flags = (flags & ~O_ACCMODE) | O_RDWR;

		if ((file = open(filename, flags, 0777)) < 0) {
			__STDIO_UNLOCK(stream);
			return NULL;
		}

		if (flags & O_APPEND)
			Seek(__stdfiledes[stream->file]->lx_fh, 0, OFFSET_END);

		/* clear a lot of flags */
		stream->_flags &= ~(__SWO | __SERR | __SEOF | __SWR | __SRD | __SNBF | __SLBF);
		if (flags & O_WRONLY)
			stream->_flags |= __SWO; /* set write-only flag */
		if (isatty(file))
			stream->_flags |= __SLBF; /* set linebuffered flag */
		stream->file = file;
	}

	__STDIO_UNLOCK(stream);
	return stream;
}
