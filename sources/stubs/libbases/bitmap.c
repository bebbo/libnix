/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* BitMapBase[2] = { 0, "bitmap.library" };
ADD2LIB(BitMapBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/bitmap.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * BitMapBase = NULL;
__attribute__((weak)) struct BitMapIFace* IBitMap = NULL;

void __init_BitMap(void) __attribute__((constructor));
void __exit_BitMap(void) __attribute__((destructor));

void __init_BitMap(void) {
  if (BitMapBase == NULL) {
    BitMapBase = (struct Library *) IExec->OpenLibrary("bitmap.library", 0);
    assert(BitMapBase != NULL);
  }
  if (IBitMap == NULL) {
    IBitMap = (struct BitMapIFace*) IExec->GetInterface((struct Library*) BitMapBase, "main", 1, NULL);
    assert(IBitMap != NULL);
  }
}

void __exit_BitMap(void) {
  IExec->DropInterface((struct Interface*) IBitMap);
  IExec->CloseLibrary((struct Library*) BitMapBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
