#include <proto/dos.h>
#include <proto/exec.h>
#include <dos/dosextens.h>

#include <stdlib.h>
#include <string.h>

long getBstr(char const * file) {
	__attribute((aligned(4)))
	static char buf[256];
	if (!file)
		return 0;

	int len = strlen(file);
	if (len > 254)
		return 0;

	buf[0] = (char)len;
	strcpy(buf + 1, file);
	return MKBADDR(buf);
}

extern struct MsgPort *CreatePort(CONST_STRPTR name,LONG pri);
extern VOID DeletePort(struct MsgPort *port);

static struct StandardPacket * sp;
static void cleanupStandardPacket() {
	if (sp == 0)
		return;

	DeletePort(sp->sp_Msg.mn_ReplyPort);
	FreeMem(sp, sizeof(struct StandardPacket));
}

struct StandardPacket * getStandardPacket() {
	if (sp != 0)
		return sp;

	sp = (struct StandardPacket *)AllocMem(sizeof(struct StandardPacket), MEMF_PUBLIC);
	if (sp == 0)
		return 0;

	struct MsgPort * rp = CreatePort(NULL, 0);
	if (rp == 0) {
		FreeMem(sp, sizeof(struct StandardPacket));
		sp = 0;
		return 0;
	}

	sp->sp_Msg.mn_ReplyPort = rp;
	sp->sp_Msg.mn_Node.ln_Name = (char *)&sp->sp_Pkt;
	sp->sp_Pkt.dp_Link = &sp->sp_Msg;

	atexit(cleanupStandardPacket);

	return sp;
}
