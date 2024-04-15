#ifndef __AMISTDIO_H__
#define __AMISTDIO_H__

#define _STDIO_H

#include <stdarg.h>
#include <dos/dos.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REPLACE_STDIO
#define puts(a) amiputs(a)
#define gets(a,b) amigets(a, b)
#define fputs(a,f) FPuts(f, a)
#define fgets(a,l,f) FGets(f, a, l)
#define putchar amiputchar
#define fread(a,b,c,d) Read(d, a, b * c)
#define fwrite(a,b,c,d) Write(d, a, b * c)
#define printf(...) amiprintf(__VA_ARGS__)
#define fprintf(...) amifprintf(__VA_ARGS__)
#define vfprintf(...) amivfprintf(__VA_ARGS__)
#define stdin Input()
#define stdout Output()
#define stderr amistderr()
#define fflush(f) Flush(f)
#endif

extern int amiputs(char const * s);
extern int amigets(char * s, unsigned sz);
extern int amiprintf(char const * ftm,...);
extern int amifprintf(BPTR f, char const * ftm,...);
extern int amivfprintf(BPTR f, const char *fmt, va_list args);
extern void amiputchar(char c);
extern BPTR amistderr();

#ifdef __cplusplus
}
#endif

#endif // __AMISTDIO_H__
