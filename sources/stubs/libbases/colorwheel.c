/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* ColorWheelBase[2] = { (void*)-1, "colorwheel.library" };

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
