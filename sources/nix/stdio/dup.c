#include "stdio.h"

/*
 **
 */

extern StdFileDes **__stdfiledes;
extern unsigned __stdfilesize;
extern StdFileDes *__allocfd();

int dup(int oldfd) {
	if ((unsigned)oldfd < __stdfilesize) {
		StdFileDes *sfd = __stdfiledes[oldfd];
		if (sfd && sfd->lx_inuse) {

			if (sfd->lx_fx)
				return sfd->lx_fx->lx_dup(sfd);

			StdFileDes * neu = __allocfd();
			int fd = neu->lx_pos;
			*neu = *sfd;
			neu->lx_pos = fd;
			return fd;
		}
	}
	return -1;
}
