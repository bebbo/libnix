#ifndef STDIO_H
#define STDIO_H
#include <stdarg.h>
#include <string.h>
#include <exec/lists.h>
#include <exec/nodes.h>

/* Adjusted to be compatible with the bsd headers
 * (At least for normal ANSI stuff)
 * Member names are not the same, but they need not be :-)
 */

typedef long fpos_t;

typedef struct __FILE
{
  unsigned char *p;	  /* pointer to actual character */
  int incount;		  /* Bytes left in buffer for reading, writemode: 0 */
  int outcount; 	  /* Space left in buffer for writing + fp->linebufsize,
			   * readmode: 0
			   */
  short flags;		  /* Some flags: 0x01 line buffered
			   *		 0x02 unbuffered
			   *		 0x04 read mode
			   *		 0x08 write mode
			   *		 0x20 EOF read
			   *		 0x40 error encountered
			   *		 0x80 buffer malloc'ed by library
			   *		0x200 sprintf/sscanf buffer
			   */
  short file;		  /* The filehandle */
  unsigned char *buffer;  /* original buffer pointer */
  int bufsize;		  /* size of the buffer */
  int linebufsize;	  /* 0 full buffered
			   * -bufsize line buffered&write mode
			   * readmode: undefined */
/* from this point on not binary compatible to bsd headers */
  unsigned char unget[4]; /* ungetc buffer 4 bytes necessary (for -Na*)
			   * ANSI requires 3 bytes (for -.*), so one more
			   * doesn't matter
			   */
  unsigned char *tmpp;	  /* Stored p if ungetc pending, otherwise NULL */
  int tmpinc;		  /* Stored incount if ungetc pending, otherwise undefined */
  long tmpdir;		  /* lock to directory if temporary file */
  char *name;		  /* filename if temporary file */
} FILE;

#ifndef NULL
#define NULL ((void *)0l)
#endif
#define BUFSIZ 1024
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

extern FILE *fopen(const char *filename,const char *mode);
extern FILE *freopen(const char *filename,const char *mode,FILE *stream);
extern int fclose(FILE *stream);
extern int fgetc(FILE *stream);
extern int fputc(int c,FILE *stream);
extern int ungetc(int c,FILE *stream);
extern int sprintf(char *s,const char *format,...);
extern int sscanf(const char *s,const char *format,...);
extern int vprintf(const char *format,va_list args);
extern int vsprintf(char *s,const char *format,va_list args);
extern int vfprintf(FILE *stream,const char *format,va_list args);
extern int vscanf(const char *format,va_list args);
extern int vsscanf(const char *s,const char *format,va_list args);
extern int vfscanf(FILE *stream,const char *format,va_list args);
extern int snprintf(char *s,size_t size,const char *format,...);
extern int vsnprintf(char *s,size_t size,const char *format,va_list args);
extern int fseek(FILE *stream,long int offset,int whence);
extern int fputs(const char *s,FILE *stream);
extern long int ftell(FILE *stream);
extern int setvbuf(FILE *stream,char *buf,int mode,unsigned long size);
extern int fread(void *,unsigned long,unsigned long,FILE *);
extern int fwrite(const void *,unsigned long,unsigned long,FILE *);

/* More bsd headers compatibility */

extern int __swbuf(int c,FILE *stream);
extern int __srget(FILE *stream);
extern FILE **__sF; /* Standard I/O streams */
#define stdin  (__sF[0]) /* Other streams are not in __sF */
#define stdout (__sF[1])
#define stderr (__sF[2])

/* Be careful: We have side effects and use incount in __srget -
	       must use comma-operator */
#define getc(fp) ((fp)->incount--,(fp)->incount>=0?(int)*(fp)->p++:__srget(fp))
#define putc(c,fp) \
((fp)->outcount--,(fp)->outcount>=0|| \
((fp)->outcount>=(fp)->linebufsize&&(char)(c)!='\n')? \
*(fp)->p++=(c):__swbuf((c),(fp)))
#define ferror(fp) ((fp)->flags&64)
#define feof(fp)   ((fp)->flags&32)

/* own stuff */
extern struct MinList __filelist;   /* List of all fopen'ed files */
extern unsigned long *__stdfiledes; /* List of Amiga OS filehandles */
extern struct MinList __memorylist; /* List of memory puddles */

extern int __fflush(FILE *stream); /* fflush single file */
extern void __chkabort(void);      /* check for SIGABRT */

struct filenode /* objects in __filelist */
{
  struct MinNode node;
  FILE FILE;
};

#endif
