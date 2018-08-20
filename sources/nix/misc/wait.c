#include <sys/types.h>
#include <sys/wait.h>

#define ECHILD -1

pid_t wait(int *wstatus) {
	return ECHILD;
}

pid_t waitpid(pid_t pid, int *wstatus, int options) {
	return ECHILD;
}
