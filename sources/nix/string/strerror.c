#include <stdlib.h>

const char * __sys_errlist[] = {
	"Undefined error",

	"Operation not permitted",	// 1: EPERM
	"No such file or directory",	// 2: ENOENT
	"No such process",	// 3: ESRCH
	"Interrupted system call",	// 4: EINTR
	"I/O error",	// 5: EIO
	"No such device or address",	// 6: ENXIO
	"Argument list too long",	// 7: E2BIG
	"Exec format error",	// 8: ENOEXEC
	"Bad file number",	// 9: EBADF
	"No child processes",	// 10: ECHILD
	"Try again",	// 11: EAGAIN
	"Out of memory",	// 12: ENOMEM
	"Permission denied",	// 13: EACCES
	"Bad address",	// 14: EFAULT
	"Block device required",	// 15: ENOTBLK
	"Device or resource busy",	// 16: EBUSY
	"File exists",	// 17: EEXIST
	"Cross-device link",	// 18: EXDEV
	"No such device",	// 19: ENODEV
	"Not a directory",	// 20: ENOTDIR
	"Is a directory",	// 21: EISDIR
	"Invalid argument",	// 22: EINVAL
	"File table overflow",	// 23: ENFILE
	"Too many open files",	// 24: EMFILE
	"Not a typewriter",	// 25: ENOTTY
	"Text file busy",	// 26: ETXTBSY
	"File too large",	// 27: EFBIG
	"No space left on device",	// 28: ENOSPC
	"Illegal seek",	// 29: ESPIPE
	"Read-only file system",	// 30: EROFS
	"Too many links",	// 31: EMLINK
	"Broken pipe",	// 32: EPIPE

/* math software */
	"Math argument out of domain of func",	// 33: EDOM
	"Math result not representable",	// 34: ERANGE

/* non-blocking and interrupt i/o */
	"Resource temporarily unavailable",	// 35: EAGAIN
	"Operation now in progress",	// 36: EINPROGRESS
	"Operation already in progress",	// 37: EALREADY

/* ipc/network software -- argument errors */
	"Socket operation on non-socket",	// 38: ENOTSOCK
	"Destination address required",	// 39: EDESTADDRREQ
	"Message too long",	// 40: EMSGSIZE
	"Protocol wrong type for socket",	// 41: EPROTOTYPE
	"Protocol not available",	// 42: ENOPROTOOPT
	"Protocol not supported",	// 43: EPROTONOSUPPORT
	"Socket type not supported",	// 44: ESOCKTNOSUPPORT
	"Operation not supported",	// 45: EOPNOTSUPP
	"Protocol family not supported",	// 46: EPFNOSUPPORT
	"Address family not supported by protocol family",	// 47: EAFNOSUPPORT
	"Address already in use",	// 48: EADDRINUSE
	"Can't assign requested address",	// 49: EADDRNOTAVAIL

/* ipc/network software -- operational errors */
	"Network is down",	// 50: ENETDOWN
	"Network is unreachable",	// 51: ENETUNREACH
	"Network dropped connection on reset",	// 52: ENETRESET
	"Software caused connection abort",	// 53: ECONNABORTED
	"Connection reset by peer",	// 54: ECONNRESET
	"No buffer space available",	// 55: ENOBUFS
	"Socket is already connected",	// 56: EISCONN
	"Socket is not connected",	// 57: ENOTCONN
	"Can't send after socket shutdown",	// 58: ESHUTDOWN
	"Too many references: can't splice",	// 59: ETOOMANYREFS
	"Operation timed out",	// 60: ETIMEDOUT
	"Connection refused",	// 61: ECONNREFUSED

	"Too many levels of symbolic links",	// 62: ELOOP
	"File name too long",	// 63: ENAMETOOLONG

/* should be rearranged */
	"Host is down",	// 64: EHOSTDOWN
	"No route to host",	// 65: EHOSTUNREACH
	"Directory not empty",	// 66: ENOTEMPTY

/* quotas & mush */
	"Too many processes",	// 67: EPROCLIM
	"Too many users",	// 68: EUSERS
	"Disc quota exceeded",	// 69: EDQUOT

/* Network File System */
	"Stale NFS file handle",	// 70: ESTALE
	"Too many levels of remote in path",	// 71: EREMOTE
	"RPC struct is bad",	// 72: EBADRPC
	"RPC version wrong",	// 73: ERPCMISMATCH
	"RPC prog. not avail",	// 74: EPROGUNAVAIL
	"Program version wrong",	// 75: EPROGMISMATCH
	"Bad procedure for program",	// 76: EPROCUNAVAIL

	"No locks available",	// 77: ENOLCK
	"Function not implemented",	// 78: ENOSYS

	"Inappropriate file type or format",	// 79: EFTYPE

/* others.. */
	"corrupted shared library",	// 80: ELIBBAD
	"section corrupted",	// 81: ELIBSCN
	"link overflow",	// 82: ELIBMAX
	"exec error",	// 83: ELIBEXEC

	"Illegal byte sequence",	// 84: EILSEQ
	"Interrupted system call should be restarted",	// 85: ERESTART
	"Streams pipe error",	// 86: ESTRPIPE
	"Too many users",	// 87: EUSERS
	"Socket operation on non-socket",	// 88: ENOTSOCK
	"Destination address required",	// 89: EDESTADDRREQ
	"Message too long",	// 90: EMSGSIZE
	"Protocol wrong type for socket",	// 91: EPROTOTYPE
	"Protocol not available",	// 92: ENOPROTOOPT
	"Protocol not supported",	// 93: EPROTONOSUPPORT
	"Socket type not supported",	// 94: ESOCKTNOSUPPORT
	"Operation not supported on transport endpoint",	// 95: EOPNOTSUPP
	"Protocol family not supported",	// 96: EPFNOSUPPORT
	"Address family not supported by protocol",	// 97: EAFNOSUPPORT
	"Address already in use",	// 98: EADDRINUSE
	"Cannot assign requested address",	// 99: EADDRNOTAVAIL
	"Network is down",	// 100: ENETDOWN
	"Network is unreachable",	// 101: ENETUNREACH
	"Network dropped connection because of reset",	// 102: ENETRESET
	"Software caused connection abort",	// 103: ECONNABORTED
	"Connection reset by peer",	// 104: ECONNRESET
	"No buffer space available",	// 105: ENOBUFS
	"Transport endpoint is already connected",	// 106: EISCONN
	"Transport endpoint is not connected",	// 107: ENOTCONN
	"Cannot send after transport endpoint shutdown",	// 108: ESHUTDOWN
	"Too many references: cannot splice",	// 109: ETOOMANYREFS
	"Connection timed out",	// 110: ETIMEDOUT
	"Connection refused",	// 111: ECONNREFUSED
	"Host is down",	// 112: EHOSTDOWN
	"No route to host",	// 113: EHOSTUNREACH
	"Operation already in progress",	// 114: EALREADY
	"Operation now in progress",	// 115: EINPROGRESS
	"Stale NFS file handle",	// 116: ESTALE
	"Structure needs cleaning",	// 117: EUCLEAN
	"Not a XENIX named type file",	// 118: ENOTNAM
	"No XENIX semaphores available",	// 119: ENAVAIL
	"Is a named type file",	// 120: EISNAM
	"Remote I/O error",	// 121: EREMOTEIO
	"Quota exceeded",	// 122: EDQUOT

	"No medium found",	// 123: ENOMEDIUM
	"Wrong medium type",	// 124: EMEDIUMTYPE
	"Operation Canceled",	// 125: ECANCELED
	"Required key not available",	// 126: ENOKEY
	"Key has expired",	// 127: EKEYEXPIRED
	"Key has been revoked",	// 128: EKEYREVOKED
	"Key was rejected by service",	// 129: EKEYREJECTED

/* for robust mutexes */
	"Owner died",	// 130: EOWNERDEAD
	"State not recoverable",	// 131: ENOTRECOVERABLE
};

#define sys_nerr (sizeof(__sys_errlist)/sizeof(__sys_errlist[0]))
extern int
#ifdef __posix_threads__
__thread
#endif
errno;
extern void __seterrno(void);

char *strerror(int eno)
{ if(eno<1||eno>=sys_nerr)
  { int saved_errno=errno;
    __seterrno();
    eno = errno;
    errno=saved_errno; }
  return(char *)__sys_errlist[eno];
}

char *strerror_r(int errnum, char *buffer, size_t buflen)
{ char *b=buffer,*ptr=strerror(errnum);
  while(buflen-- > 1)
  { if(!(*b++ = *ptr++))
      break;
  } *b = '\0';
  return buffer;
}
