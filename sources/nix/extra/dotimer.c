#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/exec.h>

extern struct DosLibrary * DOSBase;

void dotimer(ULONG timercmd, struct timeval *t) {
	struct timerequest timeRequest = *DOSBase->dl_TimeReq;

	timeRequest.tr_node.io_Message.mn_ReplyPort = &(((struct Process *) SysBase->ThisTask)->pr_MsgPort);
	timeRequest.tr_node.io_Command = timercmd;

	timeRequest.tr_time.tv_micro = t->tv_micro;
	timeRequest.tr_time.tv_secs = t->tv_secs;

	if (!DoIO((struct IORequest * ) &timeRequest)) {
		t->tv_secs = timeRequest.tr_time.tv_secs;
		t->tv_micro = timeRequest.tr_time.tv_micro;
	}
}
