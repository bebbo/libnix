#include <exec/execbase.h>
#include <proto/exec.h>

/**
 * SBF: let the scheduler switch to the next running task.
 */
void Yield() {
	Forbid();
	SysBase->SysFlags |= 1<<15; // trigger rescheduling on Permit();
	Permit();
}
