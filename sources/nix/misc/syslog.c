// syslog dummy

#include <syslog.h>

void syslog(int channel, const char *fmt, ...) {
}
void closelog(void) {
}
void openlog(const char* name, int c, int l) {
}
