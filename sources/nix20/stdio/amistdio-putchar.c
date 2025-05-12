#include "amistdio.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stabs.h>

#include <dos/dosextens.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#include <proto/exec.h>

void amiputchar(char c) {
<<<<<<< HEAD
	FPutC(Output(), c);
=======
	BPTR f = Output();
	FPutC(f, c);
>>>>>>> refs/heads/master
}
