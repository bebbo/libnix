#include <stdlib.h>
#include <sys/syslimits.h>
#include "stdio.h"

/* NOTE: NOT thread-safe */
FILE *tmpfile(void)
{ 
    char *name = malloc(PATH_MAX);
    FILE *file;

    if (name == NULL)
	goto error;

    if (tmpnam(name) == NULL) {
	goto error;
    }

    file = fopen(name,"w+b");
    if (file == NULL)
	goto error;

    file->name = name;
    return file;
error:
    if (name != NULL)
	free(name);

    return NULL;
}
