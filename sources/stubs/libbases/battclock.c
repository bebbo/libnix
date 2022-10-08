/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* BattClockBase[2] = { 0, "battclock.resource" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/battclock.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * BattClockBase = NULL;
__attribute__((weak)) struct BattClockIFace* IBattClock = NULL;

void __init_BattClock(void) __attribute__((constructor));
void __exit_BattClock(void) __attribute__((destructor));

void __init_BattClock(void) {
  if (BattClockBase == NULL) {
    BattClockBase = (struct Library *) IExec->OpenLibrary("battclock.resource", 0);
    assert(BattClockBase != NULL);
  }
  if (IBattClock == NULL) {
    IBattClock = (struct BattClockIFace*) IExec->GetInterface((struct Library*) BattClockBase, "main", 1, NULL);
    assert(IBattClock != NULL);
  }
}

void __exit_BattClock(void) {
  IExec->DropInterface((struct Interface*) IBattClock);
  IExec->CloseLibrary((struct Library*) BattClockBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
