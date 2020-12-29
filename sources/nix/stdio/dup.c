#include "stdio.h"

/*
 **
 */

extern StdFileDes **__stdfiledes;
extern unsigned __stdfilesize;
#ifdef __posix_threads__
unsigned __stdLock[2];
#endif
extern StdFileDes *__allocfd();

int dup(int oldfd) {
	__spinLock(__stdLock);
	if ((unsigned)oldfd < __stdfilesize) {
		int fd;
		StdFileDes *neu, *sfd = __stdfiledes[oldfd];
		if (sfd && sfd->lx_inuse) {

			if (sfd->lx_fx) {
				int r = sfd->lx_fx->lx_dup(sfd);
				__spinUnlock(__stdLock);
				return r;
			}

			neu = __allocfd();
			fd = neu->lx_pos;
			*neu = *sfd;
			neu->lx_pos = fd;
			__spinLock(__stdLock);
			return fd;
		}
	}
	__spinLock(__stdLock);
	return -1;
}
