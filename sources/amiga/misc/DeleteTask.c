#include <exec/execbase.h>
#include <inline/exec.h>

extern struct ExecBase * SysBase;

VOID DeleteTask(struct Task * t) {
	RemTask(t);
}
