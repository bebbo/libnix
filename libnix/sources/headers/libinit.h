/******************************************************************************/
/*                                                                            */
/* special define(s)                                                          */
/*                                                                            */
/******************************************************************************/

#if !defined(REG)
#define REG(reg,arg) arg __asm(#reg)
#endif

#include <exec/resident.h>
#include <exec/libraries.h>
#include <proto/exec.h>
#include "stabs.h"

/******************************************************************************/
/*                                                                            */
/* structure definition for a *** PRIVATE *** library/device base             */
/*                                                                            */
/******************************************************************************/

struct LibBase {
  struct Library  LibNode;
  UWORD           Pad;
  LONG            SegList;
  APTR            DataSeg,
                  SysBase;
#ifdef EXTENDED
  ULONG           DataSize;
  struct LibBase *Parent;
#endif
};

/******************************************************************************/
/*                                                                            */
/* prototypes for basic library functions                                     */
/*                                                                            */
/******************************************************************************/

LONG LibExtFunc(VOID);
LONG LibExpunge(REG(a6,struct LibBase *));
LONG LibClose(REG(a6,struct LibBase *));
APTR LibOpen(REG(a6,struct LibBase *));
APTR LibInit(REG(a0,LONG),REG(d0,struct LibBase *),REG(a6,struct Library *));

/******************************************************************************/
/*                                                                            */
/* prototypes for basic device functions                                      */
/*                                                                            */
/******************************************************************************/

APTR DevInit();
VOID DevOpen();
APTR DevClose();
APTR DevExpunge();
APTR DevExtFunc();

/******************************************************************************/
/*                                                                            */
/* imports                                                                    */
/*                                                                            */
/******************************************************************************/

extern LONG __stdargs __UserLibInit(struct Library *,REG(a4,APTR));
extern VOID __stdargs __UserLibCleanup(REG(a4,APTR));

extern const UWORD LibVersion;
extern const UWORD LibRevision;
extern const char LibIdString[];
extern const char LibName[];

extern APTR __LibTable__[];
extern APTR __FuncTable__[];

extern LONG __datadata_relocs[];

/******************************************************************************/
/*                                                                            */
/* end of libinit.h                                                           */
/*                                                                            */
/******************************************************************************/
