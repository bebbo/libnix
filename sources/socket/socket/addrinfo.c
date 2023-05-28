#include "socket.h"

#define freeaddrinfo __freeaddrinfo
#define getaddrinfo __getaddrinfo
#define getnameinfo __getnameinfo
#define gai_strerror __gai_strerror
#include <proto/bsdsocket.h>
#undef freeaddrinfo
#undef getaddrinfo
#undef getnameinfo
#undef gai_strerror

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
