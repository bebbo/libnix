/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* GfxBase[2] = { 0, "graphics.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <graphics/gfx.h>
#include <graphics/displayinfo.h>
#include <graphics/gels.h>
#include <graphics/rastport.h>
#include <graphics/view.h>
#include <graphics/copper.h>
#include <graphics/clip.h>
#include <graphics/regions.h>
#include <graphics/sprite.h>
#include <graphics/text.h>
#include <graphics/scale.h>
#include <hardware/blit.h>
#include <exec/types.h>
#include <utility/tagitem.h>

#include <interfaces/graphics.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct GfxBase * GfxBase = NULL;
__attribute__((weak)) struct GfxIFace* IGfx = NULL;

void __init_Gfx(void) __attribute__((constructor));
void __exit_Gfx(void) __attribute__((destructor));

void __init_Gfx(void) {
  if (GfxBase == NULL) {
    GfxBase = (struct GfxBase *) IExec->OpenLibrary("graphics.library", 0);
    assert(GfxBase != NULL);
  }
  if (IGfx == NULL) {
    IGfx = (struct GfxIFace*) IExec->GetInterface((struct Library*) GfxBase, "main", 1, NULL);
    assert(IGfx != NULL);
  }
}

void __exit_Gfx(void) {
  IExec->DropInterface((struct Interface*) IGfx);
  IExec->CloseLibrary((struct Library*) GfxBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
