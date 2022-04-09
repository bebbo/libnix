/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* KeymapBase = 0;
void ** __getKeymapBase() { return &KeymapBase; }
static void * __init[2] = { __getKeymapBase, "keymap.library"};
ADD2LIB(__init);
#else
void* KeymapBase[2] = { 0, "keymap.library" };
ADD2LIB(KeymapBase);
#endif

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
