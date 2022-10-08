/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* MiscBase[2] = { 0, "misc.resource" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/misc.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * MiscBase = NULL;
__attribute__((weak)) struct MiscIFace* IMisc = NULL;

void __init_Misc(void) __attribute__((constructor));
void __exit_Misc(void) __attribute__((destructor));

void __init_Misc(void) {
  if (MiscBase == NULL) {
    MiscBase = (struct Library *) IExec->OpenLibrary("misc.resource", 0);
    assert(MiscBase != NULL);
  }
  if (IMisc == NULL) {
    IMisc = (struct MiscIFace*) IExec->GetInterface((struct Library*) MiscBase, "main", 1, NULL);
    assert(IMisc != NULL);
  }
}

void __exit_Misc(void) {
  IExec->DropInterface((struct Interface*) IMisc);
  IExec->CloseLibrary((struct Library*) MiscBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
