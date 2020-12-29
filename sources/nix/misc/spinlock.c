#include <exec/execbase.h>
#include <proto/exec.h>

#ifdef DEBUG
#include "clib/debug_protos.h"
#else
#define KPrintF(a,...)
#endif

void __regargs __spinLock(unsigned * l) {
	struct Task * dis = SysBase->ThisTask;
	if (*l == (unsigned)dis) {
		++l[1];
		if (*l == 1) {
			Forbid();
		    KPrintF("%ld got %ld\n", dis, l);
		    Permit();
		}
		return;
	}

	Forbid();
	while (*(volatile unsigned *)l != 0) {
		// calling Permit() will trigger a reschedule
		SysBase->SysFlags |= 1<<15; // trigger rescheduling on Permit();
		KPrintF("waiting for %ld - locked by %ld\n", l, *l);
		Permit();
		Forbid();
	}

	*l = (unsigned)dis;
	l[1] = 1;
	KPrintF("%ld got %ld after wait\n", dis, l);
	Permit();
}
