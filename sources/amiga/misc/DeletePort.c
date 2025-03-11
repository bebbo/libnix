#include <exec/ports.h>
#include <exec/memory.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>

VOID DeletePort(struct MsgPort *port)
{ APTR SysBase = *(APTR *)4L;

  if (port->mp_Node.ln_Name)
    RemPort(port);
  FreeSignal(port->mp_SigBit); FreeMem(port,sizeof(*port));
}
