#include <stdarg.h>
#include <unistd.h>

int execlp(const char * file, const char *arg, ...) {
	va_list v;

	// count
	va_start(v, arg);
	int argc = 1;
	while (va_arg(v, const char *)) {
		++argc;
	}
	va_end(v);

	const char * argv[argc + 1];
	argv[0] = arg;

	va_start(v, arg);
	for (int i = 1; i < argc; ++i) {
		argv[i] = va_arg(v, const char *);
	}
	va_end(v);

	return execvp(file, argv);
}
