#include <amistdio.h>
#include <string.h>
#include <exec/execbase.h>
#include <exec/resident.h>
#include <proto/dos.h>
#include <proto/exec.h>

extern void exit(int);

#pragma GCC push_options
#pragma GCC optimize ("-Os")
#pragma GCC optimize ("-fno-toplevel-reorder")
#pragma GCC optimize ("-fomit-frame-pointer")

// make cli happy
long __safefail(void) {
	return -1;
}

// library header stuff - kind of forward decls - results in a rom tag directly behind the cli-do-nothing-function.
// the real values are defined at the end.
const struct Resident __RomTag;

// place into data segment -> init with zero
__attribute__((section(".data")))
 struct Library __lib = { 0 };
// track all instantiated libs, the lib_Sum fields is used to track the opening Task
__attribute__((section(".data")))
 struct List __libList = { 0 };

const char __libName[64] = { 0 };
const APTR __FuncTable__[];

struct ExecBase *SysBase = 0;
struct Library *__theMasterLib = 0;
long __segList = 0;
long __initFailed = 0;

// needed per instance
unsigned short __cleanupflag = 0;

__attribute__((section(".list___INIT_LIST__")))
const int __INIT_LIST__[1] = { 0 };
__attribute__((section(".list___EXIT_LIST__")))
const int __EXIT_LIST__[1] = { 0 };

__attribute__((section(".dlist___LIB_LIST__")))
int __LIB_LIST__[1] = { 0 };

__attribute__((section(".list___CTOR_LIST__")))
const int __CTOR_LIST__[1] = { 0 };

__attribute__((section(".list___DTOR_LIST__")))
const int __DTOR_LIST__[1] = { 0 };

// the section for the exported functions
__attribute__((section(".dlist_so_export")))
long __so_xlib_export[1] = { 0 };

__attribute__((section(".end_of_lists")))
const int __ZZZ_LIST__[1] = { 0 };
__attribute__((section(".end_of_dlists")))
int __ZZZ_DLIST__[1] = { 0 };

long __LibClose(struct Library *childLib asm("a6"));
void __callfuncs(const int *p asm("a2"), unsigned short prioo asm("d2"));

void __restore_a4() {
	asm volatile("lea 32766(a6),a4");
}

static inline VOID __NewList(struct List *_NewList_list) {
	_NewList_list->lh_TailPred = (struct Node*) _NewList_list;
	_NewList_list->lh_Head = (struct Node*) &_NewList_list->lh_Tail;
	_NewList_list->lh_Tail = 0;
}

// init the library. defer real init stuff to LibOpen!
APTR __LibInit(long __segListIn asm("a0"), struct Library *_masterlib asm("d0"), struct ExecBase *__sysBase asm("a6")) {
	// get access to the data
	register long *a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("lea	___a4_init,%0;\n" : "=r"(a4));

	struct Library *masterlib = _masterlib;

#if 0
	{
	struct DosLibrary * DOSBase = (struct DosLibrary *)OldOpenLibrary("dos.library");
	Printf("neg=%ld, pos=%ld\n", masterlib->lib_NegSize, masterlib->lib_PosSize);
	Flush(Output());
	CloseLibrary(&DOSBase->dl_lib);
	}
#endif

	/* setup private data */
	SysBase = __sysBase;
	__theMasterLib = masterlib;
	__segList = __segListIn;

//	/* set up header data */
//	masterlib->lib_Node.ln_Type = NT_LIBRARY;
//	masterlib->lib_Node.ln_Name = (char*) __libName;
//	masterlib->lib_Flags = LIBF_CHANGED | LIBF_SUMUSED;
//	masterlib->lib_Version = __lib.lib_Version;
//	masterlib->lib_Revision = __lib.lib_Revision;
//	masterlib->lib_IdString = (char*) __libName + strlen((char*) __libName) + 1;

	CopyMem(masterlib, &__lib, sizeof(__lib));

	__NewList(&__libList);

	/* this will be added to SysBase->LibList or NULL (init error) */
	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
	return masterlib;
}

// bye bye library
long __LibExpunge(struct Library *_masterlib asm("a6")) {
	register long *a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("lea	___a4_init,%0;\n" : "=r"(a4));

	struct Library *masterlib = _masterlib;

	/* set delayed expunge flag */
	masterlib->lib_Flags |= LIBF_DELEXP;

	long sl = __segList;
	/* still in use? */
	if (!masterlib->lib_OpenCnt) {
		/* remove lib from SysBase->LibList */
		Remove(&masterlib->lib_Node);

		// free the allocated ram of the lib's struct
		int neg = masterlib->lib_NegSize;
		FreeMem((-neg + (char* )masterlib), neg + masterlib->lib_PosSize);
	}
	/* return the seglist for UnLoadSeg() */
	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
	return sl;
}

