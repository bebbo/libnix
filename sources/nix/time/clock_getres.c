#include <time.h>

int clock_getres(clockid_t clk_id, struct timespec *res) {
	return _CLOCKS_PER_SEC_;
}
