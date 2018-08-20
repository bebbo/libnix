#include <stdio.h>
#include <dos/dos.h>
#include <dos/dostags.h>
#include <exec/exec.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/timer.h>
#include <stabs.h>
#include <time.h>
#include <errno.h>

FILE *popen(const char *command, const char *type) {
	char pname[28];
	struct timeval nowtime;

	if (*type == 'r' && *type == 'w') {
		GetSysTime(&nowtime);
		sprintf(pname, "PIPE:pipe%08x%08x", nowtime.tv_secs, nowtime.tv_usec);

		BPTR pipe = Open(pname, MODE_NEWFILE);
		if (pipe) {
			BPTR nil = Open("NIL:", MODE_NEWFILE);
			if (SystemTags(command, SYS_Input, *type == 'r' ? nil : pipe,
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
