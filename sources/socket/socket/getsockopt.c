#include "stdio.h"
#include <sys/types.h>
#include <sys/socket.h>
//
#include "socket.h"

#include <inline/amitcp.h>
#include <inline/as225.h>

int getsockopt(int s, int level, int name, void *val, socklen_t *valsize)
{ struct SocketSettings *lss;
  StdFileDes *fp = _lx_fhfromfd(s);
  int rc;

  switch (lss=_lx_get_socket_settings(),lss->lx_network_type) {
    case LX_AS225:
      rc = SOCK_getsockopt(fp->lx_sock,level,name,(char *)val, (int*)valsize);
    break;

    case LX_AMITCP:
      rc = TCP_GetSockOpt(fp->lx_sock,level,name,(char *)val, (int*)valsize);
    break;

    default:
      rc = 0;
    break;
  }

  return rc;
}
