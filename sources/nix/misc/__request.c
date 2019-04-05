#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/intuition.h>
#include <proto/exec.h>
#include <stddef.h>

void __request(const char *msg) {
	static struct IntuiText body = { 0, 0, 0, 15, 5, NULL, NULL, NULL };
	static struct IntuiText ok = { 0, 0, 0, 6, 3, NULL, (STRPTR) "Ok", NULL };

	if (((struct Process *) SysBase->ThisTask)->pr_WindowPtr != (APTR) -1L) {
		body.IText = (UBYTE *) msg;
		AutoRequest(0, &body, 0, &ok, 0, 0, 640, 72);
	}
}
