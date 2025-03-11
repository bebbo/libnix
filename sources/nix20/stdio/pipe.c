#include <proto/dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

extern StdFileDes *__allocfd(void);
extern void _setup_file(StdFileDes *fp);

int pipe(int pipefd[2]) {

	char tmp[32];
	sprintf(tmp, "PIPE:libnix-%08lx-%08lx", time(0), rand());
	BPTR bout = Open(tmp, MODE_NEWFILE);
	BPTR bin = Open(tmp, MODE_OLDFILE);
	if (bin && bout) {
		Write(bin, tmp, 0); // no longer blocks!?
		StdFileDes* in = __allocfd();
		StdFileDes* out = __allocfd();
		if (in && out) {
			in->lx_oflags = O_RDONLY;
			in->lx_fh = bin;
			_setup_file(in);

			out->lx_flags = O_APPEND;
			out->lx_fh = bout;
			_setup_file(out);

			pipefd[0] = in->lx_pos;
			pipefd[1] = out->lx_pos;
			return 0;
		}
		if (in)
			in->lx_inuse = 0;
		if (out)
			out->lx_inuse = 0;
	}
	if (bin) Close(bin);
	if (bout) Close(bout);
	return -1;
}
