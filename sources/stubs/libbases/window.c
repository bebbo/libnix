/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* WindowBase = 0;
void ** __getWindowBase() { return &WindowBase; }
static void * __init[2] = { __getWindowBase, "window.library"};
ADD2LIB(__init);
#else
void* WindowBase[2] = { 0, "window.library" };
ADD2LIB(WindowBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/window.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * WindowBase = NULL;
__attribute__((weak)) struct WindowIFace* IWindow = NULL;

void __init_Window(void) __attribute__((constructor));
void __exit_Window(void) __attribute__((destructor));

void __init_Window(void) {
  if (WindowBase == NULL) {
    WindowBase = (struct Library *) IExec->OpenLibrary("window.library", 0);
    assert(WindowBase != NULL);
  }
  if (IWindow == NULL) {
    IWindow = (struct WindowIFace*) IExec->GetInterface((struct Library*) WindowBase, "main", 1, NULL);
    assert(IWindow != NULL);
  }
}

void __exit_Window(void) {
  IExec->DropInterface((struct Interface*) IWindow);
  IExec->CloseLibrary((struct Library*) WindowBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
