int errno=0;

int *__errno (void) {
	return &errno;
}

void * _impure_ptr;
