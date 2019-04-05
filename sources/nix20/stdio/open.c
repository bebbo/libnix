
#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "stabs.h"

struct filenode {
  struct MinNode node;
  FILE theFILE;
};

extern struct ExecBase * SysBase;

/*
 * SBF: I put all functions into this file which are linked anyway if stdio is used.
 */
extern int __fflush(FILE *);
extern void __seterrno(void);

// hack: errno is here seen as int, and it's defined as struct in __sf.c
// stdin, stdout, stderr are attached to errno.
FILE **__sF = (FILE **) (&errno + 1); /* stdin, stdout, stderr */

/*
 ** the internal storage
 */
StdFileDes **__stdfiledes;
unsigned __stdfilesize = 4;
/* The normal Amiga shell sets no process->pr_CES stream -
 * we use Open("*",MODE_NEWFILE) in this case
 */
static long stderrdes;

/*
 **
 */
static inline void _setup_file(StdFileDes *fp) {
	fp->lx_inuse = 1;
	if (IsInteractive(fp->lx_fh))
		fp->lx_flags = LX_FILE | LX_ATTY;
	else
		fp->lx_flags = LX_FILE;
	fp->lx_fx = 0;
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
		if ((sfd = realloc(__stdfiledes, (file + 1) * sizeof(fp))) == NULL) {
			errno = ENOMEM;
			return NULL;
		}
		__stdfiledes = sfd;
		__stdfilesize++;
		*(sfd = &sfd[file]) = 0;
	}

	if ((fp = sfd[0]) == NULL) {
		if ((sfd[0] = fp = malloc(sizeof(*fp))) == NULL) {
			errno = ENOMEM;
			return NULL;
		}
		fp->lx_pos = file;
	}

	return fp;
}

int isatty(int d) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	return sfd ? (sfd->lx_flags & LX_ATTY) : 0;
}

/*
 **
 */
int _lx_addflags(int d, int oflags) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	return sfd ? sfd->lx_oflags |= oflags : 0;
}

/**
 * convert fd to a StdFileDes
 */
StdFileDes *_lx_fhfromfd(int d) {
	if ((unsigned) d < __stdfilesize) {
		StdFileDes *sfd = __stdfiledes[d];
		if (sfd && sfd->lx_inuse)
			return sfd;
	}
	return NULL;
}

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
		if ((sfd->lx_fh = (int)Open((CONST_STRPTR)path, flags&O_TRUNC?MODE_NEWFILE: flags&(O_WRONLY|O_RDWR)?MODE_READWRITE:MODE_OLDFILE))) {
			_setup_file(sfd);
			return sfd->lx_pos;
		}
		__seterrno();
		sfd->lx_inuse = 0;
	}

	return -1;
}

/**
 * Open the file stream for the file descriptor.
 */
FILE *fdopen(int filedes,const char *mode)
{ extern int _lx_addflags(int,int);
  if (mode!=NULL)
  { struct filenode *node = (struct filenode *)calloc(1,sizeof(*node));
    if(node!=NULL)
    { if((node->theFILE._bf._base=(unsigned char *)malloc(BUFSIZ))!=NULL)
      { node->theFILE._bf._size=BUFSIZ;
        node->theFILE.file=filedes;
        node->theFILE._flags|=__SMBF; /* Buffer is malloc'ed */
        if(isatty(filedes))
          node->theFILE._flags|=__SLBF; /* set linebuffered flag */
        if(_lx_addflags(filedes,*mode=='a'?O_APPEND:0)&O_WRONLY)
          node->theFILE._flags|=__SWO; /* set write-only flag */
        AddHead((struct List *)&__filelist,(struct Node *)&node->node);
        return &node->theFILE;
      }
      else
        errno=ENOMEM;
      free(node);
    }
    else
      errno=ENOMEM;
  }
  return NULL;
}


/**
 * Reopen a file.
 *
 * @return file stream.
 */
