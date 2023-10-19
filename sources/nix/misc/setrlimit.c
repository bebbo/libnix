#include <sys/resource.h>
#include <errno.h>

__stdargs int setrlimit(int resource, struct rlimit *rlim) {
	if (!rlim)
		return EFAULT;

	return 0;
}
