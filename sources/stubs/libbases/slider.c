/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* SliderBase = 0;
void ** __getSliderBase() { return &SliderBase; }
static void * __init[2] = { __getSliderBase, "slider.library"};
ADD2LIB(__init);
#else
void* SliderBase[2] = { 0, "slider.library" };
ADD2LIB(SliderBase);
#endif

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
