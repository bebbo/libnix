#include "socket.h"

#include <exec/libraries.h>

#define BSDSOCKET_BASE_NAME SocketBase
extern struct Library * SocketBase;

#define __freeaddrinfo(ai) ({ \
  struct addrinfo * _freeaddrinfo_ai = (ai); \
  { \
  register struct Library * const __freeaddrinfo__bn __asm("a6") = (struct Library *) (BSDSOCKET_BASE_NAME); register int _d1 __asm("d1"); register int _a0 __asm("a0"); register int _a1 __asm("a1");\
  register struct addrinfo * __freeaddrinfo_ai __asm("a0") = (_freeaddrinfo_ai); \
  __asm volatile ("jsr a6@(-804:W)" \
  : \
  : "r"(__freeaddrinfo__bn), "r"(__freeaddrinfo_ai) \
  : "d0", "d1", "a1", "fp0", "fp1", "cc", "memory"); \
  } \
})

#define __freeaddrinfo(ai) ({ \
  struct addrinfo * _freeaddrinfo_ai = (ai); \
  { \
  register struct Library * const __freeaddrinfo__bn __asm("a6") = (struct Library *) (BSDSOCKET_BASE_NAME); register int _d1 __asm("d1"); register int _a0 __asm("a0"); register int _a1 __asm("a1");\
  register struct addrinfo * __freeaddrinfo_ai __asm("a0") = (_freeaddrinfo_ai); \
  __asm volatile ("jsr a6@(-804:W)" \
  : \
  : "r"(__freeaddrinfo__bn), "r"(__freeaddrinfo_ai) \
  : "d0", "d1", "a1", "fp0", "fp1", "cc", "memory"); \
  } \
})

#define __getaddrinfo(hostname, servname, hints, res) ({ \
  CONST_STRPTR _getaddrinfo_hostname = (hostname); \
  CONST_STRPTR _getaddrinfo_servname = (servname); \
  const struct addrinfo * _getaddrinfo_hints = (hints); \
  struct addrinfo ** _getaddrinfo_res = (res); \
  LONG _getaddrinfo__re = \
  ({ \
  register struct Library * const __getaddrinfo__bn __asm("a6") = (struct Library *) (BSDSOCKET_BASE_NAME); register int _d1 __asm("d1"); register int _a0 __asm("a0"); register int _a1 __asm("a1");\
  register LONG __getaddrinfo__re __asm("d0"); \
  register CONST_STRPTR __getaddrinfo_hostname __asm("a0") = (_getaddrinfo_hostname); \
  register CONST_STRPTR __getaddrinfo_servname __asm("a1") = (_getaddrinfo_servname); \
  register const struct addrinfo * __getaddrinfo_hints __asm("a2") = (_getaddrinfo_hints); \
  register struct addrinfo ** __getaddrinfo_res __asm("a3") = (_getaddrinfo_res); \
  __asm volatile ("jsr a6@(-810:W)" \
  : "=r" (_d1), "=r" (_a0), "=r" (_a1),  "=r"(__getaddrinfo__re) \
  : "r"(__getaddrinfo__bn), "r"(__getaddrinfo_hostname), "r"(__getaddrinfo_servname), "r"(__getaddrinfo_hints), "r"(__getaddrinfo_res) \
  : "fp0", "fp1", "cc", "memory"); \
  __getaddrinfo__re; \
  }); \
  _getaddrinfo__re; \
})

#define __getnameinfo(sa, salen, host, hostlen, serv, servlen, flags) ({ \
  const struct sockaddr * _getnameinfo_sa = (sa); \
  ULONG _getnameinfo_salen = (salen); \
  STRPTR _getnameinfo_host = (host); \
  ULONG _getnameinfo_hostlen = (hostlen); \
  STRPTR _getnameinfo_serv = (serv); \
  ULONG _getnameinfo_servlen = (servlen); \
  ULONG _getnameinfo_flags = (flags); \
  LONG _getnameinfo__re = \
  ({ \
  register struct Library * const __getnameinfo__bn __asm("a6") = (struct Library *) (BSDSOCKET_BASE_NAME); register int _d1 __asm("d1"); register int _a0 __asm("a0"); register int _a1 __asm("a1");\
  register LONG __getnameinfo__re __asm("d0"); \
  register const struct sockaddr * __getnameinfo_sa __asm("a0") = (_getnameinfo_sa); \
  register ULONG __getnameinfo_salen __asm("d0") = (_getnameinfo_salen); \
  register STRPTR __getnameinfo_host __asm("a1") = (_getnameinfo_host); \
  register ULONG __getnameinfo_hostlen __asm("d1") = (_getnameinfo_hostlen); \
  register STRPTR __getnameinfo_serv __asm("a2") = (_getnameinfo_serv); \
  register ULONG __getnameinfo_servlen __asm("d2") = (_getnameinfo_servlen); \
  register ULONG __getnameinfo_flags __asm("d3") = (_getnameinfo_flags); \
  __asm volatile ("jsr a6@(-822:W)" \
  : "=r" (_d1), "=r" (_a0), "=r" (_a1),  "=r"(__getnameinfo__re) \
  : "r"(__getnameinfo__bn), "r"(__getnameinfo_sa), "r"(__getnameinfo_salen), "r"(__getnameinfo_host), "r"(__getnameinfo_hostlen), "r"(__getnameinfo_serv), "r"(__getnameinfo_servlen), "r"(__getnameinfo_flags) \
  : "fp0", "fp1", "cc", "memory"); \
  __getnameinfo__re; \
  }); \
  _getnameinfo__re; \
})

#define __gai_strerror(errnum) ({ \
  LONG _gai_strerror_errnum = (errnum); \
  STRPTR _gai_strerror__re = \
  ({ \
  register struct Library * const __gai_strerror__bn __asm("a6") = (struct Library *) (BSDSOCKET_BASE_NAME); register int _d1 __asm("d1"); register int _a0 __asm("a0"); register int _a1 __asm("a1");\
  register STRPTR __gai_strerror__re __asm("d0"); \
  register LONG __gai_strerror_errnum __asm("a0") = (_gai_strerror_errnum); \
  __asm volatile ("jsr a6@(-816:W)" \
  : "=r" (_d1), "=r" (_a0), "=r" (_a1),  "=r"(__gai_strerror__re) \
  : "r"(__gai_strerror__bn), "r"(__gai_strerror_errnum) \
  : "fp0", "fp1", "cc", "memory"); \
  __gai_strerror__re; \
  }); \
  _gai_strerror__re; \
})

void freeaddrinfo(struct addrinfo *ai) {
	__freeaddrinfo(ai);
}

int getaddrinfo(const char *restrict nodename,
       const char *restrict servname,
       const struct addrinfo *restrict hints,
       struct addrinfo **restrict res) {
	return __getaddrinfo(nodename, servname, hints, res);
}

int getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
                char *host, socklen_t hostlen,
                char *serv, socklen_t servlen, int flags) {
	return __getnameinfo(addr, addrlen, (STRPTR)host, hostlen, (STRPTR)serv, servlen, flags);
}

const char * gai_strerror(int ecode) {
	return __gai_strerror(ecode);
}
