/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if 0 && defined (__libnix__)

#include <stabs.h>
void* TimerBase[2] = { 0, "timer.device" };
ADD2LIB(TimerBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <devices/timer.h>

#include <interfaces/timer.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Device * TimerBase = NULL;
__attribute__((weak)) struct TimerIFace* ITimer = NULL;

void __init_Timer(void) __attribute__((constructor));
void __exit_Timer(void) __attribute__((destructor));

void __init_Timer(void) {
  if (TimerBase == NULL) {
    TimerBase = (struct Device *) IExec->OpenLibrary("timer.device", 0);
    assert(TimerBase != NULL);
  }
  if (ITimer == NULL) {
    ITimer = (struct TimerIFace*) IExec->GetInterface((struct Library*) TimerBase, "main", 1, NULL);
    assert(ITimer != NULL);
  }
}

void __exit_Timer(void) {
  IExec->DropInterface((struct Interface*) ITimer);
  IExec->CloseLibrary((struct Library*) TimerBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
