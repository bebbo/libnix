/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* LowLevelBase[2] = { 0, "lowlevel.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/interrupts.h>
#include <utility/tagitem.h>
#include <devices/timer.h>
#include <libraries/lowlevel.h>

#include <interfaces/lowlevel.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * LowLevelBase = NULL;
__attribute__((weak)) struct LowLevelIFace* ILowLevel = NULL;

void __init_LowLevel(void) __attribute__((constructor));
void __exit_LowLevel(void) __attribute__((destructor));

void __init_LowLevel(void) {
  if (LowLevelBase == NULL) {
    LowLevelBase = (struct Library *) IExec->OpenLibrary("lowlevel.library", 0);
    assert(LowLevelBase != NULL);
  }
  if (ILowLevel == NULL) {
    ILowLevel = (struct LowLevelIFace*) IExec->GetInterface((struct Library*) LowLevelBase, "main", 1, NULL);
    assert(ILowLevel != NULL);
  }
}

void __exit_LowLevel(void) {
  IExec->DropInterface((struct Interface*) ILowLevel);
  IExec->CloseLibrary((struct Library*) LowLevelBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
