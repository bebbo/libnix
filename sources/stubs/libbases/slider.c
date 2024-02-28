/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* SliderBase[2] = { (void*)-1, "gadgets/slider.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/slider.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * SliderBase = NULL;
__attribute__((weak)) struct SliderIFace* ISlider = NULL;

void __init_Slider(void) __attribute__((constructor));
void __exit_Slider(void) __attribute__((destructor));

void __init_Slider(void) {
  if (SliderBase == NULL) {
    SliderBase = (struct Library *) IExec->OpenLibrary("slider.library", 0);
    assert(SliderBase != NULL);
  }
  if (ISlider == NULL) {
    ISlider = (struct SliderIFace*) IExec->GetInterface((struct Library*) SliderBase, "main", 1, NULL);
    assert(ISlider != NULL);
  }
}

void __exit_Slider(void) {
  IExec->DropInterface((struct Interface*) ISlider);
  IExec->CloseLibrary((struct Library*) SliderBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
