#include <stdlib.h>
#include <unistd.h>
#include "stabs.h"
#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dosextens.h>
#include <dos/var.h>

char *__dummy_env[] = { 0 };
char ** environ_ptr__data = __dummy_env;
char ***environ_ptr = &environ_ptr__data;

#undef environ
#define environ __dont_use_environ

int __fillenviron() {
	unsigned index, slen, tlen;
	char * p;
	struct Process * proc = (struct Process *)SysBase->ThisTask;
	struct MinList * vars = &proc->pr_LocalVars;

	// size the environ
	unsigned varCount = 1; // trailing NULL
	{struct Node * n;
	for (n = (struct Node *)vars->mlh_Head; n->ln_Succ; n = n->ln_Succ) {
		if (n->ln_Type == LV_VAR)
			++varCount;
	}}
	char ** new_environ = (char **)malloc(varCount * sizeof(char *));
	if (new_environ == 0) {
		errno = ENOMEM;
		return -1;
	}

	// fill the environ
	index = 0;
	{struct LocalVar * n; for (n = (struct LocalVar *)vars->mlh_Head; n->lv_Node.ln_Succ; n = (struct LocalVar *)n->lv_Node.ln_Succ) {
		if (n->lv_Node.ln_Type != LV_VAR)
			continue;

		slen = strlen(n->lv_Node.ln_Name);
		tlen = slen + n->lv_Len + 1;
		p = new_environ[index] = malloc(tlen + 1);
		if (!p) {
			errno = ENOMEM;
			break;
		}

		strcpy(p, n->lv_Node.ln_Name);
		p[slen] = '=';
		memcpy(p + slen + 1, n->lv_Value, n->lv_Len);
		p[tlen] = 0;
		++index;
	}}
	new_environ[index++] = 0;
	environ_ptr__data = new_environ;
	return index - varCount;
}

int clearenv(void) {
	if (environ_ptr__data != __dummy_env) {
		char ** p = environ_ptr__data;
		while (*p) {
			free(*p++);
		}
		free(environ_ptr__data);
		environ_ptr__data = __dummy_env;
	}
	return 0;
}


ADD2INIT(__fillenviron,-2);
