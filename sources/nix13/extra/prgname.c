#include <exec/execbase.h>
#include <exec/tasks.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <string.h>


int GetProgramName(char * to, unsigned len) {
	struct Process * process = (struct Process *) SysBase->ThisTask;
	struct CommandLineInterface * cli = (struct CommandLineInterface *) BADDR(process->pr_CLI);
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
