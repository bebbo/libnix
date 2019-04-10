#include <sys/types.h>
#include <sys/socket.h>
//
#include "socket.h"

ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{ struct SocketSettings *lss;
  StdFileDes *fp = _lx_fhfromfd(s);
  int rc;

  switch (lss=_lx_get_socket_settings(),lss->lx_network_type) {
    case LX_AS225:
      rc = SOCK_recvfrom(fp->lx_sock,buf,len,flags, from, (int*)fromlen);
    break;

    case LX_AMITCP:
      rc = TCP_RecvFrom(fp->lx_sock,buf,len,flags, from, (int*)fromlen);
    break;

    default:
      rc = -1;
    break;
  }

  return rc;
}
