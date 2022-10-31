/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* KeymapBase[2] = { (void*)-1, "keymap.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <devices/inputevent.h>
#include <devices/keymap.h>

#include <interfaces/keymap.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * KeymapBase = NULL;
__attribute__((weak)) struct KeymapIFace* IKeymap = NULL;

void __init_Keymap(void) __attribute__((constructor));
void __exit_Keymap(void) __attribute__((destructor));

void __init_Keymap(void) {
  if (KeymapBase == NULL) {
    KeymapBase = (struct Library *) IExec->OpenLibrary("keymap.library", 0);
    assert(KeymapBase != NULL);
  }
  if (IKeymap == NULL) {
    IKeymap = (struct KeymapIFace*) IExec->GetInterface((struct Library*) KeymapBase, "main", 1, NULL);
    assert(IKeymap != NULL);
  }
}

void __exit_Keymap(void) {
  IExec->DropInterface((struct Interface*) IKeymap);
  IExec->CloseLibrary((struct Library*) KeymapBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
