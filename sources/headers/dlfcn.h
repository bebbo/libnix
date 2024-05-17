#ifndef __DLFCN_H__
#define __DLFCN_H__

/*
 * To be used withlibraries created with -noixemul -shared
 */

void * __stdargs dlopen (__const char *__file, int __mode);
int __stdargs dlclose (void *__handle);
void * __stdargs dlvsym (void *__restrict __handle,
		     __const char *__restrict __name,
		     __const char *__restrict __version);
void * __stdargs dlsym (void *__restrict __handle,
		    __const char *__restrict __name);

#endif //__DLFCN_H__
