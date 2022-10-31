/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* GetScreenModeBase[2] = { (void*)-1, "getscreenmode.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/getscreenmode.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GetScreenModeBase = NULL;
__attribute__((weak)) struct GetScreenModeIFace* IGetScreenMode = NULL;

void __init_GetScreenMode(void) __attribute__((constructor));
void __exit_GetScreenMode(void) __attribute__((destructor));

void __init_GetScreenMode(void) {
  if (GetScreenModeBase == NULL) {
    GetScreenModeBase = (struct Library *) IExec->OpenLibrary("getscreenmode.library", 0);
    assert(GetScreenModeBase != NULL);
  }
  if (IGetScreenMode == NULL) {
    IGetScreenMode = (struct GetScreenModeIFace*) IExec->GetInterface((struct Library*) GetScreenModeBase, "main", 1, NULL);
    assert(IGetScreenMode != NULL);
  }
}

void __exit_GetScreenMode(void) {
  IExec->DropInterface((struct Interface*) IGetScreenMode);
  IExec->CloseLibrary((struct Library*) GetScreenModeBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
