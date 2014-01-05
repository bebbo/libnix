#include <dos/dosextens.h>
#include <proto/intuition.h>
#include <proto/exec.h>

extern char __intuitionname[];

void __request(const char *msg)
{
  APTR IntuitionBase, SysBase=*(APTR *)4L;
  static struct IntuiText body = { 0,0,0, 15,5, NULL, NULL, NULL };
  static struct IntuiText   ok = { 0,0,0,  6,3, NULL, "Ok", NULL };

  if (((struct Process *)FindTask(NULL))->pr_WindowPtr != (APTR)-1L) {
    if ((IntuitionBase=OpenLibrary(__intuitionname,0))) {
      body.IText = (UBYTE *)msg;
      AutoRequest(NULL,&body,NULL,&ok,0,0,640,72);
      CloseLibrary(IntuitionBase);
    }
  }
}
