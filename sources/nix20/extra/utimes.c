#include <time.h>
#include <utime.h>
#include <errno.h>
#include <proto/dos.h>
#include <devices/timer.h>
#include <sys/time.h>

#define SECSPERDAY (24L * 60L * 60L)

#ifdef __KICK13__

#include <proto/exec.h>
#include <string.h>

extern long getBstr(char const * file);
extern struct StandardPacket * getStandardPacket();

int SetFileDate(char const * file, struct DateStamp const * ds) {
	if (ds == 0)
		return ERROR_REQUIRED_ARG_MISSING;

	int err = ERROR_OBJECT_NOT_FOUND;
	BPTR flock = Lock(file, SHARED_LOCK);
	if (flock != 0) {
		BPTR lock = ParentDir(flock);
		if (lock != 0) {

			char const * last = strrchr(file, '/');
			if (last == 0)
				last = strrchr(file, ':');
			if (last != 0)
				file = last + 1;

			long bstr = getBstr(file);
			if (bstr != 0) {
				struct StandardPacket * sp = getStandardPacket();
				sp->sp_Pkt.dp_Type = ACTION_SET_DATE;
				sp->sp_Pkt.dp_Arg2 = lock;
				sp->sp_Pkt.dp_Arg3 = bstr;
				sp->sp_Pkt.dp_Arg4 = (long)ds;

				struct MsgPort * mp = (struct MsgPort *) ((struct FileLock *) BADDR(lock))->fl_Task;
				struct MsgPort * rp = sp->sp_Msg.mn_ReplyPort;
				sp->sp_Pkt.dp_Port = rp;
				PutMsg(mp, &sp->sp_Msg);
				WaitPort(rp);
				GetMsg(rp);

				err = sp->sp_Pkt.dp_Res1;
			} else
				err = ERROR_LINE_TOO_LONG;

			UnLock(lock);
		}
		UnLock(flock);
	}

	return err;
}
#endif

int utimes(const char *file, const struct timeval *times) {
	struct DateStamp d;

	if (times) {
		struct timeval modtime = times[1];
		time_t t;

		if (modtime.tv_usec > 1000000) {
			modtime.tv_sec += (modtime.tv_usec / 1000000);
			modtime.tv_usec %= 1000000;
		}
		t = modtime.tv_sec;
#if 0
    extern long _timezone;
#endif
		t -= (2922L * SECSPERDAY); /* Datestamps start from Jan 1, 1978, unix
		 time from Jan 1, 1970, i.e., 2922 days
		 earlier! */
#if 0
    t -= _timezone;	/* Adjust for local time */
#endif
		d.ds_Days = t / SECSPERDAY;
		t %= SECSPERDAY;
		d.ds_Minute = t / 60L;
		t %= 60L;
		d.ds_Tick = t * 50 + (modtime.tv_usec / 20000);
	} else {
		DateStamp(&d);
	}

	if (SetFileDate((STRPTR )file, &d)) {
		errno = 0;
		return 0;
	} else {
		errno = ENOENT;
		return -1;
	}
}
