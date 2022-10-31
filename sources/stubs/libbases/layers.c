/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* LayersBase[2] = { (void*)-1, "layers.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <graphics/layers.h>
#include <graphics/clip.h>
#include <graphics/rastport.h>
#include <graphics/regions.h>

#include <interfaces/layers.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * LayersBase = NULL;
__attribute__((weak)) struct LayersIFace* ILayers = NULL;

void __init_Layers(void) __attribute__((constructor));
void __exit_Layers(void) __attribute__((destructor));

void __init_Layers(void) {
  if (LayersBase == NULL) {
    LayersBase = (struct Library *) IExec->OpenLibrary("layers.library", 0);
    assert(LayersBase != NULL);
  }
  if (ILayers == NULL) {
    ILayers = (struct LayersIFace*) IExec->GetInterface((struct Library*) LayersBase, "main", 1, NULL);
    assert(ILayers != NULL);
  }
}

void __exit_Layers(void) {
  IExec->DropInterface((struct Interface*) ILayers);
  IExec->CloseLibrary((struct Library*) LayersBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
