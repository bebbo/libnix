#ifdef __GNUC__
#include <exec/io.h>
#include <exec/devices.h>

void BeginIO(struct IORequest *iorequest)
{ register struct IORequest *a1 asm("a1")=iorequest;
  register struct Device    *a6 asm("a6")=iorequest->io_Device;
  __asm __volatile ("jsr a6@(-30:W)"::"r"(a1),"r"(a6):"a0","a1","d0","d1");
}
#endif
