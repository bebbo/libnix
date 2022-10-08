/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* GetFontBase[2] = { 0, "getfont.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/getfont.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GetFontBase = NULL;
__attribute__((weak)) struct GetFontIFace* IGetFont = NULL;

void __init_GetFont(void) __attribute__((constructor));
void __exit_GetFont(void) __attribute__((destructor));

void __init_GetFont(void) {
  if (GetFontBase == NULL) {
    GetFontBase = (struct Library *) IExec->OpenLibrary("getfont.library", 0);
    assert(GetFontBase != NULL);
  }
  if (IGetFont == NULL) {
    IGetFont = (struct GetFontIFace*) IExec->GetInterface((struct Library*) GetFontBase, "main", 1, NULL);
    assert(IGetFont != NULL);
  }
}

void __exit_GetFont(void) {
  IExec->DropInterface((struct Interface*) IGetFont);
  IExec->CloseLibrary((struct Library*) GetFontBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
