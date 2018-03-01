#ifndef _HEADERS_STDIO_H
#define _HEADERS_STDIO_H
#include <string.h>
#include <stdarg.h>
#include <exec/lists.h>

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
  short flags;
#define __SLBF	0x0001	  /* line buffered */
#define __SNBF	0x0002	  /* unbuffered */
#define __SRD	0x0004	  /* read mode */
#define __SWR	0x0008	  /* write mode */
#define __SEOF	0x0020	  /* EOF read */
#define __SERR	0x0040	  /* error encountered */
#define __SMBF	0x0080	  /* buffer malloc'ed by library */
#define __SSTR	0x0200	  /* sprintf/sscanf buffer */
#define __SWO	0x8000	  /* write-only mode */

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

extern __stdargs FILE *fopen(const char *filename,const char *mode);
extern __stdargs FILE *freopen(const char *filename,const char *mode,FILE *stream);
extern __stdargs FILE *fdopen(int filedes,const char *mode);
extern __stdargs int fclose(FILE *stream);
extern __stdargs int ungetc(int c,FILE *stream);
extern __stdargs int vsprintf(char *s,const char *format,va_list args);
extern __stdargs int vfprintf(FILE *stream,const char *format,va_list args);
extern __stdargs int vsscanf(const char *s,const char *format,va_list args);
extern __stdargs int vfscanf(FILE *stream,const char *format,va_list args);
extern __stdargs int vsnprintf(char *s,size_t size,const char *format,va_list args);
extern __stdargs int fseek(FILE *stream,long int offset,int whence);
extern __stdargs char *fgets(char *s,int size,FILE *stream);
extern __stdargs int fputs(const char *s,FILE *stream);
extern __stdargs long ftell(FILE *stream);
extern __stdargs int setvbuf(FILE *stream,char *buf,int mode,size_t size);
extern __stdargs int fread(void *,size_t,size_t,FILE *);
extern __stdargs int fwrite(const void *,size_t,size_t,FILE *);
extern __stdargs char *tmpnam(char *buf);
extern __stdargs void perror(const char *string);
extern __stdargs int puts(const char *s);
extern __stdargs int remove(const char *filename);
extern __stdargs int rename(const char *old,const char *neww);
extern __stdargs FILE *tmpfile(void);

/* More bsd headers compatibility */

extern __stdargs int __swbuf(int c,FILE *stream);
extern __stdargs int __srget(FILE *stream);
extern FILE **__sF; /* Standard I/O streams */
#define stdin  (__sF[0]) /* Other streams are not in __sF */
#define stdout (__sF[1])
#define stderr (__sF[2])

extern __stdargs int fprintf(FILE *stream,const char *format,...);
extern __stdargs int fscanf(FILE *stream,const char *format,...);
extern __stdargs int printf(const char *format,...);
extern __stdargs int scanf(const char *format,...);
extern __stdargs int sscanf(const char *s,const char *format,...);
extern __stdargs int snprintf(char *s,size_t size,const char *format,...);
extern __stdargs int sprintf(char *s,const char *format,...);

extern __stdargs int getc(FILE *fp);
extern __stdargs int putc(int c, FILE * fp);

/* Inline functions or protos. */
#ifdef __NO_INLINE__
extern __stdargs void clearerr(FILE *stream);
extern __stdargs int feof(FILE * fp);
extern __stdargs int ferror(FILE *fp);
extern __stdargs int fgetc(FILE *stream);
extern __stdargs int fgetpos(FILE *stream,fpos_t *pos);
extern __stdargs int fileno(FILE *file);
extern __stdargs int fputc(int c,FILE *stream);
extern __stdargs int fsetpos(FILE *stream,fpos_t *pos);
extern __stdargs int getchar();
extern __stdargs char *gets(char *s);
extern __stdargs int vprintf(const char *format,va_list args);
extern __stdargs int putchar(int c);
extern __stdargs int vscanf(const char *format,va_list args);
extern __stdargs void rewind(FILE *stream);
extern __stdargs int setbuf(FILE *stream,char *buf);
#else

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define __MY_INLINE__ inline
#else
#define __MY_INLINE__ extern inline
#endif

__MY_INLINE__ __stdargs  void clearerr(FILE *stream)
{ stream->flags&=~(__SERR|__SEOF); }

__MY_INLINE__ __stdargs  int feof(FILE * fp)
{ return ((fp)->flags&__SEOF); }

