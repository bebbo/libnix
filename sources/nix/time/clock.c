#include <time.h>
#include <limits.h>
#include <proto/dos.h>
#include <proto/timer.h>
#include "stabs.h"

static struct EClockVal eval0;

void __initclock(void)
{
	struct Device * TimerBase = DOSBase->dl_TimeReq->tr_node.io_Device;
	ReadEClock(&eval0);
}

ADD2INIT(__initclock,-10);

clock_t clock(void)
{
	struct EClockVal eval;
	struct Device * TimerBase = DOSBase->dl_TimeReq->tr_node.io_Device;
	UWORD freq = ReadEClock(&eval) / 1000; // 709 or 715  < 1024

	ULONG difflo = eval.ev_lo - eval0.ev_lo;
	ULONG diffhi = eval.ev_hi - eval0.ev_hi;
	ULONG remhi = diffhi % freq; // max 10 bit
	return difflo / freq + (((remhi << 22) / freq) << 10);
}
