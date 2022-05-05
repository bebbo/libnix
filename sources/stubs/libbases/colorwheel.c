/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* ColorWheelBase = 0;
void ** __getColorWheelBase() { return &ColorWheelBase; }
static void * const __init[2] = { __getColorWheelBase, "colorwheel.library"};
ADD2LIB(__init);
#else
void* ColorWheelBase[2] = { 0, "colorwheel.library" };
ADD2LIB(ColorWheelBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <gadgets/colorwheel.h>

#include <interfaces/colorwheel.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ColorWheelBase = NULL;
__attribute__((weak)) struct ColorWheelIFace* IColorWheel = NULL;

void __init_ColorWheel(void) __attribute__((constructor));
void __exit_ColorWheel(void) __attribute__((destructor));

void __init_ColorWheel(void) {
  if (ColorWheelBase == NULL) {
    ColorWheelBase = (struct Library *) IExec->OpenLibrary("colorwheel.library", 0);
    assert(ColorWheelBase != NULL);
  }
  if (IColorWheel == NULL) {
    IColorWheel = (struct ColorWheelIFace*) IExec->GetInterface((struct Library*) ColorWheelBase, "main", 1, NULL);
    assert(IColorWheel != NULL);
  }
}

void __exit_ColorWheel(void) {
  IExec->DropInterface((struct Interface*) IColorWheel);
  IExec->CloseLibrary((struct Library*) ColorWheelBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
