#include <stdlib.h>
#include "stabs.h"
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dosextens.h>
#include <dos/var.h>

#ifdef __KICK13__
#define LV_VAR 0
struct LocalVar {
	struct Node lv_Node;
	UWORD	lv_Flags;
	UBYTE	*lv_Value;
	ULONG	lv_Len;
};
#endif

static char *dummy_env[] = { 0 };

char **environ;

int __fillenviron() {
	struct Process * proc = (struct Process *)FindTask(0);
	struct MinList * vars = &proc->pr_LocalVars;

	// size the environ
	unsigned varCount = 1; // trailing NULL
	for (struct Node *  n = (struct Node *)vars->mlh_Head; n->ln_Succ; n = n->ln_Succ) {
		if (n->ln_Type == LV_VAR)
			++varCount;
	}
	environ = (char **)malloc(varCount * sizeof(char *));
	if (environ == 0) {
		environ = dummy_env;
		errno = ENOMEM;
		return -1;
	}

	// fill the environ
	unsigned index = 0;
	for (struct LocalVar *  n = (struct LocalVar *)vars->mlh_Head; n->lv_Node.ln_Succ; n = (struct LocalVar *)n->lv_Node.ln_Succ) {
		if (n->lv_Node.ln_Type != LV_VAR)
			continue;

		unsigned slen = strlen(n->lv_Node.ln_Name);
		unsigned tlen = slen + n->lv_Len + 1;
		char * p = environ[index] = malloc(tlen + 1);
		if (!p) {
			errno = ENOMEM;
			break;
		}

		strcpy(p, n->lv_Node.ln_Name);
		p[slen] = '=';
		memcpy(p + slen + 1, n->lv_Value, n->lv_Len);
		p[tlen] = 0;
		++index;
	}
	environ[index++] = 0;
	return index - varCount;
}

void __clearenviron() {
	if (environ != dummy_env) {
		char ** p = environ;
		while (*p) {
			free(*p++);
		}
		free(environ);
		environ = dummy_env;
	}
}

int clearenv(void) {
	struct Process * proc = (struct Process *)FindTask(0);
	for (struct Node *t, * n = (struct Node *)proc->pr_LocalVars.mlh_Head; n->ln_Succ; n = t) {
		t = n->ln_Succ;
		if (n->ln_Type != LV_VAR)
			continue;

		DeleteVar(n->ln_Name, 0);
	}
	__clearenviron();
	return 0;
}


ADD2INIT(__fillenviron,-2);
ADD2EXIT(__clearenviron,-2);
