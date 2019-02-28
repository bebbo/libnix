#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdio.h>
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
extern unsigned __stdfilesize;


int dup(int oldfd) {
	if ((unsigned)oldfd < __stdfilesize) {
		StdFileDes *old = __stdfiledes[oldfd];
		if (old && old->lx_inuse) {
			StdFileDes * neu = __allocfd();
			int fd = neu->lx_pos;
			*neu = *old;
			neu->lx_pos = fd;
			return fd;
		}
	}
	return -1;
}
