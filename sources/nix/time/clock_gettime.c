#include <time.h>
#include <proto/dos.h>
#include <proto/timer.h>

#define TimerBase DOSBase->dl_TimeReq->tr_node.io_Device

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
	if (tp) {
		GetSysTime((struct timeval *)tp);
		tp->tv_nsec /= 1000;
	}
	return 0;
}