FILE *freopen(const char *filename, const char *mode, FILE *stream) {
	int error = __fflush(stream);

	if (stream->file >= 0)
		close(stream->file);
	if (stream->name != NULL && (stream->_flags & __BPTRS) == 0) /* file is temporary */
	{
		BPTR cd = CurrentDir(stream->tmpdir); /* cd t: */
		if (!DeleteFile((CONST_STRPTR)stream->name)) /* delete file */
		{
			__seterrno();
			error = 1;
		}
		free(stream->name); /* free filename */
		stream->name = NULL;
		UnLock(CurrentDir(cd)); /* cd back, unlock t: */
	}
	stream->file = 0;

	if (error)
		return NULL;

	if (filename != NULL) {
		long file, flags = O_RDONLY;
		char ch;
		if (mode == NULL)
			return NULL;
		if (ch = *mode++, ch != 'r')
			if (flags = O_WRONLY | O_CREAT | O_TRUNC, ch != 'w')
				if (flags = O_WRONLY | O_CREAT | O_APPEND, ch != 'a')
					return NULL;
		if ((ch = *mode++)) {
			if (ch == '+') {
				if ((ch = *mode++) && (ch != 'b' || *mode))
					return NULL;
				flags = (flags & ~O_ACCMODE) | O_RDWR;
			} else if (ch != 'b')
				return NULL;
			else if ((ch = *mode++)) {
				if (ch != '+' || *mode)
					return NULL;
				flags = (flags & ~O_ACCMODE) | O_RDWR;
			}
		}

		if ((file = open(filename, flags, 0777)) < 0)
			return NULL;

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

	return stream;
}


/*
 **
 */
void __initstdio(void) {
	extern struct WBStartup *_WBenchMsg;
	StdFileDes *fp, **sfd;

	if ((__stdfiledes = sfd = (StdFileDes **) malloc(4 * sizeof(StdFileDes *)))) {
		if ((fp = (StdFileDes *) malloc(sizeof(StdFileDes)))) {
			*sfd++ = fp;
			fp->lx_fh = Input();
			fp->lx_pos = STDIN_FILENO;
			fp->lx_oflags = O_RDONLY;
			_setup_file(fp);
			fp->lx_flags |= LX_SYS;
			if ((fp = (StdFileDes *) malloc(sizeof(StdFileDes)))) {
				*sfd++ = fp;
				fp->lx_fh = Output();
				fp->lx_pos = STDOUT_FILENO;
				fp->lx_oflags = O_WRONLY;
				_setup_file(fp);
				fp->lx_flags |= LX_SYS;
				if ((fp = (StdFileDes *) malloc(sizeof(StdFileDes)))) {
					*sfd++ = fp;
					*sfd = 0; // have a free one

					struct Process * proc = (struct Process *) SysBase->ThisTask;
#ifdef __KICK13__
					struct CommandLineInterface * cli = (struct CommandLineInterface *)BADDR(proc->pr_CLI);
					fp->lx_fh = cli->cli_StandardOutput;
					if(fp->lx_fh==0)
#else
					if ((fp->lx_fh = (proc)->pr_CES) == 0)
#endif
						if (_WBenchMsg || (fp->lx_fh = stderrdes = Open((CONST_STRPTR)"*", MODE_OLDFILE)) == 0)
							fp->lx_fh = sfd[STDOUT_FILENO]->lx_fh;
					fp->lx_pos = STDERR_FILENO;
					fp->lx_oflags = O_WRONLY;
					_setup_file(fp);
					fp->lx_flags |= LX_SYS;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

					{
						// fdopen stdin, stdout and stderr and make stderr unbuffered
						FILE **f = __sF, *err;
						if (((*f++ = fdopen(STDIN_FILENO, "r")) == NULL) || ((*f++ = fdopen(STDOUT_FILENO, "w")) == NULL) || ((*f = err = fdopen(STDERR_FILENO, "w")) == NULL))
							exit(20);
						free(err->_bf._base);
						err->_flags &= ~(__SMBF | __SLBF);
						err->_flags |= __SNBF;
						err->_bf._base = err->unget;
					}

					return;
				}
			}
		}
	}
	exit(20);
}


/**
 * Close the file descriptor d.
 *
 * Located here since it's called from __exitstdio
 */
int close(int d) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	if (sfd) {

		if (sfd->lx_fx)
			return sfd->lx_fx->lx_close(sfd);

		if (!(sfd->lx_inuse -= 1)) {
			if (!(sfd->lx_flags & LX_SYS)) {
				if (!Close(sfd->lx_fh)) {
					__seterrno();
					return EOF;
				}
			}
		}
	}

	return 0;
}

/**
 * Close the file handle stream.
 *
 * Located here since it's called from __exitstdio
 */

int fclose(FILE *stream) {
	struct filenode *node;
	int retval;
	if (!stream) {
		return EOF;
	}
	retval = freopen(NULL, NULL, stream) == NULL ? EOF : 0;
	if (stream->_flags & __SMBF) /* Free buffer if necessary */
	{
		free(stream->_bf._base);
		stream->_bf._base = NULL;
	}

	if (stream->_flags & __BPTRS) {
		Close((BPTR )stream->name);
		Close((BPTR )stream->tmpdir);
	}

	node = (struct filenode *) ((struct MinNode *) stream - 1);
	Remove((struct Node * )&node->node);
	free(node);
	return retval;
}

struct MinList __filelist = { /* list of open files (fflush() needs also access) */
(struct MinNode *) &__filelist.mlh_Tail,
NULL, (struct MinNode *) &__filelist.mlh_Head };

void __exitstdio(void) {
	struct MinNode *node;
	while ((node = __filelist.mlh_Head)->mln_Succ != NULL) {
		fclose(&((struct filenode *) node)->theFILE);
	}

	int i, max;
	for (max = __stdfilesize, i = 0; i < max; i++) {
		StdFileDes *sfd = __stdfiledes[i];
		if (sfd && sfd->lx_inuse) {
			sfd->lx_inuse = 1; // force closing
			close(i);
		}
	}

	if (stderrdes)
		Close(stderrdes);
}

ADD2INIT(__initstdio, -30);
ADD2EXIT(__exitstdio, -30);
