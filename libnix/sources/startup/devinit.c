/******************************************************************************/
/*                                                                            */
/* this works with gcc too and makes life easier                              */
/*                                                                            */
/******************************************************************************/

#define _USEOLDEXEC_

/******************************************************************************/
/*                                                                            */
/* includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include <exec/types.h>
#include <exec/resident.h>
#include <proto/exec.h>
#include "libinit.h"
#include "stabs.h"

/******************************************************************************/
/*                                                                            */
/* *** FIRST *** function - prevents a crash when called from CLI!            */
/*                                                                            */
/******************************************************************************/

int safefail()
{
  return -1;
}

/******************************************************************************/
/*                                                                            */
/* imports                                                                    */
/*                                                                            */
/******************************************************************************/

extern const UWORD DevVersion;
extern const UWORD DevRevision;

extern const BYTE DevName[];
extern const BYTE DevIdString[];

extern APTR  __FuncTable__[];

extern int   __UserDevInit(_DEV *);
extern int   __UserDevOpen(struct IORequest *,ULONG,ULONG);
extern VOID  __UserDevClose();
extern VOID  __UserDevCleanUp();

/******************************************************************************/
/*                                                                            */
/* resident structure                                                         */
/*                                                                            */
/******************************************************************************/

const APTR InitTab[4];

static const struct Resident RomTag = {
  RTC_MATCHWORD,
  (struct Resident *)&RomTag,
  (APTR)((&RomTag)+1),
  RTF_AUTOINIT,
  0,
  NT_DEVICE,
  0,
  (BYTE *)DevName,
  (BYTE *)DevIdString,
  (APTR)&InitTab
};

/******************************************************************************/
/*                                                                            */
/* autoinit table for use with initial MakeLibrary()                          */
/*                                                                            */
/******************************************************************************/

const APTR InitTab[4] = {
  (APTR)sizeof(_DEV),
  (APTR)&__FuncTable__[1],
  0,
  (APTR)DevInit
};

/******************************************************************************/
/*                                                                            */
/* support function(s) to be inlined                                          */
/*                                                                            */
/******************************************************************************/

static inline APTR __GetDataSeg()
{
  APTR res;
  asm ("lea ___a4_init,%0" : "=a" (res));
  return res;
}

static inline ULONG __BSize()
{
  ULONG res;
  asm ("movel #___bss_size,%0" : "=d" (res));
  return res;
}

static inline ULONG *__GetBssStart()
{
  ULONG *res;
  asm ("lea __edata,%0" : "=a" (res));
  return res;
}

/******************************************************************************/
/*                                                                            */
/* initialization function called by MakeLibrary()                            */
/*                                                                            */
/******************************************************************************/

struct Library *DevInit()
{
  register APTR DataSeg asm("a4");
  register APTR SegList asm("a0");
  register struct Library *dev asm("d0");
  _DEV *Device = (_DEV *)dev;
  ULONG size,result;

  /* init library base */

  Device->DevNode.lib_Node.ln_Type = NT_DEVICE;
  Device->DevNode.lib_Node.ln_Name = (UBYTE *)DevName;
  Device->DevNode.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  Device->DevNode.lib_Version      = (UWORD)DevVersion;
  Device->DevNode.lib_Revision     = (UWORD)DevRevision;
  Device->DevNode.lib_IdString     = (UBYTE *)DevIdString;
  Device->SegList                  = SegList;
  Device->DataSeg                  = __GetDataSeg();

  /* clear the bss part */

  if ((size=__BSize()))
  {
    ULONG *p=__GetBssStart();

    do
    {
      *p++=0;
    }
    while((size-=sizeof(ULONG)));
  }

  DataSeg=Device->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));

  /* now call user-init */

  result=__UserDevInit(Device);

  /* all ok? */

  if (result!=0)
    Device=NULL;

  /* this will be added to SysBase->DevList or NULL (init error) */

  return (struct Library *)Device;
}

/******************************************************************************/
/*                                                                            */
/* DevOpen() will be called for every OpenDevice()                            */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

VOID DevOpen()
{
  register struct Library *dev asm("a6");
  register struct IORequest *iorq asm("a1");
  register ULONG flags asm("d1");
  register ULONG unit asm("d0");
  register APTR DataSeg asm("a4");
  int result;

  /* any memory allocation can cause a call of THIS device expunge vector.
     if OpenCnt is zero the library might go away ... so fake a user :-) */

  dev->lib_OpenCnt++;

  DataSeg=((_DEV *)dev)->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));

  /* call user-open */

  result=__UserDevOpen(iorq,unit,flags);

  if (result==0)
  {
    /* clear delayed expunge flag */

    dev->lib_Flags &= ~LIBF_DELEXP;

    /* one new user */

    dev->lib_OpenCnt++;
  }

  /* end of expunge protection */

  --dev->lib_OpenCnt;

  /* exec returns io_error later */
}

/******************************************************************************/
/*                                                                            */
/* DevClose() will be called for every CloseDevice()                          */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

APTR DevClose()
{
  register struct Library *dev asm("a6");
  register struct IORequest *iorq asm("a1");
  register APTR DataSeg asm("a4");
  APTR SegList=0;

  DataSeg=((_DEV *)dev)->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));

  __UserDevClose(iorq);

  /* one less user */

  if (--dev->lib_OpenCnt==0 && (dev->lib_Flags&LIBF_DELEXP))
    SegList=DevExpunge();

  /* SegList or NULL (still in use) */

  return SegList;
}

/******************************************************************************/
/*                                                                            */
/* remove device from memory if possible                                      */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

APTR DevExpunge()
{
  register struct Library *dev asm("a6");
  register APTR DataSeg asm("a4");
  _DEV *Device = (_DEV *)dev;
  APTR SegList=0;

  /* set delayed expunge flag */

  Device->DevNode.lib_Flags |= LIBF_DELEXP;

  /* still in use? */

  if (Device->DevNode.lib_OpenCnt == 0)
  {
    ULONG NegSize;

    /* return the seglist for UnLoadSeg() */

    SegList = Device->SegList;

    /* remove device from SysBase->DevList */

    Remove((struct Node *)Device);

    DataSeg=Device->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));
 
    /* now call user-exit */

    __UserDevCleanup();

    /* free device */

    NegSize = Device->DevNode.lib_NegSize;
    FreeMem((APTR)((UBYTE *)Device-(UBYTE *)NegSize),NegSize+Device->DevNode.lib_PosSize);
  }
  return SegList;
}

/******************************************************************************/
/*                                                                            */
/* a do nothing stub (required!)                                              */
/*                                                                            */
/******************************************************************************/

APTR DevExtFunc()
{
  return 0;
}

/******************************************************************************/
/*                                                                            */
/* add these functions to 'funclist'                                          */
/*                                                                            */
/******************************************************************************/

ADD2LIST(DevOpen,__FuncTable__,22);
ADD2LIST(DevClose,__FuncTable__,22);
ADD2LIST(DevExpunge,__FuncTable__,22);
ADD2LIST(DevExtFunc,__FuncTable__,22);

/******************************************************************************/
/*                                                                            */
/* end of devinit.c                                                           */
/*                                                                            */
/******************************************************************************/
