/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* BitMapBase[2] = { (void*)-1, "bitmap.library" };

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
