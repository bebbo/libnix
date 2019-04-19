#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <proto/dos.h>

extern StdFileDes **__stdfiledes;
extern unsigned __stdfilesize;

StdFileDes *__allocfd(void);
extern void _setup_file(StdFileDes *fp);
/**
 * open a file
 *
 * @return the file descriptor.
 */
int open(const char *path, int flags, ...) {
	extern char *__amigapath(const char *path);
	StdFileDes *sfd;

#ifdef IXPATHS
	if((path=__amigapath(path))==NULL)
	return -1;
#endif

	if ((sfd = __allocfd())) {
		sfd->lx_oflags = flags;

		long mode = flags&O_TRUNC?MODE_NEWFILE: flags&O_CREAT?MODE_READWRITE:MODE_OLDFILE;
		if ((sfd->lx_fh = (int)Open((CONST_STRPTR)path, mode))) {
			_setup_file(sfd);
			return sfd->lx_pos;
		}
		__seterrno();
		sfd->lx_inuse = 0;
	}

	return -1;
}

/**
 * Reuse or allocate a StdFileDes object.
 */
StdFileDes *__allocfd(void) {
	StdFileDes *fp, **sfd;
	int file, max;

	for (sfd = __stdfiledes, max = __stdfilesize, file = 0; file < max; sfd++, file++)
		if (!sfd[0] || !sfd[0]->lx_inuse)
			break;

	if (file == SHRT_MAX) {
		errno = EMFILE;
		return NULL;
	}

	if (file == max) {
		if ((sfd = (StdFileDes **)realloc(__stdfiledes, (file + 1) * sizeof(fp))) == NULL) {
			errno = ENOMEM;
			return NULL;
		}
		__stdfiledes = sfd;
		__stdfilesize++;
		*(sfd = &sfd[file]) = 0;
	}

	if ((fp = sfd[0]) == NULL) {
		if ((sfd[0] = fp = (StdFileDes *)malloc(sizeof(*fp))) == NULL) {
			errno = ENOMEM;
			return NULL;
		}
		fp->lx_pos = file;
	}

	return fp;
}