__MY_INLINE__ __stdargs  int ferror(FILE *fp)
{ return ((fp)->flags&__SERR); }

__MY_INLINE__ __stdargs  int fgetc(FILE *stream)
{ return getc(stream); }

__MY_INLINE__ __stdargs  int fgetpos(FILE *stream,fpos_t *pos)
{ *pos=ftell(stream); return 0; }

__MY_INLINE__ __stdargs  int fileno(FILE *file)
{ return file->file; }

__MY_INLINE__ __stdargs  int fputc(int c,FILE *stream)
{ return putc(c,stream); }

__MY_INLINE__ __stdargs  int fsetpos(FILE *stream,fpos_t *pos)
{ return fseek(stream,*pos,SEEK_SET); }

__MY_INLINE__ __stdargs  int getchar()
{ return getc(stdin);
}

__MY_INLINE__ __stdargs  char *gets(char *s)
{ return fgets(s, 0, stdin); }

__MY_INLINE__ __stdargs  int vprintf(const char *format,va_list args)
{ return vfprintf(stdout,format,args); }

__MY_INLINE__ __stdargs  int putchar(int c)
{ return putc(c, stdout); }

__MY_INLINE__ __stdargs  int vscanf(const char *format,va_list args)
{ return vfscanf(stdin,format,args); }

__MY_INLINE__ __stdargs  void rewind(FILE *stream)
{ fseek(stream,0,SEEK_SET); }

__MY_INLINE__ __stdargs  int setbuf(FILE *stream,char *buf)
{ return setvbuf(stream,buf,buf?_IOFBF:_IONBF,BUFSIZ); }
#endif

/* own stuff */
extern struct MinList __filelist;   /* List of all fopen'ed files */
extern struct MinList __memorylist; /* List of memory puddles */
extern int __vfprintf_total_size(FILE *stream, const char *fmt, va_list args);

#define __fflush fflush
extern __stdargs int __fflush(FILE *stream); /* fflush single file */
extern __stdargs void __chkabort(void);      /* check for SIGABRT */

/* objects in __filelist */
struct filenode {
  struct MinNode node;
  FILE FILE;
};

/*
** FILE/SOCKET abstraction layer
*/

#ifndef _SOCKET_IO

typedef struct _StdFileDes {
  long lx_fh;
  int  lx_pos; /* __stdfiledes[lx_pos]; */
  int  lx_inuse;
  int  lx_oflags;
  char lx_isatty;
  char lx_sys;
} StdFileDes;

#else

#include <sys/types.h>
#include <dos/dosextens.h>

struct stat;

typedef enum {LX_FILE,LX_SOCKET} LX_FILE_TYPE;

typedef struct _StdFileDes {
  LX_FILE_TYPE lx_type;
  int          lx_pos; /* __stdfiledes[lx_pos]; */
  int          lx_inuse;
  union {
    struct {
      int                    lx_oflags;
      long                   lx_fh;
      char                   lx_isatty;
      char                   lx_sys,lx_pad[2];
      struct StandardPacket *lx_packet;
    } file;
    struct {
      int lx_sock;
      int lx_family;
      int lx_protocol;
      int lx_domain;
    } sock;
  } fd;
#define lx_oflags   fd.file.lx_oflags
#define lx_fh       fd.file.lx_fh
#define lx_isatty   fd.file.lx_isatty
#define lx_sys      fd.file.lx_sys
#define lx_packet   fd.file.lx_packet
#define lx_sock     fd.sock.lx_sock
#define lx_family   fd.sock.lx_family
#define lx_protocol fd.sock.lx_protocol
#define lx_domain   fd.sock.lx_domain

  ssize_t __stdargs (*lx_read)(struct _StdFileDes *,void *,size_t);
  ssize_t __stdargs (*lx_write)(struct _StdFileDes *,const void *,size_t);
  int     __stdargs (*lx_close)(struct _StdFileDes *);
  int     __stdargs (*lx_dup)(struct _StdFileDes *);
  int     __stdargs (*lx_fstat)(struct _StdFileDes *,struct stat *);
  int     __stdargs (*lx_select)(struct _StdFileDes *sfd,int select_cmd,int io_mode,fd_set *,u_long *);
} StdFileDes;

extern __stdargs StdFileDes *_lx_fdfromfh(int fh, LX_FILE_TYPE type);

#endif /* _SOCKET_IO */

extern __stdargs StdFileDes *_lx_fhfromfd(int fd);

#endif /* _HEADERS_STDIO_H */
