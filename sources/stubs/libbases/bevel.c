/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* BevelBase[2] = { (void*)-1, "gadgets/bevel.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/bevel.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * BevelBase = NULL;
__attribute__((weak)) struct BevelIFace* IBevel = NULL;

void __init_Bevel(void) __attribute__((constructor));
void __exit_Bevel(void) __attribute__((destructor));

void __init_Bevel(void) {
  if (BevelBase == NULL) {
    BevelBase = (struct Library *) IExec->OpenLibrary("bevel.library", 0);
    assert(BevelBase != NULL);
  }
  if (IBevel == NULL) {
    IBevel = (struct BevelIFace*) IExec->GetInterface((struct Library*) BevelBase, "main", 1, NULL);
    assert(IBevel != NULL);
  }
}

void __exit_Bevel(void) {
  IExec->DropInterface((struct Interface*) IBevel);
  IExec->CloseLibrary((struct Library*) BevelBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
