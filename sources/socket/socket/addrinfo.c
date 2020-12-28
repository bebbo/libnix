#include "socket.h"
#include <proto/bsdsocket.h>

asm("_freeaddrinfo: .global _freeaddrinfo");
void __freeaddrinfo(struct addrinfo *ai) {
	freeaddrinfo(ai);
}

asm("_getaddrinfo: .global _getaddrinfo");
int __getaddrinfo(const char *restrict nodename,
       const char *restrict servname,
       const struct addrinfo *restrict hints,
       struct addrinfo **restrict res) {
	return getaddrinfo(nodename, servname, hints, res);
}

asm("_getnameinfo: .global _getnameinfo");
int __getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
                char *host, socklen_t hostlen,
                char *serv, socklen_t servlen, int flags) {
	return getnameinfo(addr, addrlen, (STRPTR)host, hostlen, (STRPTR)serv, servlen, flags);
}

asm("_gai_strerror: .global _gai_strerror");
const char * __gai_strerror(int ecode) {
	return gai_strerror(ecode);
}
