/******************************************************************************/
/*                                                                            */
/* includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include <exec/types.h>
#include <exec/execbase.h>
#include <dos/dosextens.h>
#include <proto/exec.h>
#include "stabs.h"

/******************************************************************************/
/*                                                                            */
/* exports                                                                    */
/*                                                                            */
/******************************************************************************/

const BYTE LibName[]="simple.library";
const BYTE LibIdString[]="version 1.0";

const UWORD LibVersion=1;
const UWORD LibRevision=0;

/******************************************************************************/
/*                                                                            */
/* global declarations                                                        */
/*                                                                            */
/******************************************************************************/

struct Library *myLibPtr;
struct ExecBase *SysBase;
struct DosLibrary *DOSBase;

/******************************************************************************/
/*                                                                            */
/* user library initialization                                                */
/*                                                                            */
/* !!! CAUTION: This function may run in a forbidden state !!!                */
/*                                                                            */
/******************************************************************************/

int __UserLibInit(struct Library *myLib)
{
  /* setup your library base - to access library functions over *this* basePtr! */

  myLibPtr = myLib;

  /* required !!! */
  SysBase=*(struct ExecBase **)4;

  return (DOSBase=(struct DosLibrary *)OpenLibrary("dos.library",33))==NULL;
}

/******************************************************************************/
/*                                                                            */
/* user library cleanup                                                       */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

void __UserLibCleanup()
{
  CloseLibrary((struct Library *)DOSBase);
}

/******************************************************************************/
/*                                                                            */
/* library dependent function(s)                                              */
/*                                                                            */
/******************************************************************************/

ADDTABL_1(__UserFunc,d0); /* One Argument in d0 */

int __UserFunc(long a)
{
  return a*2;
}

/******************************************************************************/
/*                                                                            */
/* endtable marker (required!)                                                */
/*                                                                            */
/******************************************************************************/

ADDTABL_END();

/******************************************************************************/
/*                                                                            */
/* end of simplelib.c                                                         */
/*                                                                            */
/******************************************************************************/
