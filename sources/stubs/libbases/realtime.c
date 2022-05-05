/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* RealTimeBase = 0;
void ** __getRealTimeBase() { return &RealTimeBase; }
static void * const __init[2] = { __getRealTimeBase, "realtime.library"};
ADD2LIB(__init);
#else
void* RealTimeBase[2] = { 0, "realtime.library" };
ADD2LIB(RealTimeBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <libraries/realtime.h>
#include <utility/tagitem.h>

#include <interfaces/realtime.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct RealTimeBase * RealTimeBase = NULL;
__attribute__((weak)) struct RealTimeIFace* IRealTime = NULL;

void __init_RealTime(void) __attribute__((constructor));
void __exit_RealTime(void) __attribute__((destructor));

void __init_RealTime(void) {
  if (RealTimeBase == NULL) {
    RealTimeBase = (struct RealTimeBase *) IExec->OpenLibrary("realtime.library", 0);
    assert(RealTimeBase != NULL);
  }
  if (IRealTime == NULL) {
    IRealTime = (struct RealTimeIFace*) IExec->GetInterface((struct Library*) RealTimeBase, "main", 1, NULL);
    assert(IRealTime != NULL);
  }
}

void __exit_RealTime(void) {
  IExec->DropInterface((struct Interface*) IRealTime);
  IExec->CloseLibrary((struct Library*) RealTimeBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
