#include <sys/stat.h>
#include <proto/dos.h>

int mkdir(const char * filename, mode_t mode) {
	return CreateDir(filename) == DOSTRUE;
}
