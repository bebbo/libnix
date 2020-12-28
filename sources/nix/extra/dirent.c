#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <exec/memory.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <strsup.h>

#ifdef __KICK13__
#include <exec/execbase.h>
#include <dos/dosextens.h>

extern struct ExecBase * SysBase;

extern void * AllocVec(unsigned, int);
extern void FreeVec(void *);

/**
 * Fill the ead and
 */
static unsigned fill(struct FileInfoBlock * fib, STRPTR buffer, unsigned size) {
	/* next + type + nameptr + name + \0 */
	unsigned needed = 4 + 4 + 4 + strlen(fib->fib_FileName) + 1;
	if (needed > size)
		return 0;

	{
		struct ExAllData * ead = (struct ExAllData *)buffer;
		ead->ed_Next = 0;
		strcpy(ead->ed_Name = (UBYTE *)buffer + 12, fib->fib_FileName);
		ead->ed_Type = fib->fib_EntryType;
		return needed;
	}
}

LONG
ExAll (BPTR lock, STRPTR buffer, LONG size, LONG type, struct ExAllControl *control) {
	struct FileInfoBlock *fib, *fib1, *fib2;
	struct ExAllData *ead, *next;
	STRPTR nextBuffer;
	unsigned count, needed;

	count = 0;
	ead = NULL;
	// alternate buffers
	fib1 = (struct FileInfoBlock *)(1 + control);
	fib2 = fib1 + 1;
	fib = (struct FileInfoBlock *)control->eac_LastKey;

	for(;;) {
		int r;
		if (fib == NULL) {
			fib = fib1;
			r = Examine(lock, fib);
		} else {
			fib = (fib == fib1) ? fib2 : fib1;
			r = ExNext(lock, fib);
		}
		if (!r)
			break;

		needed = fill(fib, buffer, size);
		if (!needed)
			break;

		/** mark fib read successful. */
		control->eac_LastKey = (ULONG)fib;

		next = (struct ExAllData *)buffer;
		if (ead != NULL) {
			ead->ed_Next = next;
			ead = next;
		}
		size -= needed;
		buffer += needed;
		++count;
	}
	control->eac_Entries = count;
	return ead != NULL;
}
#endif

DIR* opendir(const char *dirname) {
	DIR *dirp;

	if ((dirp = (DIR*) AllocVec(sizeof(DIR), MEMF_PUBLIC | MEMF_CLEAR)) != NULL) {
		if ((dirp->d_lock = (Lock((STRPTR )dirname, SHARED_LOCK))) != 0ul) {
//			dirp->d_count = 0;
			dirp->d_more = DOSTRUE;
			if ((dirp->d_eac = AllocVec(sizeof(struct ExAllControl)
#ifdef __KICK13__
					+ sizeof(struct FileInfoBlock) * 2 /* also alloc two FileInfoBlocks. */
#endif
					,MEMF_PUBLIC | MEMF_CLEAR)) != NULL) {
#if 0
				dirp->d_eac->eac_LastKey=0;
				dirp->d_eac->eac_MatchString=NULL;
				dirp->d_eac->eac_MatchFunc=NULL;
#endif
				if (Examine(dirp->d_lock, &dirp->d_info)) {
					if (dirp->d_info.fib_EntryType >= 0)
						return dirp;
				}
				FreeVec(dirp->d_eac);
			}
			UnLock(dirp->d_lock);
		}
		FreeVec(dirp);
		dirp = NULL;
	}
	return dirp;
}

struct dirent* readdir(DIR *dirp) {
	struct dirent *result;

	if (!dirp->d_count && dirp->d_more != DOSFALSE) {
		dirp->d_more = ExAll(dirp->d_lock, (APTR)&dirp->d_ead[0], sizeof(dirp->d_ead), ED_TYPE, dirp->d_eac);
		dirp->current = (struct ExAllData*) &dirp->d_ead[0];
		dirp->d_count = dirp->d_eac->eac_Entries;
	}

	result = NULL;
	if (dirp->d_count) {
		dirp->dd_ent.d_fileno = dirp->dd_ent.d_reclen = 1;
		strcpy((char*) dirp->dd_ent.d_name, (const char*) dirp->current->ed_Name);
		dirp->dd_ent.d_namlen = strlen((const char*) dirp->dd_ent.d_name);
		dirp->dd_ent.d_type = (dirp->current->ed_Type < 0 ? DT_REG : (dirp->current->ed_Type != ST_SOFTLINK ? DT_DIR : DT_LNK));
		dirp->current = dirp->current->ed_Next;
		dirp->d_count--;
		result = &dirp->dd_ent;
	}

	return result;
}

void rewinddir(DIR *dirp) {
#ifndef __KICK13__
	if (dirp->d_more != DOSFALSE)
		do {
			dirp->d_more = ExAll(dirp->d_lock, (APTR)&dirp->d_ead[0], sizeof(dirp->d_ead), ED_TYPE, dirp->d_eac);
		} while (dirp->d_more != DOSFALSE);
#endif
	dirp->d_count = 0;
	dirp->d_more = DOSTRUE;
	dirp->d_eac->eac_LastKey = 0;
}

int closedir(DIR *dirp) {
	rewinddir(dirp);
	FreeVec(dirp->d_eac);
	UnLock(dirp->d_lock);
	FreeVec(dirp);
	return 0;
}
