#include <stdlib.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <signal.h>

int kill(pid_t pid, int signo) {
	if (pid <= 0 || (signo != SIGTERM && signo != SIGINT)) {
		errno = EINVAL;
		return -1;
	}

	errno = 0;

	Forbid();
	struct Task *task = FindCliProc(pid);

	if (task == FindTask(NULL)) {
		Permit();
		exit(EXIT_FAILURE);
	}
	Signal(task, SIGBREAKF_CTRL_C);
	Permit();
	return 0;
}
