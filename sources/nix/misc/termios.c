#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <proto/dos.h>

extern StdFileDes *_lx_fhfromfd(int d);

static struct termios std_termios = {
		0, 0, 0,
		ECHO
};


int tcsetattr(int fildes, int optional_actions,
       const struct termios *termios_p) {
	StdFileDes * sfd = _lx_fhfromfd(fildes);

	if (!sfd || fildes > 2) {
		// no valid fildes
		errno = EBADF;
		return -1;
	}

	if ((sfd->lx_flags & LX_ATTY) == 0) {
		// not a tty
		errno = ENOTTY;
		return -1;
	}

	// echo switched off?
	if ((std_termios.c_lflag & ECHO) && !(termios_p->c_lflag & ECHO))
		Write(sfd->lx_fh, "\x9B\x38\x6D", 3);

	if (!(std_termios.c_lflag & ECHO) && (termios_p->c_lflag & ECHO))
		Write(sfd->lx_fh, "\x9B\x32\x38\x6D", 4);

	std_termios = *termios_p;

	return 0;
}

int tcgetattr(int fildes, struct termios *termios_p) {
	StdFileDes * sfd = _lx_fhfromfd(fildes);

	if (!sfd || fildes > 2) {
		// no valid fildes
		errno = EBADF;
		return -1;
	}

	if ((sfd->lx_flags & LX_ATTY) == 0) {
		// not a tty
		errno = ENOTTY;
		return -1;
	}

	*termios_p = std_termios;

	return 0;
}
