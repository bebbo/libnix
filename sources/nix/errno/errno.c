// errno moved to __stdio.c
extern int errno;
int *__errno (void) {
	return &errno;
}
