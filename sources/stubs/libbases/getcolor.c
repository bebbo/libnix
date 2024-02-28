/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* GetColorBase[2] = { (void*)-1, "gadgets/getcolor.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/libraries.h>
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <gadgets/getcolor.h>

#include <interfaces/getcolor.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GetColorBase = NULL;
__attribute__((weak)) struct GetColorIFace* IGetColor = NULL;

void __init_GetColor(void) __attribute__((constructor));
void __exit_GetColor(void) __attribute__((destructor));

void __init_GetColor(void) {
  if (GetColorBase == NULL) {
    GetColorBase = (struct Library *) IExec->OpenLibrary("getcolor.gadget", 0);
    assert(GetColorBase != NULL);
  }
  if (IGetColor == NULL) {
    IGetColor = (struct GetColorIFace*) IExec->GetInterface((struct Library*) GetColorBase, "main", 1, NULL);
    assert(IGetColor != NULL);
  }
}

void __exit_GetColor(void) {
  IExec->DropInterface((struct Interface*) IGetColor);
  IExec->CloseLibrary((struct Library*) GetColorBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
