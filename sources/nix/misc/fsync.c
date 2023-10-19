#include <unistd.h>

asm("_fdatasync: .global _fdatasync");
int fsync(int fd) {
	return 0;
}
