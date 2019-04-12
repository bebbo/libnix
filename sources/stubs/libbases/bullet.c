/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* BulletBase[2] = { 0, "bullet.library" };
ADD2LIB(BulletBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <utility/tagitem.h>
#include <diskfont/glyph.h>

#include <interfaces/bullet.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * BulletBase = NULL;
__attribute__((weak)) struct BulletIFace* IBullet = NULL;

void __init_Bullet(void) __attribute__((constructor));
void __exit_Bullet(void) __attribute__((destructor));

void __init_Bullet(void) {
  if (BulletBase == NULL) {
    BulletBase = (struct Library *) IExec->OpenLibrary("bullet.library", 0);
    assert(BulletBase != NULL);
  }
  if (IBullet == NULL) {
    IBullet = (struct BulletIFace*) IExec->GetInterface((struct Library*) BulletBase, "main", 1, NULL);
    assert(IBullet != NULL);
  }
}

void __exit_Bullet(void) {
  IExec->DropInterface((struct Interface*) IBullet);
  IExec->CloseLibrary((struct Library*) BulletBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
