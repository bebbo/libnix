/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* DrawListBase[2] = { 0, "drawlist.library" };
ADD2LIB(DrawListBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/drawlist.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * DrawListBase = NULL;
__attribute__((weak)) struct DrawListIFace* IDrawList = NULL;

void __init_DrawList(void) __attribute__((constructor));
void __exit_DrawList(void) __attribute__((destructor));

void __init_DrawList(void) {
  if (DrawListBase == NULL) {
    DrawListBase = (struct Library *) IExec->OpenLibrary("drawlist.library", 0);
    assert(DrawListBase != NULL);
  }
  if (IDrawList == NULL) {
    IDrawList = (struct DrawListIFace*) IExec->GetInterface((struct Library*) DrawListBase, "main", 1, NULL);
    assert(IDrawList != NULL);
  }
}

void __exit_DrawList(void) {
  IExec->DropInterface((struct Interface*) IDrawList);
  IExec->CloseLibrary((struct Library*) DrawListBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