// open the library
struct Library*
__LibOpen(struct Library *_masterlib asm("a6")) {
	register long *a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("lea	___a4_init,%0;\n" : "=r"(a4));

	struct Library *masterlib = _masterlib;

	// Forbid is on - increase the counter
	++masterlib->lib_OpenCnt;

	/* clear delayed expunge flag */
	masterlib->lib_Flags &= ~LIBF_DELEXP;

	struct Task *task = SysBase->ThisTask;
	// search the List if the task already opened this library.
	for (struct Node *node = __libList.lh_Head; node != (struct Node*) &__libList.lh_Tail; node = node->ln_Succ) {
		struct Library *childLib = (struct Library*) node->ln_Name;
		if (childLib->lib_Sum == (ULONG) task) {
			++childLib->lib_OpenCnt;
			asm volatile("move.l	(a7)+,a4" : "=r"(a4));
			return childLib;
		}
	}

	// get memory per lib
	unsigned sz = masterlib->lib_PosSize + masterlib->lib_NegSize;
	char *to = (char*) AllocVec(sz, MEMF_PUBLIC);

	// copy jump table
	CopyMemQuick(((char* )masterlib) - masterlib->lib_NegSize, to, masterlib->lib_NegSize);

	to += masterlib->lib_NegSize;

	// copy data segment
	CopyMemQuick(&__lib, to, masterlib->lib_PosSize);

	struct Library *childLib = (struct Library*) to;
	childLib->lib_Sum = (ULONG) task;
	childLib->lib_OpenCnt = 1;
	AddHead(&__libList, (struct Node* )&childLib[1]); // the child's libList as node...

	// apply datadata relocs
	long *p;
	asm volatile("lea	___datadata_relocs,%0" : "=r"(p));
	asm volatile("lea	__etext,%0" : "=r"(a4));
	if (p < a4) {
		long count = *p++;
		long diff = (char*) &__lib - to;
		while (count > 0) {
			long *t = (long*) *p++;
			*t -= diff;
			--count;
		}
	}

	// reload a4 for the child library
	asm volatile(
			"move.l	%1,%0;\n"
			"add.l #32766,%0;\n"
			: "=r"(a4) : "r"(childLib));

	// run init
	__callfuncs(&__INIT_LIST__[1], 0);

	if (__initFailed) {
		__LibClose(childLib);
		childLib = 0;
	}

	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
	return childLib;
}

// close the library
long __LibClose(struct Library *childLib asm("a6")) {
	register long *a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("lea	32766(a6),%0;\n" : "=r"(a4));

	Forbid();
	--__theMasterLib->lib_OpenCnt;
	// still in user
	long r = 0;
	if (!--childLib->lib_OpenCnt) {
		// disable forbid during cleanup
		Permit();

		// run exit
		__cleanupflag ^= -1;
		__callfuncs(&__EXIT_LIST__[1], -1);

		// forbid again
		Forbid();
		// free the instance
		Remove((struct Node* )&childLib[1]);
		FreeVec(((char* )childLib) - childLib->lib_NegSize);

		/* one less user */
		if (!__theMasterLib->lib_OpenCnt && (__theMasterLib->lib_Flags & LIBF_DELEXP))
			r = __LibExpunge(__theMasterLib);

	}
	Permit();
	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
	return r;
}

__regargs
void __so_xlib_init(char const *name, void **to) {
	long *p = &__so_xlib_export[1];
	while (*p) {
		char const *oname = (char const*) *p++;
//		{
//		struct DosLibrary * DOSBase = (struct DosLibrary *)OldOpenLibrary("dos.library");
//		Printf("%s==%s\n", name, oname);
//		Flush(Output());
//		CloseLibrary(&DOSBase->dl_lib);
//		}
		void *v = (void*) *p++;
		if (0 == strcmp(name, oname)) {
			*to = v;
			break;
		}
	}
	if (!*to)
		exit(10);
}

void __ResolveSymbols(long *p asm("a0"), struct Library *childLib asm("a6")) {
	register long *a4 asm("a4");
	asm volatile("move.l	a4,-(a7)" :: "r"(a4));
	asm volatile("lea	32766(a6),%0;\n" : "=r"(a4));
	while (*p) {
		char const *name = (char const*) *p++;
		void **to = (void**) *p++;
		__so_xlib_init(name, to);
	}
	asm volatile("move.l	(a7)+,a4" : "=r"(a4));
}

extern void __initlibraries();
extern void __initcpp();

// the function table
const APTR __FuncTable__[] = { __LibOpen, __LibClose, __LibExpunge, NULL, __ResolveSymbols, (APTR) -1,
// link __initlibraries and __initcpp behind end marker^
		__initlibraries, __initcpp };

// the libraries init table
extern long __data_size;
const APTR __InitTab[4] = { (APTR) &__data_size, (APTR) &__FuncTable__[0], (APTR) NULL, (APTR) &__LibInit };

// that's what the library loader is looking for: the rom tag with references to the remaining data.
const struct Resident __RomTag = { RTC_MATCHWORD, (struct Resident*) &__RomTag, (struct Resident*) &__RomTag + 1,
RTF_AUTOINIT, 1,
NT_LIBRARY, 0, (char*) __libName,
(char*) __libName, // the linker will fix this!
(APTR) &__InitTab };

void __callfuncs(const int *q asm("a2"), unsigned short order asm("d2")) {
	for (;;) {
		const int *p = q;
		unsigned short curprio = __cleanupflag;
		unsigned short nextprio = -1;

		while (*p) {
			unsigned short prio = *((unsigned short*) p + 3) ^ order;

			// invoke
			if (prio == curprio)
				((void (*)(void)) *p)();

			// update next prio
			if (prio < nextprio && prio > curprio)
				nextprio = prio;

			p += 2;
		}
		if (nextprio == curprio)
			break;

		__cleanupflag = nextprio;
	}
}

// just in case callfunc calls something which calls exit
void exit(int x) {
	__initFailed = x;
}
