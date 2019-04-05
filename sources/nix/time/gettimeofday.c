#include <time.h>
#include <proto/dos.h>
#include <proto/timer.h>
#include <devices/timer.h>
#include <sys/time.h>

#define TimerBase DOSBase->dl_TimeReq->tr_node.io_Device

int gettimeofday(struct timeval *tv, struct timezone *tz) {
	GetSysTime(tv);
	return 0;
}
