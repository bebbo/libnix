/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* DOSBase[2] = { 0, "dos.library" };
ADD2LIB(DOSBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <dos/record.h>
#include <dos/rdargs.h>
#include <dos/dosasl.h>
#include <dos/var.h>
#include <dos/notify.h>
#include <dos/datetime.h>
#include <dos/exall.h>
#include <utility/tagitem.h>

#include <interfaces/dos.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct DosLibrary * DOSBase = NULL;
__attribute__((weak)) struct DOSIFace* IDOS = NULL;

void __init_DOS(void) __attribute__((constructor));
void __exit_DOS(void) __attribute__((destructor));

void __init_DOS(void) {
  if (DOSBase == NULL) {
    DOSBase = (struct DosLibrary *) IExec->OpenLibrary("dos.library", 0);
    assert(DOSBase != NULL);
  }
  if (IDOS == NULL) {
    IDOS = (struct DOSIFace*) IExec->GetInterface((struct Library*) DOSBase, "main", 1, NULL);
    assert(IDOS != NULL);
  }
}

void __exit_DOS(void) {
  IExec->DropInterface((struct Interface*) IDOS);
  IExec->CloseLibrary((struct Library*) DOSBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
