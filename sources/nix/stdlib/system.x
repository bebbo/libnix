#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#include <clib/alib_protos.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <dos/dostags.h>
#include <exec/execbase.h>

#include <inline/bsdsocket.h>
int system(const char *string) {
	if (string == NULL) {
		errno = EINVAL;
		return -1;
	}
#ifndef __KICK13__
	if (((struct Library*) DOSBase)->lib_Version >= 36) {
		static struct TagItem notags[] = { { TAG_END, 0 } };
		return SystemTagList((CONST_STRPTR )string, notags);
	} else
#endif
		return (int) ~Execute((STRPTR )string, Input(), Output());
}

__attribute__((__noinline__))
__regargs int clutch(int cmdlen, void * cmdline, __regargs int (*realProc)(int cmdlen, void * cmdline)) {
	return realProc(cmdlen, cmdline);
}

static __regargs __entrypoint
int startProc(int cmdlen, void * cmdline) {
	volatile struct ExecBase * SysBase = *(struct ExecBase **)4;
	struct Process *self = (struct Process*) SysBase->ThisTask;
	for(;;) {
		struct Message * m = GetMsg(&self->pr_MsgPort);
		if (!m)
			continue;
		self->pr_Task.tc_UserData = m;
		__regargs int (*realProc)(int cmdlen, void * cmdline) = (__regargs int (*)(int, void *))m->mn_Node.ln_Name;
		int r = clutch(cmdlen, cmdline, realProc);
		SysBase = *(struct ExecBase **)4;
		Forbid();
		self = (struct Process*) SysBase->ThisTask;
		m = (struct Message *)self->pr_Task.tc_UserData;
		m->mn_Node.ln_Name = (char *)r;
		ReplyMsg(m);
		return r;
	}
}

int execvp(const char *file, char *const argv[]) {
	return execv(file, argv);
}
int execv(const char *path, char *const argv[]) {
	char *const*p;
	char *cmd;

//	if (1)
//		return 0;

	BPTR seg = LoadSeg((UBYTE * )path);
	printf("execv: %s -> %p\n", path, seg);
	if (!seg) {
		return -1;
	}

	int r, len = 1
			+ strlen(cmd)
			;
	for (p = argv; *p; ++p) {
		len += 3 + strlen(*p);
	}
	cmd = malloc(len);
	//*cmd = 0;
	strcpy(cmd, path);

	if (*argv)
	for (p = argv+1; *p; ++p) {
		strcat(cmd, " \"");
		strcat(cmd, *p);
		strcat(cmd, "\"");
	}
	if (1) {
		int r = system(cmd);
		free(cmd);
		exit(r);
	}


	printf("execv: %s %s\n", path, cmd);

//	BPTR inp = DupLock(Input());
//	BPTR out = DupLock(Output());
	BPTR stdio = Open((UBYTE* )"*", MODE_READWRITE);
	struct Process *proc = (struct Process*) CreateNewProcTags(
			NP_Entry, (ULONG) startProc,
			NP_Input, (ULONG) stdio,
			NP_Output, (ULONG) stdio,
			NP_Arguments, (ULONG) cmd,
			NP_FreeSeglist, seg,
			NP_StackSize, 100000,
			NP_Cli, 1,
			NP_Name, (ULONG )path,
			0);

	free(cmd);

	printf("execv: %s -> proc %p\n", path, proc);

	struct Process *self = (struct Process*) SysBase->ThisTask;
	struct MsgPort * mp = &self->pr_MsgPort;
	struct Message msg;
	msg.mn_Node.ln_Succ = 0;
	msg.mn_Node.ln_Pred = 0;
	msg.mn_Node.ln_Type = NT_MESSAGE;
	msg.mn_Node.ln_Pri = 42;
	msg.mn_Node.ln_Name = (char *)(1 + (ULONG *) BADDR(seg)); // real program start
	msg.mn_ReplyPort = mp;
	msg.mn_Length = sizeof(struct Message);

	PutMsg(&proc->pr_MsgPort, &msg);
	printf("execv: put msg -> %p\n", &proc->pr_MsgPort);
	for(;;) {
		WaitPort(mp);
		if (GetMsg(mp) == &msg)
			break;
	}
	int rc = (int)msg.mn_Node.ln_Name;
	printf("execv: done rc=%d\n", rc);
	exit(rc);
	return rc;
}

//int execvp(const char *file, char *const argv[]) {
//}

int pipe(int pipefd[2]) {
	return -1;
}

pid_t fork(void) {
	return 0;
}
