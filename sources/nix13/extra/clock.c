#include <time.h>
#include <limits.h>
#include <dos/dos.h>
#include <proto/dos.h>
#include <hardware/custom.h>
#include "stabs.h"

static struct DateStamp ds;

void __initclock(void)
{ DateStamp(&ds); }

ADD2INIT(__initclock,-10);

clock_t clock(void)
{
	static volatile struct Custom * c = (struct Custom *)0xdff000;
	static int lastinc, lastvp;
	static clock_t lastti;
	struct DateStamp ds;
	DateStamp(&ds); /* Get timestamp */
	clock_t ms = ((ds.ds_Days + 2922) * 1440 + ds.ds_Minute) * 60 * CLOCKS_PER_SEC + ds.ds_Tick * (CLOCKS_PER_SEC / TICKS_PER_SECOND);
	int vp = lastvp;
	int inc = c->vhposr >> 12;
	if (ms == lastti) {
		if (inc >= lastinc)
			vp += inc - lastinc;
		else
			++vp;
		if (vp > 19)
			vp = 19;
	} else {
		vp = 0;
	}

	lastinc = inc;
	lastvp = vp;
	lastti = ms;

	return ms + vp;
}
