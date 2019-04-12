/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* SysBase[2] = { 0, "exec.library" };
ADD2LIB(SysBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/tasks.h>
#include <exec/memory.h>
#include <exec/ports.h>
#include <exec/devices.h>
#include <exec/io.h>
#include <exec/semaphores.h>
#include <exec/avl.h>

#include <interfaces/exec.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct ExecBase * SysBase = NULL;
__attribute__((weak)) struct SysIFace* ISys = NULL;

void __init_Sys(void) __attribute__((constructor));
void __exit_Sys(void) __attribute__((destructor));

void __init_Sys(void) {
  if (SysBase == NULL) {
    SysBase = (struct ExecBase *) IExec->OpenLibrary("exec.library", 0);
    assert(SysBase != NULL);
  }
  if (ISys == NULL) {
    ISys = (struct SysIFace*) IExec->GetInterface((struct Library*) SysBase, "main", 1, NULL);
    assert(ISys != NULL);
  }
}

void __exit_Sys(void) {
  IExec->DropInterface((struct Interface*) ISys);
  IExec->CloseLibrary((struct Library*) SysBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
