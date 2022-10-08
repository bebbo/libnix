/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* WorkbenchBase[2] = { 0, "workbench.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <dos/dos.h>
#include <workbench/workbench.h>
#include <intuition/intuition.h>
#include <utility/tagitem.h>

#include <interfaces/wb.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * WorkbenchBase = NULL;
__attribute__((weak)) struct WorkbenchIFace* IWorkbench = NULL;

void __init_Workbench(void) __attribute__((constructor));
void __exit_Workbench(void) __attribute__((destructor));

void __init_Workbench(void) {
  if (WorkbenchBase == NULL) {
    WorkbenchBase = (struct Library *) IExec->OpenLibrary("workbench.library", 0);
    assert(WorkbenchBase != NULL);
  }
  if (IWorkbench == NULL) {
    IWorkbench = (struct WorkbenchIFace*) IExec->GetInterface((struct Library*) WorkbenchBase, "main", 1, NULL);
    assert(IWorkbench != NULL);
  }
}

void __exit_Workbench(void) {
  IExec->DropInterface((struct Interface*) IWorkbench);
  IExec->CloseLibrary((struct Library*) WorkbenchBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
