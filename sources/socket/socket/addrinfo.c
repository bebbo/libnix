#include "socket.h"
#include <proto/bsdsocket.h>
#include "stabs.h"

void __freeaddrinfo(struct addrinfo *ai) {
	freeaddrinfo(ai);
}

int __getaddrinfo(const char *restrict nodename,
       const char *restrict servname,
       const struct addrinfo *restrict hints,
       struct addrinfo **restrict res) {
	return getaddrinfo(nodename, servname, hints, res);
}

int __getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
                char *host, socklen_t hostlen,
                char *serv, socklen_t servlen, int flags) {
	return getnameinfo(addr, addrlen, (STRPTR)host, hostlen, (STRPTR)serv, servlen, flags);
}

const char * __gai_strerror(int ecode) {
	return gai_strerror(ecode);
}

ALIAS(freeaddrinfo, __freeaddrinfo);
ALIAS(getaddrinfo, __getaddrinfo);
ALIAS(getnameinfo, __getnameinfo);
ALIAS(gai_strerror, __gai_strerror);
