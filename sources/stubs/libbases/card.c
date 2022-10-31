/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* CardResource[2] = { (void*)-1, "card.resource" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/resident.h>
#include <resources/card.h>

#include <interfaces/card.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * CardResource = NULL;
__attribute__((weak)) struct CardResourceIFace* ICardResource = NULL;

void __init_CardResource(void) __attribute__((constructor));
void __exit_CardResource(void) __attribute__((destructor));

void __init_CardResource(void) {
  if (CardResource == NULL) {
    CardResource = (struct Library *) IExec->OpenLibrary("card.resource", 0);
    assert(CardResource != NULL);
  }
  if (ICardResource == NULL) {
    ICardResource = (struct CardResourceIFace*) IExec->GetInterface((struct Library*) CardResource, "main", 1, NULL);
    assert(ICardResource != NULL);
  }
}

void __exit_CardResource(void) {
  IExec->DropInterface((struct Interface*) ICardResource);
  IExec->CloseLibrary((struct Library*) CardResource);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
