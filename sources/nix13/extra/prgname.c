#include <exec/tasks.h>
#include <inline/exec.h>
#include <dos/dos.h>
#include <dos/dosextens.h>

extern struct ExecBase * SysBase;
extern struct DOSBase * DOSBase;

int GetProgramName(char * to, unsigned len) {
	struct Process * process = (struct Process *) FindTask(0);
	struct CommandLineInterface * cli = (struct CommandLineInterface *)BADDR(process->pr_CLI);
	if (cli) {
		unsigned char * bname = (unsigned char *) BADDR(cli->cli_CommandName);
		if (*bname < len - 1) {
			strncpy(to, bname + 1, *bname);
			to[*bname] = 0;
			process->pr_Result2 = 0;
			return DOSTRUE;
		}
	}
	process->pr_Result2 = ERROR_LINE_TOO_LONG;
	if (to && len)
		*to = 0;
	return DOSFALSE;
}

BPTR SelectInput(BPTR p) {
	struct Process * process = (struct Process *) FindTask(0);
	BPTR r = process->pr_CIS;
	process->pr_CIS = p;
	return r;
}

BPTR SelectOutput(BPTR p) {
	struct Process * process = (struct Process *) FindTask(0);
	BPTR r = process->pr_COS;
	process->pr_COS = p;
	return r;
}
