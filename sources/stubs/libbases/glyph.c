/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* GlyphBase[2] = { 0, "glyph.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/glyph.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GlyphBase = NULL;
__attribute__((weak)) struct GlyphIFace* IGlyph = NULL;

void __init_Glyph(void) __attribute__((constructor));
void __exit_Glyph(void) __attribute__((destructor));

void __init_Glyph(void) {
  if (GlyphBase == NULL) {
    GlyphBase = (struct Library *) IExec->OpenLibrary("glyph.library", 0);
    assert(GlyphBase != NULL);
  }
  if (IGlyph == NULL) {
    IGlyph = (struct GlyphIFace*) IExec->GetInterface((struct Library*) GlyphBase, "main", 1, NULL);
    assert(IGlyph != NULL);
  }
}

void __exit_Glyph(void) {
  IExec->DropInterface((struct Interface*) IGlyph);
  IExec->CloseLibrary((struct Library*) GlyphBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
