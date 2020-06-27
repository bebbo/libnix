#include <termios.h>


int tcsetattr(int fildes, int optional_actions,
       const struct termios *termios_p) {
	return -1;
}

int tcgetattr(int fildes, struct termios *termios_p) {
	return -1;
}
