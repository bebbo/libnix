#include <amistdio.h>
#include <string.h>
#include <proto/dos.h>
#include <proto/exec.h>

// the linker inserts this id behind the idString
static char id[3] = {0x0b, 0xeb, 0xb0};
void *dlopen (__const char *__file, int __mode) {
	struct Library * lib = OldOpenLibrary(__file);
	if (lib) {
		// only one exported function -> neg size == 32, magic marker "bebb0" behind id string!
		if (32 != lib->lib_NegSize || !lib->lib_IdString || memcmp(id, lib->lib_IdString + strlen(lib->lib_IdString) + 1, 3)) {
#ifndef __KICK13__
			Printf("%s is not suitable for dlopen", __file);
#endif
			CloseLibrary(lib);
			lib = 0;
		}
	}
	return lib;
}

/* Unmap and close a shared object opened by `dlopen'.
   The handle cannot be used again after calling `dlclose'.  */
int dlclose (void *__handle) {
	if (!__handle)
		return -1;
	CloseLibrary((struct Library *)__handle);
	return 0;
}

/* Find the run-time address in the shared object HANDLE refers to
   of the symbol called NAME with VERSION.  */
void *dlvsym (void *__restrict __handle,
		     __const char *__restrict __name,
		     __const char *__restrict __version) {
	if (!__handle)
		return 0;

	void * r = 0;
	static void const * p[3];
	p[0] = __name;
	p[1] = &r;

	register void * a0 asm("a0") = p;
	register struct Library * a6 asm("a6") = (struct Library *)__handle;
	asm volatile("jsr (-30,a6)" : "=m"(r) : "r"(a0), "r"(a6));

	return r;
}

/* Find the run-time address in the shared object HANDLE refers to
   of the symbol called NAME.  */
void *dlsym (void *__restrict __handle,
		    __const char *__restrict __name) {
	return dlvsym(__handle, __name, 0);
}
