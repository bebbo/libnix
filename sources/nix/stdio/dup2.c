#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "stabs.h"

/*
 **
 */

extern StdFileDes **__stdfiledes;
extern int __stdfilesize;

int dup2(int oldfd, int newfd) {
	if (oldfd < __stdfilesize) {
		StdFileDes *old = __stdfiledes[oldfd];
		if (old && old->lx_inuse) {
			int fd;
			StdFileDes * neu;
			if (newfd < __stdfilesize) {
				neu = __stdfiledes[newfd];
				if (neu && neu->lx_inuse)
					close(newfd);
			} else
				neu = 0;
			if (!neu) {
				StdFileDes ** sfd = __stdfiledes;
				if (newfd >= __stdfilesize) {
					if ((sfd = realloc(__stdfiledes, ((unsigned)newfd + 1) * sizeof(int)))
							== NULL) {
						errno = ENOMEM;
						return -1;
					}
					__stdfiledes = sfd;
					for (; __stdfilesize <= newfd; ++__stdfilesize)
						sfd[__stdfilesize] = 0;
				}
				neu = sfd[newfd] = (StdFileDes *) malloc(sizeof(StdFileDes));
				if (!neu) {
					errno = ENOMEM;
					return -1;
				}
				neu->lx_pos = newfd;
			}
			fd = neu->lx_pos;
			*neu = *old;
			neu->lx_pos = fd;
			return fd;
		}
	}
	return -1;
}
