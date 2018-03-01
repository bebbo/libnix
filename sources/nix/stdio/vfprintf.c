#include <stdio.h>
#include <stdarg.h>

int vfprintf(FILE *stream, const char *fmt, va_list args)
{
	int total_write_size = __vfprintf_total_size(stream, fmt, args);
	if(stream->flags & __SERR) {
		return -1;
	}
	return total_write_size;
}

#ifdef TESTME
int main(int argc, char ** argv) {
  double d;
	printf("%-20.0f|\n", 0.0d);
	printf("%-20.0e\n", 0.0d);
	printf("%-20.1g\n", 0.0d);
	printf("%#20.0f\n", 0.0d);
	printf("%#20.0e\n", 0.0d);
	printf("%#20.1g\n", 0.0d);

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7f\n", d);
	}

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7g\n", d);
	}

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7e\n", d);
	}

  return 0;
}
#endif
