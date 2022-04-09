/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* SpaceBase = 0;
void ** __getSpaceBase() { return &SpaceBase; }
static void * __init[2] = { __getSpaceBase, "space.library"};
ADD2LIB(__init);
#else
void* SpaceBase[2] = { 0, "space.library" };
ADD2LIB(SpaceBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/space.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * SpaceBase = NULL;
__attribute__((weak)) struct SpaceIFace* ISpace = NULL;

void __init_Space(void) __attribute__((constructor));
void __exit_Space(void) __attribute__((destructor));

void __init_Space(void) {
  if (SpaceBase == NULL) {
    SpaceBase = (struct Library *) IExec->OpenLibrary("space.library", 0);
    assert(SpaceBase != NULL);
  }
  if (ISpace == NULL) {
    ISpace = (struct SpaceIFace*) IExec->GetInterface((struct Library*) SpaceBase, "main", 1, NULL);
    assert(ISpace != NULL);
  }
}

void __exit_Space(void) {
  IExec->DropInterface((struct Interface*) ISpace);
  IExec->CloseLibrary((struct Library*) SpaceBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
