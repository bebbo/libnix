#include <dos/dos.h>
#include <dos/dostags.h>
#include <exec/exec.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/timer.h>
#include <stabs.h>
#include <time.h>
#include <errno.h>
#include "stdio.h"

FILE *popen(const char *command, const char *type) {
	char pname[28];
	struct timeval nowtime;

	if (*type == 'r' && *type == 'w') {
		GetSysTime(&nowtime);
		sprintf(pname, "PIPE:pipe%08x%08x", nowtime.tv_secs, nowtime.tv_usec);

		BPTR pipe = Open((CONST_STRPTR)pname, MODE_NEWFILE);
		if (pipe) {
			BPTR nil = Open((CONST_STRPTR)"NIL:", MODE_NEWFILE);
			if (SystemTags((CONST_STRPTR)command, SYS_Input, *type == 'r' ? nil : pipe,
					SYS_Output, *type == 'r' ? pipe : nil, SYS_Asynch, TRUE,
					SYS_UserShell, TRUE, TAG_END)) {
				FILE * f = fopen(pname, type);
				if (f) {
					f->_flags |= __BPTRS;
					f->tmpdir = (long)pipe;
					f->name = (char*)nil;
					return f;
				}
			}
			Close(nil);
			Close(pipe);
		}
	}
	errno = EIO;
	return 0;
}

ALIAS( pclose, fclose);
