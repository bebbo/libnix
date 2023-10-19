#include <sys/resource.h>
#include <errno.h>

__stdargs int getrlimit(int resource, struct rlimit *rlim) {
	if (!rlim)
		return EFAULT;

	rlim->rlim_cur = rlim->rlim_max = RLIM_INFINITY;
	return 0;
}
