#include <stdlib.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <signal.h>

int kill(pid_t pid, int signo) {
	struct Task *task;

	if (pid <= 0 || (signo != SIGTERM && signo != SIGINT)) {
		errno = EINVAL;
		return -1;
	}

	errno = 0;

	Forbid();
	task = (struct Task *) FindCliProc(pid);

	if (task == FindTask(NULL)) {
		Permit();
		exit(EXIT_FAILURE);
	}
	Signal(task, SIGBREAKF_CTRL_C);
	Permit();
	return 0;
}
