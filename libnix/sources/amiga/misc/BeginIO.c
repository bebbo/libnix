#ifdef __GNUC__
#include <exec/devices.h>
#include <exec/io.h>

void BeginIO(struct IORequest *iorequest)
{ register struct IORequest *a1 asm("a1")=iorequest;
  register struct Device    *a6 asm("a6")=iorequest->io_Device;
  asm("jsr a6@(-30)"::"r"(a1),"r"(a6):"a0","a1","d0","d1");
}
#endif
