/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* RexxSysBase[2] = { 0, "rexxsyslib.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <rexx/rxslib.h>
#include <rexx/rexxio.h>

#include <interfaces/rexxsyslib.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct RxsLib * RexxSysBase = NULL;
__attribute__((weak)) struct RexxSysIFace* IRexxSys = NULL;

void __init_RexxSys(void) __attribute__((constructor));
void __exit_RexxSys(void) __attribute__((destructor));

void __init_RexxSys(void) {
  if (RexxSysBase == NULL) {
    RexxSysBase = (struct RxsLib *) IExec->OpenLibrary("rexxsyslib.library", 0);
    assert(RexxSysBase != NULL);
  }
  if (IRexxSys == NULL) {
    IRexxSys = (struct RexxSysIFace*) IExec->GetInterface((struct Library*) RexxSysBase, "main", 1, NULL);
    assert(IRexxSys != NULL);
  }
}

void __exit_RexxSys(void) {
  IExec->DropInterface((struct Interface*) IRexxSys);
  IExec->CloseLibrary((struct Library*) RexxSysBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
